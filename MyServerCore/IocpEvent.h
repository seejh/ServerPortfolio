#pragma once

class IocpObject;
class Session;

enum EventType { ACCEPT, CONNECT, DISCONNECT, SEND, RECV, };

// �̺�Ʈ�� ���ÿ��� ������ ���̸�, ���� ���ο��� ���Ǵ� ����Ʈ ������ ������� ����� ������ ������ �Ҵ� �����ϴ� ����̹Ƿ�
// ���⼭ �Ҹ��ڸ� ���� ������ �ʿ䰡 ����.
// ���� WSAOVERLAPPED�� �Ҵ� �޴� ������ ������µ�, virtual �Ἥ ������ �и�
class IocpEvent : public WSAOVERLAPPED
{
public:
	IocpEvent(EventType type) : _type(type) { Reset(); }

	void Reset() {
		hEvent = 0;
		Internal = 0;
		InternalHigh = 0;
		Offset = 0;
		OffsetHigh = 0;
	}
public:
	EventType _type;
	shared_ptr<IocpObject> _ownerIocpObject;
};

class AcceptEvent : public IocpEvent {
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT) {}
public:
	shared_ptr<Session> _connectedSession;
};

class ConnectEvent : public IocpEvent {
public:
	ConnectEvent() : IocpEvent(EventType::CONNECT) {}
};

class DisconnectEvent : public IocpEvent {
public:
	DisconnectEvent() : IocpEvent(EventType::DISCONNECT) {}
};

class SendEvent : public IocpEvent {
public:
	SendEvent() : IocpEvent(EventType::SEND) {}
};

class RecvEvent : public IocpEvent {
public:
	RecvEvent() : IocpEvent(EventType::RECV) {}
};