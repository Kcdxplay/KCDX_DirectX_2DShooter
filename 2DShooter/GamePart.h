#pragma once

#include "BasePart.h"
#include "Telegram.h"

class Weapon:public BaseGameEntity
{
protected:
	float damage;		//�����˺�
	float bulletSpeed;	//�ӵ��ٶ�
	float fireRate;		//����Ƶ��
	float accuracy;		//�������
	Graphic graph;		//ͼ��ģ��

	float width;		//��ͼ�Ŀ�
	float height;		//��ͼ�ĸ�
	float gunLength;	//�������� ���ڼ���ǹ��λ��

	D3DXVECTOR2 rotateCenter;		//��ת�����ģ���������λ��
public:
	Weapon() {}
	Weapon(int id) :BaseGameEntity(id) {}

	virtual void LoadTexture()=0;
	virtual void Shoot();

	virtual void Update();
	virtual void Render();

	//Ϊ�����Ⱦ�õĺ���
	virtual void RenderForPlayer()=0;

	//��������λ��
	virtual void SetPos(float x, float y)=0;

	virtual bool HandleMessage(const Telegram& msg)=0;

	//��ȡǹ��λ��
	D3DXVECTOR2 GetMuzzlePos();

	//�����ӿ�
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