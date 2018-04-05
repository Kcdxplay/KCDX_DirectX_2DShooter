#include "DirectX.h"
#include "Map.h"
#include "Tools.h"



void Map::Update()
{

}
void Map::Render()
{
	spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
	spriteOBJ->Draw(graphic.texture, NULL, NULL, &graphic.paintPos, D3DCOLOR_XRGB(255, 255, 255));
	spriteOBJ->End();
}
bool Map::HandleMessage(const Telegram & msg)
{
	return false;
}

//��ȡ��ͼ��ͼ
void Map::LoadTexture(wstring file, D3DCOLOR color)
{
	graphic.texture = LoadTextureWithInfo(file, color, &this->info);
}

//��һ��ǽ
void Map::AddOneWall(long left, long top, long right, long bottom)
{
	RECT rect = { left,top,right,bottom };

	Walls.push_front(rect);
}

//���õ�ͼλ��
void Map::SetPos(double x, double y)
{
	graphic.paintPos.x = x;
	graphic.paintPos.y = y;
}

//��ȡ��ͼʵ�����
Map * Map::Instance()
{
	static Map instance;
	return &instance;
}
//����������Ʒ�����λ��
void Map::GetPaintPos(double mapPosX, double mapPosY, float * x, float * y)
{
	*x = mapPosX + graphic.paintPos.x;
	*y = mapPosY + graphic.paintPos.y; 
}
void Map::GetMapPos(double paintPosX, double paintPosY, float * x, float * y)
{
	*x = paintPosX - graphic.paintPos.x;
	*y = paintPosY - graphic.paintPos.y;
}
//����Ƿ���ǽ������ײ
bool Map::CheckWallCollision(RECT rect,RECT* wall)
{
	for (auto var : Walls)
	{
		RECT dest;
		
		if (IntersectRect(&dest, &var, &rect))
		{
			if (wall)
			{
				*wall = var;
			}
			return true;
		}
	}
	return false;
}

bool Map::CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2, list<RectCollision>* RC)
{
	for (auto var : Walls)
	{
		if (LineRectCollision(F1, F2, var))
		{
			D3DXVECTOR2 contactPoint;
			RectCollision rc;

			LineRectCollision(F1, F2, var, &contactPoint);
			rc.mainRect = var;
			rc.collisionPoint = contactPoint;
			rc.extraInfo.rectType = WallRect;

			RC->push_front(rc);
		}
	}

	return false;
}

bool Map::CheckBulletWallHit(D3DXVECTOR2 F1, D3DXVECTOR2 F2, D3DXVECTOR2 * contactPoint)
{
	for (auto var : Walls)
	{
		if (LineRectCollision(F1, F2, var,contactPoint))
		{
			return true;
		}
	}

	return false;
}