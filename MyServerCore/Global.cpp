#include "pch.h"
#include "Global.h"

#include"Memory.h"
#include"DBConnectionPool.h"

Memory* GMemory = nullptr;
DBConnectionPool* GDBConnectionPool = nullptr;

class Global {
public:
	Global() {
		GMemory = new Memory();
		GDBConnectionPool = new DBConnectionPool();
	}

	~Global() {
		delete GMemory;
		delete GDBConnectionPool;
	}
} g_global;