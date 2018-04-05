#pragma once
#include "BasePart.h"
#include "DirectX.h"
#include <list>

class Bullet : public BaseGameEntity
{
private:
	D3DXVECTOR2 startPos;	//��ʼλ��
	D3DXVECTOR2 targetPos;	//����λ��
	D3DXVECTOR2 dir;		//�ӵ�����

	//������ص�����
	D3DXVECTOR2 FramP1;
	D3DXVECTOR2 FramP2;
	D3DXVECTOR2* PaintPos = new D3DXVECTOR2[2];

	int owner;				//�ӵ���Դ
	float damage;			//�ӵ��˺�
	double deltaTime;		//�ӵ�����
	bool ended = false;		//�ж��Ƿ����

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



	//�ӿ�
	bool Ended() { return ended; }
	Bullet Instance() { return *this; }
};
