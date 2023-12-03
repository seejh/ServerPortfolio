#pragma once
#include<sql.h>
#include<sqlext.h>

enum {
	WVARCHAR_MAX = 4000,
	BINARY_MAX = 8000
};

class DBConnection
{
public:
	// ���������� DB�� Ŀ��Ʈ �ϴ� �Լ�
	bool Connect(SQLHENV henv, const WCHAR* connectionString);
	void Clear();

	// SQL query ����
	bool Execute(const WCHAR* query);
	// �����Ͱ� ������ �޾ƿ��ڴ�.
	bool Fetch();
	// �����͸� ��� �޾ƿԴ���
	int32 GetRowCount();
	// statement�� ���ε�� ���� ����
	void Unbind();

public:

	// ���� �Ʒ� �ΰ��� �ߴµ� �޾ƿ� �� ���� Ÿ�Ե��� �����ִ°� ����
	// SQL�� signed int�ۿ� ����, bool�� ���� �� int8 ���
	bool BindParam(int32 paramIndex, bool* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, float* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, double* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int8* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int16* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int32* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, int64* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindParam(int32 paramIndex, const WCHAR* str, SQLLEN* index);
	bool BindParam(int32 paramIndex, const BYTE* bin, int32 size, SQLLEN* index);

	bool BindCol(int32 columnIndex, bool* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, float* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, double* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int8* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int16* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int32* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, int64* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool BindCol(int32 columnIndex, WCHAR* str, int32 size, SQLLEN* index);
	bool BindCol(int32 columnIndex, BYTE* bin, int32 size, SQLLEN* index);

private:
	// ������ ������ �� ������ ���� ���ε�
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT cType, SQLSMALLINT sqlType, SQLULEN len, SQLPOINTER ptr, SQLLEN* index);

	// ������ ������ �� ���� ���� ���ε�
	bool BindCol(SQLUSMALLINT columnIndex, SQLSMALLINT cType, SQLULEN len, SQLPOINTER value, SQLLEN* index);

	void HandleError(SQLRETURN ret);

private:
	// ������ DB Ŀ�ؼ��� ����ϴ� �ڵ�
	SQLHDBC _connection = SQL_NULL_HANDLE;
	// SQL ���� ���ڸ� ���
	SQLHSTMT _statement = SQL_NULL_HANDLE;
};

