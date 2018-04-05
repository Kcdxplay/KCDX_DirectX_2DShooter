#pragma once

#include "MState.h"

class Charcter;

//È«¾ÖÅÐ¶Ï×´Ì¬
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

//Õ¾Á¢×´Ì¬
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

//ÐÐ×ß×´Ì¬
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

//³å´Ì×´Ì¬
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

//µôÂä×´Ì¬
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
