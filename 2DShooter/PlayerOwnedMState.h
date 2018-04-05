#pragma once

#include "Charcter.h"
#include "Player.h"
#include "Map.h"

class Charcter;

//ȫ��״̬
class PlayerGlobal : public MState<Charcter>
{
private:
	PlayerGlobal() {}

public:
	static PlayerGlobal* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};

//վ��״̬
class PlayerMStanding :public MState<Charcter>
{
private:
	PlayerMStanding() {}

public:
	static PlayerMStanding* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~PlayerMStanding() {}
};

//����״̬
class PlayerMWalking : public MState<Charcter>
{
private:
	PlayerMWalking() {}

public:
	static PlayerMWalking* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~PlayerMWalking() {}
};

//���״̬
class PlayerMDashing :public MState<Charcter>
{
private:

	PlayerMDashing() {}


public:
	static PlayerMDashing* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~PlayerMDashing() {}
};

//����״̬
class PlayerMFalling :public MState<Charcter>
{
private:
	PlayerMFalling() {}

public:
	static PlayerMFalling* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};