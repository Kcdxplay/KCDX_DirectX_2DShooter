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

	RECT rect;			//角色本体矩阵
	RECT preCheck[3];	//角色周围的预碰撞范围 0-左侧10像素，1-右侧10像素，2-下侧10像素

	list<Bullet> bullets;//角色的一大堆子弹>:3
	float health;	//生命值
public:

	Charcter() {}
	Charcter(int id):BaseGameEntity(id)
	{
		pMStateMachine = new MStateMachine<Charcter>(this);
		pMStateMachine->SetGlobalState(MGlobalChecking::Instance());
		pMStateMachine->SetCurrentState(MStanding::Instance());
	}

	//type:1-普通 2-高机动 3-重甲
	void BootUp(float x, float y, int type = 1);
	void SetPos(float x, float y);
	void SetHealth(float health);

	//读取贴图
	void LoadTexture(wstring file, D3DCOLOR color=NULL);
	void LoadTexture(wstring file, float framW, float framH, D3DCOLOR color = NULL);

	void SetTowards(bool towards);
	void GotHited(float damage);
	
	//配置周边矩阵，包括自身矩阵，碰撞检测矩阵
	void RectSet();
	//获取实体本体矩阵
	RECT GetMainRect();
	//获取碰撞判断矩阵	0-左侧10像素，1-右侧10像素，2-下侧10像素
	RECT GetPreCheckRect(int num);

	//返回详细数据实例
	CharcterDetailData* GetDetailData();
	Graphic* GetGraphic();
	list<Bullet>* Bullets();
	float Health();

	//消息处理
	virtual bool HandleMessage(const Telegram& msg);

	//更新状态
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