#pragma once

class ClientSession;
class SessionManager
{
	SessionManager() {}

public:
	static SessionManager* Instance() {
		if (!_instance) {
			_instance = new SessionManager();
		}

		return _instance;
	}

	void AddSession(shared_ptr<ClientSession> session);
	void RemoveSession(shared_ptr<ClientSession> session);

private:
	static SessionManager* _instance;

	mutex _mutex;
	set<shared_ptr<ClientSession>> _sessions;
};

