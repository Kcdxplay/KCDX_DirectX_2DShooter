#pragma once

#include <list>
#include "BasePart.h"

#define MAP Map::Instance()

class Map : public BaseGameEntity
{
private:
	Graphic graphic;
	D3DXIMAGE_INFO info;

	list<RECT> Walls;
public:
	Map() {}

	//��ȡ��ͼʵ�����
	static Map* Instance();

	virtual void Update();
	virtual void Render();

	bool HandleMessage(const Telegram& msg);

	//��ȡ��ͼ��ͼ
	void LoadTexture(wstring file, D3DCOLOR color);
	//��һ��ǽ
	void AddOneWall(long left, long top, long right, long bottom);
	//���õ�ͼλ��
	void SetPos(double x, double y);

	//virtual bool OnMessage(Map* agent, const Telegram& msg);

	
	//����������Ʒ�����λ��
	void GetPaintPos(double mapPosX, double mapPosY, float* x, float* y);
	//������Եĵ�ͼ����λ��
	void GetMapPos(double paintPosX, double paintPosY, float* x, float* y);
	//����Ƿ���ǽ������ײ
	bool CheckWallCollision(RECT rect, RECT* wall = NULL);
	//����ӵ���ײ,����������ײǽ��
	bool CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2,list<RectCollision>* RC);
	//����ӵ���ײ������㷵��
	bool CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2, D3DXVECTOR2* contactPoint);

	//װ���ܿ��ƾ�ͷ2333
	void MoveToRight(double amount)
	{
		graphic.paintPos.x -= amount;
	}
	void MoveToLeft(double amount)
	{
		graphic.paintPos.x += amount;
	}
	void MoveToUp(double amount)
	{
		graphic.paintPos.y += amount;
	}
	void MoveToDown(double amount)
	{
		graphic.paintPos.y -= amount;
	}
};