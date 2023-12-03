// MyServerPF.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include"pch.h"
#include"NetService.h"

#include"SessionManager.h"
#include"DBConnectionPool.h";

void DBSetting() {
    // create DB
    ASSERT_CRASH(GDBConnectionPool->Connect(1, L"Driver={SQL Server Native Client 11.0};Server=(localdb)\\MSSQLLocalDB;Database=MyDB;Trusted_Connection=Yes;"));
    auto query = L"										    \
			DROP TABLE IF EXISTS [dbo].[Player];			\
			CREATE TABLE[dbo].[Player]						\
			(												\
				[id] INT NOT NULL PRIMARY KEY IDENTITY,		\
                [playerId] NVARCHAR(20) NULL,               \
                [playerPw] NVARCHAR(20) NULL,               \
				[win] INT NULL,								\
                [lose] INT NULL                             \
			);";
    DBConnection* dbConn = GDBConnectionPool->Pop();
    ASSERT_CRASH(dbConn->Execute(query));
    GDBConnectionPool->Push(dbConn);

    // Add Player Data 1
    // Query
    {
        WCHAR name[100] = L"see";
        SQLLEN nameLen = 0;

        WCHAR pw[100] = L"asd123";
        SQLLEN pwLen = 0;

        int32 winCount = 10;
        SQLLEN winCountLen = 0;

        int32 loseCount = 20;
        SQLLEN loseCountLen = 0;

        ASSERT_CRASH(dbConn->BindParam(1, name, &nameLen));
        ASSERT_CRASH(dbConn->BindParam(2, pw, &pwLen));
        ASSERT_CRASH(dbConn->BindParam(3, &winCount, &winCountLen));
        ASSERT_CRASH(dbConn->BindParam(4, &loseCount, &loseCountLen));

        // Execute Query
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Player]([playerId], [playerPw], [win], [lose]) VALUES(?, ?, ?, ?)"));
        GDBConnectionPool->Push(dbConn);
    }

    // Add Player Data 2
    // Query
    {
        WCHAR name[100] = L"lee";
        SQLLEN nameLen = 0;

        WCHAR pw[100] = L"asd123";
        SQLLEN pwLen = 0;

        int32 winCount = 50;
        SQLLEN winCountLen = 0;

        int32 loseCount = 60;
        SQLLEN loseCountLen = 0;

        ASSERT_CRASH(dbConn->BindParam(1, name, &nameLen));
        ASSERT_CRASH(dbConn->BindParam(2, pw, &pwLen));
        ASSERT_CRASH(dbConn->BindParam(3, &winCount, &winCountLen));
        ASSERT_CRASH(dbConn->BindParam(4, &loseCount, &loseCountLen));

        // Execute Query
        ASSERT_CRASH(dbConn->Execute(L"INSERT INTO [dbo].[Player]([playerId], [playerPw], [win], [lose]) VALUES(?, ?, ?, ?)"));
        GDBConnectionPool->Push(dbConn);
    }
}

int main()
{
    DBSetting();

    // MAIN
    NetService* service = new NetService(make_shared<ClientSession>);
    service->Init();

    while (true) {
        service->_iocpCore->Dispatch();
    }
}
