#pragma once

// �������� ������ ���� Ǯ�ν� �Ҵ� �ް�, ����� ������ �˾Ƽ� �ݳ��ǰ�
// �ٸ� send�� ������ ���, �� �޸��� ó���� ���ؼ� ���
// shared_ptr�� �����Ǿ�� �Ѵ�.
class SendBuffer
{
public:
	SendBuffer(int size);
	~SendBuffer();

	char* Buffer() { return _buffer; }
	int Size() { return _size; }
public:
	char* _buffer;
	int _size;
};

