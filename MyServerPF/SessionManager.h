#pragma once

#include"Session.h"

class Player;

class ClientSession : public Session {
public:
    // override
    virtual void OnConnected() {}
    virtual void OnDisconnected() {}
    virtual void OnSend(int sendLen) {}
    virtual void OnRecv(char* buffer, int recvLen);

public:
    shared_ptr<Player> _player;
};


/*---------------------------
    SessionManager
-------------------------*/
class SessionManager {
public:
    void AddSession(shared_ptr<ClientSession> clientSession);
    void RemoveSession(shared_ptr<ClientSession> clientSession);

public:
    mutex _mutex;
    set<shared_ptr<ClientSession>> _clientSessions;
};