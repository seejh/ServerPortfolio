#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool() {}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}
// ���� ���� �� Ǯ�� �ִ� Ŀ�ؼǵ� �� DB�� Ŀ�� �س���
bool DBConnectionPool::Connect(int32 connectionCount, const WCHAR* connectionString)
{
	lock_guard<mutex> _lock(_mutex);

	if (::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_environment) != SQL_SUCCESS)
		return false;

	// sql odbc3����
	if (::SQLSetEnvAttr(_environment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS)
		return false;

	// Ŀ�ؼ� ī��Ʈ�� ������ ���� ��ŭ
	for (int32 i = 0; i < connectionCount; i++) {
		DBConnection* connection = xnew<DBConnection>();
		if (connection->Connect(_environment, connectionString) == false)
			return false;

		_connections.push_back(connection);
	}

	return true;
}

void DBConnectionPool::Clear()
{
	lock_guard<mutex> _lock(_mutex);

	if (_environment != SQL_NULL_HANDLE) {
		::SQLFreeHandle(SQL_HANDLE_ENV, _environment);
		_environment = SQL_NULL_HANDLE;
	}

	for (DBConnection* connection : _connections)
		xdelete(connection);

	_connections.clear();
}
// Ŀ�ؼ� �������� ������ nullptr, ������ �ѱ�
DBConnection* DBConnectionPool::Pop()
{
	lock_guard<mutex> _lock(_mutex);

	if (_connections.empty())
		return nullptr;

	DBConnection* connection = _connections.back();
	_connections.pop_back();

	return connection;
}
// Ŀ�ؼ� �ݳ�
void DBConnectionPool::Push(DBConnection* connection)
{
	lock_guard<mutex> _lock(_mutex);

	_connections.push_back(connection);
}


