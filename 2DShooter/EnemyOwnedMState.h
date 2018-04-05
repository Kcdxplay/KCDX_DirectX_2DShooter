#pragma once

#include "Charcter.h"
#include "Map.h"

//ȫ��״̬
class EnemyMGloable :public MState<Charcter>
{
private:
	EnemyMGloable() {}

public:
	static EnemyMGloable* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};

//վ��״̬
class EnemyMStanding :public MState<Charcter>
{
private:
	EnemyMStanding() {}

public:
	static EnemyMStanding* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};

//��������
class EnemyMWalkLeft :public MState<Charcter>
{
private:
	EnemyMWalkLeft() {}

public:
	static EnemyMWalkLeft* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};

//��������
class EnemyMWalkRight :public MState<Charcter>
{
private:
	EnemyMWalkRight() {}

public:
	static EnemyMWalkRight* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};

class EnemyMFalling :public MState<Charcter>
{
private:
	EnemyMFalling() {}

public:
	static EnemyMFalling* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);
};