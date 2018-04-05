#pragma once

#include "AState.h"
#include "Map.h"

class Charcter;

class EnemyAWalkAround :public AState<Charcter>
{
private:
	EnemyAWalkAround() {}

public:
	static EnemyAWalkAround* Instance();
	virtual void Enter(Charcter* pCharcter);
	virtual void Execute(Charcter* pCharcter);
	virtual void Exit(Charcter* pCharcter);

	virtual bool OnMessage(Charcter* pCharcter, const Telegram& msg);

	virtual ~EnemyAWalkAround() {}
};