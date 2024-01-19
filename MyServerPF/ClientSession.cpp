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
	// �÷��̾ ������
	if (_player.get() != nullptr) {
		// �뿡�� �÷��̾� ����
		Room::Instance()->PlayerLeave(_player);

		// �÷��̾�� ���� ���� ����
		_player->_ownerSession.reset();
	}

	// ���ǿ��� �÷��̾� ���� ����
	_player.reset();

	// ���� �Ŵ������� �� ���� ����
	SessionManager::Instance()->RemoveSession(static_pointer_cast<ClientSession>(shared_from_this()));
	
}

void ClientSession::OnSend(int len)
{
}

void ClientSession::OnRecv(char* buffer, int len)
{
	ClientPacketHandler::HandlePacket(static_pointer_cast<ClientSession>(shared_from_this()), buffer, len);
}
