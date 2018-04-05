#pragma once
#include "BasePart.h"
#include "DirectX.h"
#include <list>

class Bullet : public BaseGameEntity
{
private:
	D3DXVECTOR2 startPos;	//开始位置
	D3DXVECTOR2 targetPos;	//结束位置
	D3DXVECTOR2 dir;		//子弹向量

	//绘制相关的向量
	D3DXVECTOR2 FramP1;
	D3DXVECTOR2 FramP2;
	D3DXVECTOR2* PaintPos = new D3DXVECTOR2[2];

	int owner;				//子弹来源
	float damage;			//子弹伤害
	double deltaTime;		//子弹射速
	bool ended = false;		//判断是否击中

public:
	Bullet();
	Bullet(int owner, D3DXVECTOR2 startPos, D3DXVECTOR2 endPos);
	Bullet(int owner, D3DXVECTOR2 startPos, D3DXVECTOR2 endPos, double deltaTime);
	~Bullet();

	void BulletEnd();
	void BulletEnd(RectCollision rc);

	RectCollision* FindClosestHit(list<RectCollision>* RC);

	virtual void Update();
	virtual void Render();



	bool HandleMessage(const Telegram& msg);

	bool operator==(const Bullet &bul)
	{
		return (&bul == this);
	}



	//接口
	bool Ended() { return ended; }
	Bullet Instance() { return *this; }
};
