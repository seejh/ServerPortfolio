#include "pch.h"
#include "SessionManager.h"

#include"ClientPacketHandler.h"

void SessionManager::AddSession(shared_ptr<ClientSession> clientSession)
{
	lock_guard<mutex> _lock(_mutex);
	_clientSessions.insert(clientSession);
}

void SessionManager::RemoveSession(shared_ptr<ClientSession> clientSession)
{
	lock_guard<mutex> _lock(_mutex);
	_clientSessions.erase(clientSession);
}

void ClientSession::OnRecv(char* buffer, int recvLen)
{
	ClientPacketHandler::HandlePacket(static_pointer_cast<ClientSession>(shared_from_this()), buffer, recvLen);
}
