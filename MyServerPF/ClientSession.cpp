#include "pch.h"
#include "ClientSession.h"

#include"ClientPacketHandler.h"
#include"SessionManager.h"
#include"Actor.h"
#include"Room.h"

void ClientSession::OnConnected()
{
	SessionManager::Instance()->AddSession(static_pointer_cast<ClientSession>(shared_from_this()));
}

void ClientSession::OnDisconnected()
{
	// 플레이어가 있으면
	if (_player.get() != nullptr) {
		// 룸에서 플레이어 제거
		Room::Instance()->PlayerLeave(_player);

		// 플레이어에서 세션 참조 해제
		_player->_ownerSession.reset();
	}

	// 세션에서 플레이어 참조 해제
	_player.reset();

	// 세션 매니저에서 이 세션 제거
	SessionManager::Instance()->RemoveSession(static_pointer_cast<ClientSession>(shared_from_this()));
	
}

void ClientSession::OnSend(int len)
{
}

void ClientSession::OnRecv(char* buffer, int len)
{
	ClientPacketHandler::HandlePacket(static_pointer_cast<ClientSession>(shared_from_this()), buffer, len);
}
