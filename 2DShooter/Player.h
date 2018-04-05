#pragma once

#include "Charcter.h"

class PlayerMStanding;

class Player : public Charcter
{
public:
	LARGE_INTEGER tWalkStart, tWalkEnd, tFrequency;//���ߵ�ʱ���ʱ
	double tWalking;	//����ʱ�䳤��
	bool Walk2Long;//���˺ܾ���

	Player() {}
	Player(int id):Charcter(id)
	{
		pMStateMachine = new MStateMachine<Charcter>(this);
		//pMStateMachine->SetGlobalState();
		pMStateMachine->SetCurrentState(MStanding::Instance());

		pWeapon = new WP_ChargeRifle();
	}

	//��Ϣ����
	virtual bool HandleMessage(const Telegram& msg);

	//����״̬
	virtual void Update();
	virtual void Render();

	MStateMachine<Charcter>* GetMotionFSM()const { return this->pMStateMachine; }

	void KeyCheck();	//��ⰴ��
	void SetTowards(bool towards);
	void Walk();
	void Dash();
	void Jump();
	void Shoot();
};