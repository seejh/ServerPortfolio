#include "pch.h"
#include "ClientPacketHandler.h"

#include"Room.h"
#include"Actor.h"
#include"ClientSession.h"

#include"DBBind.h"
#include"DBConnectionPool.h"

function<bool(shared_ptr<ClientSession>, char*, int)> GPacketHandler[PacketCount];

bool Handle_INVALID(shared_ptr<ClientSession> session, char* buffer, int len)
{
	cout << "Handle INVALID PACKET" << endl;
	return false;
}

bool Handle_C_LOGIN(shared_ptr<ClientSession> session, PROTOCOL::C_LOGIN fromPkt)
{
	string fromPktIdStr = fromPkt.id();
	string fromPktPwStr = fromPkt.pw();

	// DB���� ������ �����ͼ� ID, PW �������� üũ
	auto query = L"SELECT playerPw FROM [dbo].[Player] WHERE playerId = (?)";
	DBConnection* dbConn = GDBConnectionPool->Pop();
	DBBind<1, 1> dbBind(*dbConn, query);

	BYTE inIdByte[20] = "";
	::memcpy(inIdByte, fromPktIdStr.c_str(), fromPktIdStr.length());
	dbBind.BindParam(0, inIdByte);

	BYTE outPwByte[20] = "";
	dbBind.BindCol(0, outPwByte);

	bool result = false;
	ASSERT_CRASH(dbBind.Execute());
	while (dbConn->Fetch()) {
		string outPwStr("");
		outPwStr.append((char*)outPwByte);
		
		if (outPwStr.compare(fromPktPwStr) == 0) {
			result = true;
			break;
		}
	}
	GDBConnectionPool->Push(dbConn);

	// TO PACKET
	PROTOCOL::S_LOGIN toPkt;
	if (result) {
		// ���ǿ� �÷��̾� ���� �� ��ȯ ����, �ε��� ����
		shared_ptr<Player> player = make_shared<Player>();
		player->_ownerSession = session;
		session->_player = player;
		player->_index = g_playerIndexGenerator.fetch_add(1);

		cout << "Player-" << player->_index << " Login" << endl;

		// ������ ���� : �α��� ���, ������ �ε���, 
		toPkt.set_success(true);
		toPkt.mutable_actor()->set_index(player->_index);
		toPkt.mutable_actor()->set_actortype(PROTOCOL::PLAYER);
	}
	else {
		toPkt.set_success(false);
	}

	shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
	session->Send(sendBuffer);

	return result;
}

bool Handle_C_ENTER_ROOM(shared_ptr<ClientSession> session, PROTOCOL::C_ENTER_ROOM fromPkt)
{
	// �÷��̾� ���� ���Ƿ� ����, �뿡 ����, ��ε� ĳ����
	cout << "Player-" << session->_player->GetIndex() << " Enter Room " << fromPkt.roomnum() << endl;

	// �뿡 ����	
	PROTOCOL::ACTOR protocolActor;
	Room::Instance()->PlayerEnter(session->_player, protocolActor);

	// Set To PACKET
	PROTOCOL::S_ENTER_ROOM toPkt;
	toPkt.set_success(true);
	toPkt.mutable_actor()->CopyFrom(protocolActor);
	
	// ��ε� ĳ����
	shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
	Room::Instance()->Broadcast(sendBuffer);

	return true;
}

bool Handle_C_PLAYERLIST(shared_ptr<ClientSession> session, PROTOCOL::C_PLAYERLIST fromPkt)
{
	cout << "Player-" << session->_player->_index << " Request PlayerList" << endl;
	
	// Set To PACKET
	PROTOCOL::S_PLAYERLIST toPkt;
	if(Room::Instance()->GetPlayerList(toPkt)) {
		// Send
		shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
		session->Send(sendBuffer);
	}

	return true;
}

bool Handle_C_MONSTERLIST(shared_ptr<ClientSession> session, PROTOCOL::C_MONSTERLIST fromPkt)
{
	cout << "Player-" << session->_player->_index << " Request MonsterList" << endl;

	// Set To PACKET
	PROTOCOL::S_MONSTERLIST toPkt;
	if (Room::Instance()->GetMonsterList(toPkt)) {
		// Send
		shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
		session->Send(sendBuffer);
	}
	
	return true;
}

bool Handle_C_MOVE(shared_ptr<ClientSession> session, PROTOCOL::C_MOVE fromPkt)
{
	// Ŭ�󿡼� ���� �̵� ������ ������ �����̴� �÷��̾� Ÿ�� �ۿ� ����.
	// player ������Ʈ, ��ε� ĳ��Ʈ
	
	// �÷��̾� ������Ʈ
	PROTOCOL::ACTOR protocolActor = fromPkt.actor();
	Room::Instance()->ActorMove(protocolActor);

	// Set To PACKET
	PROTOCOL::S_MOVE toPkt;
	toPkt.mutable_actor()->CopyFrom(fromPkt.actor());

	// �� �ڵ带 ActorMove�� ������?
	// ��ε� ĳ����(���� ����)
	shared_ptr<SendBuffer> sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
	Room::Instance()->BroadcastWithoutMe(session->_player, sendBuffer);
	
	return true;
}

bool Handle_C_ATTACK(shared_ptr<ClientSession> session, PROTOCOL::C_ATTACK fromPkt)
{
	// Ŭ�󿡼� ���� ���� ������ ������ ������ �÷��̾� Ÿ�� �ۿ� ����.
	// ����� ��� -> hp ���� -> ��ε� ĳ����
	cout << "Player-" << session->_player->GetIndex() << " Attack" << endl;
	
	// Set To PACKET
	PROTOCOL::S_ATTACK toPkt;
	if (Room::Instance()->ActorAttack(fromPkt, toPkt)) {

		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
		Room::Instance()->Broadcast(sendBuffer);
	}

	return true;
}

bool Handle_C_CHAT(shared_ptr<ClientSession> session, PROTOCOL::C_CHAT fromPkt)
{
	// ���� ���������� ê ����� ����ٸ�..
	cout << "Player-" << session->_player->GetIndex() << " Chat" << endl;
	PROTOCOL::S_CHAT toPkt;
	uint64 id = session->_player->GetIndex();
	toPkt.mutable_actor()->set_index(id);
	toPkt.set_text(fromPkt.text());

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(toPkt);
	Room::Instance()->Broadcast(sendBuffer);

	return true;
}

