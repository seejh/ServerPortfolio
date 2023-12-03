#pragma once

class ClientSession;

class Player
{
public:

public:
	int playerId = 0;
	shared_ptr<ClientSession> _ownerClientSession;
};

