#pragma once


class Player;
class Room
{
public:
	void Enter(shared_ptr<Player> player);
	void Leave(shared_ptr<Player> player);
public:
	map<int, shared_ptr<Player>> _players;
};

extern shared_ptr<Room> GRoom;