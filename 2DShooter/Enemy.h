#pragma once

#include "Charcter.h"
#include "AStateMachine.h"
#include "EnityManager.h"
#include "EnemyOwnedAState.h"
#include "EnemyOwnedMState.h"

#define lEnemy EnemyList::Instance()->listOfEnemy
#define ENM EnemyList::Instance()

class Enemy;

class EnemyList
{
private:
	int EID = 100;

	EnemyList() {}
public:
	static EnemyList* Instance();
	list<Enemy*> listOfEnemy;
	list<Enemy*> listOfRemove;

	void Update();

	void AddOneEnemy(float x,float y,int type=1);
	void AddOneWalkEnemy(float x, float y, float map1, float map2, int type = 1);
};

class Enemy : public Charcter
{
private:
	AStateMachine<Charcter>* pAStateMachine;
	float Area[2];	//Ѳ������	[0]Ϊ��࣬[1]Ϊ�Ҳ�

public:
	Enemy() {}
	Enemy(int id) :Charcter(id) 
	{
		pMStateMachine = new MStateMachine<Charcter>(this);
		pMStateMachine->SetGlobalState(EnemyMGloable::Instance());
		pMStateMachine->SetCurrentState(EnemyMStanding::Instance());

		pAStateMachine = new AStateMachine<Charcter>(this);
		//pAStateMachine->SetCurrentState(EnemyAWalkAround::Instance());
	}

	//��Ϣ����
	virtual bool HandleMessage(const Telegram& msg);

	//����״̬
	virtual void Update();
	virtual void Render();

	//�ӿ�
	MStateMachine<Charcter>* GetMotionFSM()const { return this->pMStateMachine; }
	AStateMachine<Charcter>* GetAIFSM()const { return this->pAStateMachine; }

	void SetAreaLeft(float a) { Area[0] = a; }
	void SetAreaRight(float a) { Area[1] = a; }
	float AreaLeft() { return Area[0]; }
	float AreaRight() { return Area[1]; }
};