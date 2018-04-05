#pragma once

#include "BasePart.h"
#include "GamePart.h"
#include "Weapon.h"
#include "CharcterOwnedMState.h"
#include "CharcterDetailData.h"
#include "MStateMachine.h"
#include "AStateMachine.h"
#include "Bullet.h"
#include "Cursor.h"

#include <list>

class Charcter : public BaseGameEntity
{
protected:
	MStateMachine<Charcter>* pMStateMachine;
	CharcterDetailData data;
	Weapon* pWeapon;
	//Armor  pArmor;

	Graphic graph;

	RECT rect;			//��ɫ�������
	RECT preCheck[3];	//��ɫ��Χ��Ԥ��ײ��Χ 0-���10���أ�1-�Ҳ�10���أ�2-�²�10����

	list<Bullet> bullets;//��ɫ��һ����ӵ�>:3
	float health;	//����ֵ
public:

	Charcter() {}
	Charcter(int id):BaseGameEntity(id)
	{
		pMStateMachine = new MStateMachine<Charcter>(this);
		pMStateMachine->SetGlobalState(MGlobalChecking::Instance());
		pMStateMachine->SetCurrentState(MStanding::Instance());
	}

	//type:1-��ͨ 2-�߻��� 3-�ؼ�
	void BootUp(float x, float y, int type = 1);
	void SetPos(float x, float y);
	void SetHealth(float health);

	//��ȡ��ͼ
	void LoadTexture(wstring file, D3DCOLOR color=NULL);
	void LoadTexture(wstring file, float framW, float framH, D3DCOLOR color = NULL);

	void SetTowards(bool towards);
	void GotHited(float damage);
	
	//�����ܱ߾��󣬰������������ײ������
	void RectSet();
	//��ȡʵ�屾�����
	RECT GetMainRect();
	//��ȡ��ײ�жϾ���	0-���10���أ�1-�Ҳ�10���أ�2-�²�10����
	RECT GetPreCheckRect(int num);

	//������ϸ����ʵ��
	CharcterDetailData* GetDetailData();
	Graphic* GetGraphic();
	list<Bullet>* Bullets();
	float Health();

	//��Ϣ����
	virtual bool HandleMessage(const Telegram& msg);

	//����״̬
	virtual void Update();
	virtual void Render();

	MStateMachine<Charcter>* GetMotionFSM()const { return pMStateMachine; }
};

class C_Normal :public CharcterTypeSet<Charcter>
{
private:
	C_Normal() {}

public:
	static C_Normal* Instance();
	virtual void SetCharcterData(Charcter* pCharcter);
};

class C_Fast : public CharcterTypeSet<Charcter>
{
private:
	C_Fast() {}

public:
	static C_Fast* Instance();
	virtual void SetCharcterData(Charcter* pCharcter);
};

class C_Heavy :public CharcterTypeSet<Charcter>
{
private:
	C_Heavy() {}

public:
	static C_Heavy* Instance();
	virtual void SetCharcterData(Charcter* pCharcter);
};