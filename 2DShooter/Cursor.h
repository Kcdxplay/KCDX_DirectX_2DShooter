#pragma once
#include "DirectX.h"

//更美好的生活HooHooHoo
#define Mouse Cursor::Instance()

class Cursor
{
private:
	D3DXVECTOR2 MapPos;
	D3DXVECTOR2 PaintPos;
	POINT mousePoint;
	
	Cursor() {}


public:
	static Cursor* Instance();
	void Update(RECT windowRect);
	void Render();

	float GetMapPosX() { return MapPos.x; }
	float GetMapPosY() { return MapPos.y; }
	float GetPaintPosX() { return PaintPos.x; }
	float GetPaintPosY() { return PaintPos.y; }
};