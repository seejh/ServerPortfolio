#include "pch.h"
#include "ListenSession.h"

#include"NetService.h"
#include"IocpCore.h"
#include"Session.h"
#include"IocpEvent.h"

ListenSession::ListenSession(NetService* netService) : _ownerNetService(netService)
{
}

ListenSession::~ListenSession()
{
}

HANDLE ListenSession::GetHandle()
{
    return reinterpret_cast<HANDLE>(_listenSocket);
}

void ListenSession::Dispatch(IocpEvent* iocpEvent, int len)
{
    AcceptEvent* acceptEvent = reinterpret_cast<AcceptEvent*>(iocpEvent);
    ProcessAccept(acceptEvent);
}

bool ListenSession::Init()
{
    if (!NetUtils::Init())
        return NetUtils::HandleError("ListenSession Init::NetUtils::Init");

    _listenSocket = NetUtils::CreateSocket();
    if (_listenSocket == INVALID_SOCKET)
        return NetUtils::HandleError("ListenSession::Init INVLAID listenSocket");

    // setsockopt reuse

    string ip = "127.0.0.1";
    int port = 7777;
    NetUtils::SetSockAddrIn(_serverAddr, ip, port);

    if (!NetUtils::Bind(_listenSocket, _serverAddr))
        return NetUtils::HandleError("ListenSession::Init Bind");
    if (!NetUtils::Listen(_listenSocket))
        return NetUtils::HandleError("ListenSession::Init Listen");

    _ownerNetService->_iocpCore->Register(shared_from_this());
    _acceptEvents = new AcceptEvent[_acceptCount];
    
    for (int i = 0; i < _acceptCount; i++) {
        _acceptEvents[i]._ownerIocpObject = shared_from_this();

        if (!RegisterAccept(&_acceptEvents[i]))
            return false;
    }

    return true;
}

bool ListenSession::RegisterAccept(AcceptEvent* acceptEvent)
{
    cout << "ListenSession::RegisterAccept()" << endl;
    DWORD dwBytes;

    // CreateSession
    shared_ptr<Session> session = _ownerNetService->_sessionFactory();
    session->_socket = NetUtils::CreateSocket();
    if (session->_socket == INVALID_SOCKET)
        return false;

    // shared_ptr<Session> session = CreateSession();
    acceptEvent->_connectedSession = session;
    
    if (NetUtils::_acceptEx(_listenSocket, session->_socket, session->_recvBuffer.BufferWritePos(), 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwBytes, reinterpret_cast<LPOVERLAPPED>(acceptEvent))) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            return false;
        }
    }

    return true;
}

void ListenSession::ProcessAccept(AcceptEvent* acceptEvent)
{
    cout << "ListenSession::ProcessAccept()" << endl;
    
    // Register session to IOCP & NetService
    shared_ptr<Session> session = acceptEvent->_connectedSession;
    session->_ownerNetService = _ownerNetService;
    _ownerNetService->_iocpCore->Register(session);
    _ownerNetService->AddSession(session);

    // Session Register Recv
    session->_isConnected.store(true);
    session->RegisterRecv();

    // Reset AcceptEvent
    acceptEvent->Reset();
    acceptEvent->_connectedSession.reset();

    // Register Accept Again
    RegisterAccept(acceptEvent);
}

NetService* ListenSession::OwnerNetService()
{
    return nullptr;
}
