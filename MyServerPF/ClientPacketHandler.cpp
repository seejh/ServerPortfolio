#include "pch.h"
#include "ClientPacketHandler.h"

#include"Room.h"
#include"DBConnectionPool.h"

function<bool(shared_ptr<ClientSession>, char*, int)> GPacketHandler[PacketCount];

bool Handle_INVALID(shared_ptr<ClientSession> session, char* buffer, int len)
{
	return false;
}

bool Handle_C_LOGIN(shared_ptr<ClientSession> session, PROTOCOL::C_LOGIN pkt)
{
	DBConnection* dbConn = GDBConnectionPool->Pop();
	dbConn->Unbind();

	// Query
	wstring playerID(L"see");
	SQLLEN playerIdLen = 0;
	dbConn->BindParam(1, playerID.c_str(), &playerIdLen);

	// 
	int32 outId = 0;
	SQLLEN outIdLen = 0;
	ASSERT_CRASH(dbConn->BindCol(1, &outId, &outIdLen));

	WCHAR outPlayerId[100];
	SQLLEN outPlayerIdLen = 0;
	ASSERT_CRASH(dbConn->BindCol(2, outPlayerId, sizeof(outPlayerId) / sizeof(WCHAR), &outPlayerIdLen));

	WCHAR outPlayerPw[100];
	SQLLEN outPlayerPwLen = 0;
	ASSERT_CRASH(dbConn->BindCol(3, outPlayerId, sizeof(outPlayerPw) / sizeof(WCHAR), &outPlayerPwLen));

	int32 outWin = 0;
	SQLLEN outWinLen = 0;
	ASSERT_CRASH(dbConn->BindCol(4, &outWin, &outWinLen));

	int32 outLose = 0;
	SQLLEN outLoseLen = 0;
	ASSERT_CRASH(dbConn->BindCol(5, &outLose, &outLoseLen));

	// Execute Query
	ASSERT_CRASH(dbConn->Execute(L"SELECT id, playerId, playerPw, win, lose FROM [dbo].[Player] WHERE playerId = (?)"));

	while (dbConn->Fetch()) {
		
	}

	return true;
}

bool Handle_C_ENTER_ROOM(shared_ptr<ClientSession> session, PROTOCOL::C_ENTER_ROOM pkt)
{
	
	return true;
}
