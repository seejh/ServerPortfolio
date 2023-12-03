#include "pch.h"
#include "Room.h"

#include"Player.h"

shared_ptr<Room> GRoom = make_shared<Room>();

void Room::Enter(shared_ptr<Player> player) {
	_players[player->playerId] = player;
}

void Room::Leave(shared_ptr<Player> player) {
	_players.erase(player->playerId);
}
