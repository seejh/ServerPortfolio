#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer() : _size(1000), _readPos(0), _writePos(0)
{
	_buffer = new char[_size + 200];
}

RecvBuffer::~RecvBuffer()
{
	delete _buffer;
}

bool RecvBuffer::OnRead(int len)
{
	if (DataSize() < len)
		return false;

	_readPos += len;

	return true;
}

bool RecvBuffer::OnWrite(int len)
{
	if (FreeSize() < len) return false;

	_writePos += len;

	return true;
}

void RecvBuffer::Reset()
{
	if (_readPos == 0) return;

	if (_readPos == _writePos) {
		_readPos = _writePos = 0;
		return;
	}

	::memcpy(_buffer, &_buffer[_readPos], DataSize());

	_writePos -= _readPos;
	_readPos = 0;
}

char* RecvBuffer::BufferReadPos()
{
	return &_buffer[_readPos];
}

char* RecvBuffer::BufferWritePos()
{
	return &_buffer[_writePos];
}

int RecvBuffer::DataSize()
{
	return _writePos - _readPos;
}

int RecvBuffer::FreeSize()
{
	return _size - _writePos;
}
