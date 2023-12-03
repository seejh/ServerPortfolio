#pragma once

#include"IocpCore.h"
#include"Session.h"
#include"ListenSession.h"

class NetService
{
public:
	NetService(function<shared_ptr<Session>()> sessionFactory);
	~NetService();

	shared_ptr<Session> CreateSession();
	void AddSession(shared_ptr<Session> session);
	void RemoveSession(shared_ptr<Session> session);
	bool Init();

public:
	shared_ptr<IocpCore> _iocpCore;
	shared_ptr<ListenSession> _listenSession;

	set<shared_ptr<Session>> _connectedSessions;
	int _connectedSessionCount = 0;

	function<shared_ptr<Session>()> _sessionFactory;
	// USE_LOCK;
};

