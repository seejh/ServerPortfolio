#include "pch.h"
#include "NetService.h"




NetService::NetService(function<shared_ptr<Session>()> sessionFactory) : _sessionFactory(sessionFactory)
{
}

NetService::~NetService()
{
}

shared_ptr<Session> NetService::CreateSession()
{
	return _sessionFactory();
}

void NetService::AddSession(shared_ptr<Session> session)
{
	// WRITE_LOCK
	_connectedSessions.insert(session);
	_connectedSessionCount++;
}

void NetService::RemoveSession(shared_ptr<Session> session)
{
	// WRITE_LOCK
	
	ASSERT_CRASH(_connectedSessions.erase(session) != 0);
	_connectedSessionCount--;
}

bool NetService::Init()
{
	_iocpCore = make_shared<IocpCore>();
	_listenSession = make_shared<ListenSession>(this);
	if (_listenSession->Init())
		return false;

	cout << "Listen Init OK now Listening..." << endl;

	return true;
}
