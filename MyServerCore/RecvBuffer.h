#pragma once

class RecvBuffer
{
public:
	RecvBuffer();
	~RecvBuffer();

	bool OnRead(int len);
	bool OnWrite(int len);
	void Reset();

	char* BufferReadPos();
	char* BufferWritePos();

	int DataSize();
	int FreeSize();
public:
	char* _buffer;
	int _size;
	int _readPos;
	int _writePos;
};

