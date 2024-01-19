#include "pch.h"
#include "CoreGlobal.h"

#include"Memory.h"
#include"DBConnectionPool.h"

Memory* GMemory = new Memory();
DBConnectionPool* GDBConnectionPool = new DBConnectionPool();

class CoreGlobal {
public:
	CoreGlobal() {
		//GMemory = new Memory();
		//GDBConnectionPool = new DBConnectionPool();
	}

	~CoreGlobal() {
		delete GDBConnectionPool;
		delete GMemory;

	}
} g_global;