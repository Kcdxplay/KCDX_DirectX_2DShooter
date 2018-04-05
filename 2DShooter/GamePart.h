#pragma once

#include "BasePart.h"
#include "Telegram.h"

class Weapon:public BaseGameEntity
{
protected:
	float damage;		//武器伤害
	float bulletSpeed;	//子弹速度
	float fireRate;		//开火频率
	float accuracy;		//射击精度
	Graphic graph;		//图像模块

	float width;		//贴图的宽
	float height;		//贴图的高
	float gunLength;	//武器长度 用于计算枪口位置

	D3DXVECTOR2 rotateCenter;		//旋转的中心，握武器的位置
public:
	Weapon() {}
	Weapon(int id) :BaseGameEntity(id) {}

	virtual void LoadTexture()=0;
	virtual void Shoot();

	virtual void Update();
	virtual void Render();

	//为玩家渲染用的函数
	virtual void RenderForPlayer()=0;

	//设置武器位置
	virtual void SetPos(float x, float y)=0;

	virtual bool HandleMessage(const Telegram& msg)=0;

	//获取枪口位置
	D3DXVECTOR2 GetMuzzlePos();

	//大量接口
	float Damage() { return damage; }
	float BulletSpeed() { return bulletSpeed; }
	float FireRate() { return fireRate; }
	float Accuracy() { return accuracy; }
	
	float HandleX() { return rotateCenter.x; }
	float HandleY() { return rotateCenter.y; }

};

class Armor:public BaseGameEntity
{
	Armor(int id):BaseGameEntity(id) {}
};