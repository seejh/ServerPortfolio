#pragma once

#include<iostream>
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<WinSock2.h>
#include<MSWSock.h>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include<thread>
#include<mutex>
#include<atomic>
#include<chrono>

#include<functional>
#include<string>

#include<set>
#include<vector>
#include<queue>
#include<concurrent_queue.h>

#include<conio.h>

//#include"MyEnum.pb.h"
//#include"MyProtocol.pb.h"
//#include"MyStruct.pb.h"

using namespace std;

#include"NetUtils.h"
#include"CoreGlobal.h"
#include"Memory.h"




/// MACRO

#define CRASH(cause){					\
	unsigned int* crash = nullptr;		\
	__analysis_assume(crash != nullptr);\
	*crash = 0xDEADBEEF;				\
}

#define ASSERT_CRASH(expr){		\
	if (!(expr)) {				\
		CRASH("ASSERT_CRASH");	\
		__analysis_assume(expr);\
	}							\
}

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#define size32(val) static_cast<int32>(sizeof(val))