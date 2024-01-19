#include "pch.h"
#include "SessionManager.h"

SessionManager* SessionManager::_instance = nullptr;


void SessionManager::AddSession(shared_ptr<ClientSession> session)
{
	lock_guard<mutex> lock(_mutex);
	_sessions.insert(session);
}

void SessionManager::RemoveSession(shared_ptr<ClientSession> session)
{
	lock_guard<mutex> lock(_mutex);
	_sessions.erase(session);
}
