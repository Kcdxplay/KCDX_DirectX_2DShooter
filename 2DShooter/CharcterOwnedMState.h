#pragma once

#include "MState.h"

class Charcter;

//ȫ���ж�״̬
class MGlobalChecking :public MState<Charcter>
{
private:
	MGlobalChecking() {}

public:
	static MGlobalChecking* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~MGlobalChecking() {}
};

//վ��״̬
class MStanding :public MState<Charcter>
{
private:
	MStanding() {}

public:
	static MStanding* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~MStanding() {}
};

//����״̬
class MWalking : public MState<Charcter>
{
private:
	MWalking() {}

public:
	static MWalking* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~MWalking() {}
};

//���״̬
class MDashing :public MState<Charcter>
{
private:
	
	MDashing() {}
	

public:
	static MDashing* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~MDashing() {}
};

//����״̬
class MFalling :public MState<Charcter>
{
private:
	MFalling() {}

public:
	static MFalling* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};
