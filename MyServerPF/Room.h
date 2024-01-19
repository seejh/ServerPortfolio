#pragma once


#include"Protocol3.pb.h"

class ClientSession;
class Monster;
class Actor;
class Player;
class SendBuffer;
class Room
{
	Room(){}
	static Room* _instance;
public:
	static Room* Instance() {
		if (!_instance) 
			_instance = new Room();

		return _instance;
	}

	void PlayerEnter(shared_ptr<Player>& player, PROTOCOL::ACTOR& protocolActor);
	void PlayerLeave(shared_ptr<Player> player);
	void MonsterAdd(shared_ptr<Monster> monster);
	void MonsterRemove(shared_ptr<Monster> monster);
	
	void Broadcast(shared_ptr<SendBuffer> sendBuffer);
	void BroadcastWithoutMe(shared_ptr<Player> player, shared_ptr<SendBuffer> sendBuffer);
	void BroadcastWithoutLock(shared_ptr<SendBuffer> sendBuffer);

	bool GetPlayerList(PROTOCOL::S_PLAYERLIST& playerList);
	bool GetMonsterList(PROTOCOL::S_MONSTERLIST& monsterList);
	
	void ActorMove(PROTOCOL::ACTOR player);
	bool ActorAttack(PROTOCOL::C_ATTACK& fromPkt, PROTOCOL::S_ATTACK& toPkt);

	void Update();
private:
	shared_ptr<Actor> FindActorByProtoActor(PROTOCOL::ACTOR protoActor);
	
public:
	uint64 _lastUpdateTime = -1;

	map<uint64, shared_ptr<Player>> _players;
	map<uint64, shared_ptr<Monster>> _monsters;

	atomic<uint64> _indexGenerator;
	mutex _mutex;
};

