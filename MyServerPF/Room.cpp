#include "pch.h"
#include "Room.h"

#include"Actor.h"
#include"ClientSession.h"
#include"ClientPacketHandler.h"

Room* Room::_instance = nullptr;

void Room::PlayerEnter(shared_ptr<Player>& player, PROTOCOL::ACTOR& protocolActor)
{
	lock_guard<mutex> _lock(_mutex);
	
	uint64 playerIndex = player->_index;
	
	// 없으면 컨테이너에 새로 만들어 저장<uint, Player>
	auto it = _players.find(playerIndex);
	if (it == _players.end()) {
		// 플레이어 리스트에 추가(룸 진입)
		_players[playerIndex] = player;

		// 플레이어 정보 스택에서 임의로 생성(TODO : DB에서 종료 시 저장되는 데이터 가져오기)
		player->SetLocation(0, 0, 112.000687f);
		player->SetRotation(0, 0, 0);
		player->SetHP(100);
		player->SetLogin(true);
		player->SetAlive(true);

		// Set ToPACKET
		protocolActor.set_index(player->GetIndex());
		protocolActor.set_locationx(player->GetLocation()._x);
		protocolActor.set_locationy(player->GetLocation()._y);
		protocolActor.set_locationz(player->GetLocation()._z);
		protocolActor.set_rotationyaw(player->GetRotation()._yaw);
		protocolActor.set_rotationpitch(player->GetRotation()._pitch);
		protocolActor.set_rotationroll(player->GetRotation()._roll);
		protocolActor.set_hp(player->GetHP());
	}
}

void Room::PlayerLeave(shared_ptr<Player> player)
{
	lock_guard<mutex> _lock(_mutex);
	
	// 나가는 사람 index
	uint64 playerId = player->GetIndex();
	
	// 해당 index 찾아서 제거
	auto it = _players.find(playerId);
	if (it != _players.end()) 
		_players.erase(playerId);
}

void Room::MonsterAdd(shared_ptr<Monster> monster)
{
	lock_guard<mutex> lock(_mutex);

	_monsters[monster->GetIndex()] = monster;
}

void Room::MonsterRemove(shared_ptr<Monster> monster)
{
	lock_guard<mutex> lock(_mutex);

	uint64 monsterId = monster->GetIndex();

	auto it = _monsters.find(monsterId);
	if (it != _monsters.end())
		_monsters.erase(monsterId);
}

void Room::Broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	lock_guard<mutex> lock(_mutex);

	map<uint64, shared_ptr<Player>>::iterator it;
	for (it = _players.begin(); it != _players.end(); it++) {
		it->second->_ownerSession->Send(sendBuffer);
	}
}

void Room::BroadcastWithoutMe(shared_ptr<Player> player, shared_ptr<SendBuffer> sendBuffer)
{
	lock_guard<mutex> lock(_mutex);

	// 브로드캐스팅할 건데
	map<uint64, shared_ptr<Player>>::iterator it;
	for (it = _players.begin(); it != _players.end(); it++) {
		// 자기 자신이면 제외
		if (it->second->_index == player->_index)
			continue;

		// Send
		it->second->_ownerSession->Send(sendBuffer);
	}
}

bool Room::GetPlayerList(PROTOCOL::S_PLAYERLIST& playerList)
{
	lock_guard<mutex> lock(_mutex);

	// 리스트 for 돌려서
	map<uint64, shared_ptr<Player>>::iterator it;
	for (it = _players.begin(); it != _players.end(); it++) {
		shared_ptr<Player>& tmpPlayer = it->second;

		// 해당 정보 프로토콜에 담음
		PROTOCOL::ACTOR* protocolActor = playerList.add_actors();
		protocolActor->set_index(tmpPlayer->_index);
		protocolActor->set_locationx(tmpPlayer->GetLocation()._x);
		protocolActor->set_locationy(tmpPlayer->GetLocation()._y);
		protocolActor->set_locationz(tmpPlayer->GetLocation()._z);
		protocolActor->set_rotationyaw(tmpPlayer->GetRotation()._yaw);
		protocolActor->set_rotationpitch(tmpPlayer->GetRotation()._pitch);
		protocolActor->set_rotationroll(tmpPlayer->GetRotation()._roll);
		protocolActor->set_hp(tmpPlayer->GetHP());
	}

	return true;
}

bool Room::GetMonsterList(PROTOCOL::S_MONSTERLIST& monsterList)
{
	lock_guard<mutex> lock(_mutex);

	map<uint64, shared_ptr<Monster>>::iterator it;
	for (it = _monsters.begin(); it != _monsters.end(); it++) {
		shared_ptr<Monster>& tmpMonster = it->second;

		PROTOCOL::ACTOR* protocolActor = monsterList.add_actors();
		protocolActor->set_index(tmpMonster->GetIndex());
		protocolActor->set_locationx(tmpMonster->GetLocation()._x);
		protocolActor->set_locationy(tmpMonster->GetLocation()._y);
		protocolActor->set_locationz(tmpMonster->GetLocation()._z);
		protocolActor->set_rotationyaw(tmpMonster->GetRotation()._yaw);
		protocolActor->set_rotationpitch(tmpMonster->GetRotation()._pitch);
		protocolActor->set_rotationroll(tmpMonster->GetRotation()._roll);
		protocolActor->set_hp(tmpMonster->GetHP());
	}

	return true;
}

void Room::ActorMove(PROTOCOL::ACTOR actor)
{
	lock_guard<mutex> lock(_mutex);

	// 플레이어
	if (actor.actortype() == PROTOCOL::PLAYER) {
		// 찾아서
		auto it = _players.find(actor.index());
		if (it != _players.end()) {
			// 이동
			it->second->SetLocation(actor.locationx(), actor.locationy(), actor.locationz());
			it->second->SetRotation(actor.rotationyaw(), actor.rotationpitch(), actor.rotationroll());
			it->second->SetVelocity(actor.velocityx(), actor.velocityy(), actor.velocityz());
		}
	}

	// 몬스터
	else {
		auto it = _monsters.find(actor.index());
		if (it != _monsters.end()) {
			// 이동
			it->second->SetLocation(actor.locationx(), actor.locationy(), actor.locationz());
		}
	}
}

bool Room::ActorAttack(PROTOCOL::C_ATTACK& fromPkt, PROTOCOL::S_ATTACK& toPkt)
{
	lock_guard<mutex> lock(_mutex);

	// Attacker &  damage
	toPkt.mutable_attacker()->CopyFrom(fromPkt.attacker());
	shared_ptr<Actor> attackActor = FindActorByProtoActor(toPkt.attacker());
	toPkt.mutable_attacker()->set_rotationyaw(attackActor->GetRotation()._yaw);
	int damage = attackActor->GetDamage();
	
	// Victims
	for (int i = 0; i < fromPkt.victims_size(); i++) {
		shared_ptr<Actor> actor = FindActorByProtoActor(fromPkt.victims(i));

		int attackedHP = actor->GetHP() - damage;
		actor->SetHP(attackedHP);

		PROTOCOL::ACTOR* protoActor = toPkt.add_victims();
		protoActor->set_index(actor->GetIndex());
		protoActor->set_hp(attackedHP);

		if (actor->GetActorType() == ActorType::PLAYER)
			protoActor->set_actortype(PROTOCOL::PLAYER);
		else
			protoActor->set_actortype(PROTOCOL::MONSTER);
	}

	return true;
}

void Room::Update()
{
	// 락을 걸고
	lock_guard<mutex> lock(_mutex);

	// deltaTime
	uint64 now = GetTickCount64();
	float deltaTime = float(now - _lastUpdateTime) / 1000.f;
	_lastUpdateTime = now;

	// monster update
	map<uint64, shared_ptr<Monster>>::iterator it;
	for (it = _monsters.begin(); it != _monsters.end(); it++) {
		it->second->Update(deltaTime);
	}
}


shared_ptr<Actor> Room::FindActorByProtoActor(PROTOCOL::ACTOR protoActor)
{
	//lock_guard<mutex> lock(_mutex);

	if (protoActor.actortype() == PROTOCOL::PLAYER) {
		auto it = _players.find(protoActor.index());
		if (it != _players.end()) 
			return it->second;
	}

	else {
		auto it = _monsters.find(protoActor.index());
		if (it != _monsters.end()) 
			return it->second;
	}

	return nullptr;
}



void Room::BroadcastWithoutLock(shared_ptr<SendBuffer> sendBuffer)
{
	map<uint64, shared_ptr<Player>>::iterator it;
	for (it = _players.begin(); it != _players.end(); it++) {
		it->second->_ownerSession->Send(sendBuffer);
	}
}



