#pragma once



#ifdef _DEBUG
#pragma comment(lib, "Debug\\MyServerCore.lib")
#pragma comment(lib, "libprotobufd.lib")
#else
#pragma comment(lib, "Release\\MyServerCore.lib")
//#pragma comment(lib, "Protobuf\\Release\\libprotobuf .lib")
#endif

#include"CorePch.h"
#include<map>
