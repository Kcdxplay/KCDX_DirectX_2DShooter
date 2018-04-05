#pragma once

#include "Charcter.h"

class PlayerMStanding;

class Player : public Charcter
{
public:
	LARGE_INTEGER tWalkStart, tWalkEnd, tFrequency;//行走的时间计时
	double tWalking;	//行走时间长度
	bool Walk2Long;//走了很久吗

	Player() {}
	Player(int id):Charcter(id)
	{
		pMStateMachine = new MStateMachine<Charcter>(this);
		//pMStateMachine->SetGlobalState();
		pMStateMachine->SetCurrentState(MStanding::Instance());

		pWeapon = new WP_ChargeRifle();
	}

	//消息处理
	virtual bool HandleMessage(const Telegram& msg);

	//更新状态
	virtual void Update();
	virtual void Render();

	MStateMachine<Charcter>* GetMotionFSM()const { return this->pMStateMachine; }

	void KeyCheck();	//检测按键
	void SetTowards(bool towards);
	void Walk();
	void Dash();
	void Jump();
	void Shoot();
};