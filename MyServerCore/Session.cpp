#include "pch.h"
#include "Session.h"

#include"IocpEvent.h"
#include"NetService.h"

Session::Session()
{
}

Session::~Session()
{
	cout << "~Session()" << endl;
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int len)
{
	switch (iocpEvent->_type) {
	case EventType::SEND:
		ProcessSend(len);
		break;
	case EventType::RECV:
		ProcessRecv(len);
		break;
	case EventType::DISCONNECT:
		ProcessDisconnect();
		break;
	default:
		break;
	}
}

void Session::RegisterRecv()
{
	cout << "Session::RegisterRecv()" << endl;
	if (!_isConnected.load()) {
		return;
	}

	_recvEvent._ownerIocpObject = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = _recvBuffer.BufferWritePos();
	wsaBuf.len = _recvBuffer.FreeSize();
	DWORD dwBytes;
	DWORD flag = 0;
	if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, &dwBytes, &flag, reinterpret_cast<LPWSAOVERLAPPED>(&_recvEvent), 0)) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			NetUtils::HandleError("RegisterRecv");
			_recvEvent.Reset();
			_recvEvent._ownerIocpObject.reset();
		}
	}
}

void Session::ProcessRecv(int recvLen)
{
	cout << "Sesson::ProcessRecv()" << endl;
	// Reset RecvEvent
	_recvEvent.Reset();
	_recvEvent._ownerIocpObject.reset();

	if (!_isConnected.load())
		return;

	if (recvLen <= 0) {
		Disconnect();
		return;
	}

	_recvBuffer.OnWrite(recvLen);
	if (_recvBuffer.DataSize() >= sizeof(PacketHeader)) {
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_recvBuffer.BufferReadPos());
		int packetSize = header->_size;
		int totalSize = packetSize + sizeof(PacketHeader);
		
		if (totalSize <= _recvBuffer.DataSize()) {
			OnRecv(_recvBuffer.BufferReadPos(), totalSize);
			_recvBuffer.OnRead(totalSize);
			_recvBuffer.Reset();
		}
	}

	// Register Recv Again
	RegisterRecv();
}

void Session::Send(shared_ptr<SendBuffer> sendBuffer)
{
	cout << "Send()" << endl;
	if (!_isConnected.load()) {
		return;
	}

	WSABUF wsaBuf;
	wsaBuf.buf = sendBuffer->Buffer();
	wsaBuf.len = sendBuffer->Size();

	{
		lock_guard<mutex> lock(_mutex);
		_wsaBufFront.push_back(wsaBuf);
	}

	if (_isSendRegistered.exchange(true) == false) {
		RegisterSend();
	}
}

void Session::RegisterSend()
{
	cout << "RegisterSend()" << endl;
	if (!_isConnected.load())
		return;

	_sendEvent._ownerIocpObject = shared_from_this();
	
	{
		lock_guard<mutex> lock(_mutex);
		_wsaBufFront.swap(_wsaBufBack);
	}

	DWORD dwSendByte;
	if (::WSASend(_socket, _wsaBufBack.data(), _wsaBufBack.size(), &dwSendByte, DWORD(0), reinterpret_cast<LPWSAOVERLAPPED>(&_sendEvent), 0)) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			_sendEvent.Reset();
			_sendEvent._ownerIocpObject.reset();
		}
	}
}

void Session::ProcessSend(int sendLen)
{
	cout << "ProcessSend()" << endl;
	_sendEvent.Reset();
	_sendEvent._ownerIocpObject.reset();

	if (!_isConnected.load())
		return;

	if (sendLen <= 0) {
		Disconnect();
		return;
	}

	_wsaBufBack.clear();
	_isSendRegistered.exchange(false);
	
	OnSend(sendLen);
}

void Session::Disconnect()
{
	cout << "Disconnect()" << endl;
	// load로 처리하려고 했으나 그 잠시 사이에 다른 진입이 있을 수 있기에 한 방에 가야댐
	if (_isConnected.exchange(false) == false)
		return;

	RegisterDisconnect();
}

bool Session::RegisterDisconnect()
{
	cout << "RegisterDisconnect()" << endl;
	_disconnectEvent._ownerIocpObject = shared_from_this();

	if (NetUtils::_disconnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0)) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			_disconnectEvent.Reset();
			_disconnectEvent._ownerIocpObject.reset();
			return false;
		}
	}

	return true;
}

void Session::ProcessDisconnect()
{
	cout << "ProcessDisconnect()" << endl;
	_ownerNetService->RemoveSession(static_pointer_cast<Session>(shared_from_this()));
	_disconnectEvent.Reset();
	_disconnectEvent._ownerIocpObject.reset();
}
