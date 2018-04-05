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

	//获取地图实例句柄
	static Map* Instance();

	virtual void Update();
	virtual void Render();

	bool HandleMessage(const Telegram& msg);

	//读取地图贴图
	void LoadTexture(wstring file, D3DCOLOR color);
	//加一堵墙
	void AddOneWall(long left, long top, long right, long bottom);
	//设置地图位置
	void SetPos(double x, double y);

	//virtual bool OnMessage(Map* agent, const Telegram& msg);

	
	//更新其他物品的相对位置
	void GetPaintPos(double mapPosX, double mapPosY, float* x, float* y);
	//计算相对的地图绝对位置
	void GetMapPos(double paintPosX, double paintPosY, float* x, float* y);
	//检测是否与墙体有碰撞
	bool CheckWallCollision(RECT rect, RECT* wall = NULL);
	//检测子弹碰撞,返回所有碰撞墙体
	bool CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2,list<RectCollision>* RC);
	//检测子弹碰撞，带落点返回
	bool CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2, D3DXVECTOR2* contactPoint);

	//装作能控制镜头2333
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