#pragma once

#include"IocpCore.h"
#include"IocpEvent.h"
#include"RecvBuffer.h"
#include"SendBuffer.h"

class NetService;

struct PacketHeader {
	short _id;
	short _size;
};

class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();

	// for hooking
	virtual void OnConnected() {}
	virtual void OnDisconnected() {}
	virtual void OnSend(int len) {}
	virtual void OnRecv(char* buffer, int len) { cout << "OnRecv()" << endl; }

	// override
	virtual HANDLE GetHandle();
	virtual void Dispatch(IocpEvent* iocpEvent, int len);

	//void ProcessConnect();

	void RegisterRecv();
	void ProcessRecv(int recvLen);

	void Send(shared_ptr<SendBuffer> sendBuffer);
	void RegisterSend();
	void ProcessSend(int sendLen);

	void Disconnect();
	bool RegisterDisconnect();
	void ProcessDisconnect();

public:
	SOCKET _socket;
	NetService* _ownerNetService;

	SendEvent _sendEvent;
	RecvEvent _recvEvent;
	DisconnectEvent _disconnectEvent;
	//ConnectEvent _connectEvent;
	
	RecvBuffer _recvBuffer;
	vector<WSABUF> _wsaBufFront;
	vector<WSABUF> _wsaBufBack;
	atomic<bool> _isSendRegistered;
	atomic<bool> _isConnected;

	mutex _mutex;
};

