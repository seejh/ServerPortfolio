#pragma once

#include"Session.h"

class Player;
class ClientSession : public Session {
public:
	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnSend(int len) override;
	virtual void OnRecv(char* buffer, int len) override;
public:
	shared_ptr<Player> _player;
};

