#pragma once


class IocpEvent;

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual void Dispatch(IocpEvent* iocpEvent, int len) abstract;
	virtual HANDLE GetHandle() abstract;
};

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	void Register(shared_ptr<IocpObject> iocpObject);
	void Dispatch();
public:
	HANDLE _iocpHandle;
};

