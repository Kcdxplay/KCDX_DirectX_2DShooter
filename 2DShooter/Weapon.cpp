#include "GamePart.h"
#include "Weapon.h"
#include "Map.h"
#include "Tools.h"
#include "Cursor.h"

void Weapon::Shoot()
{
}
void Weapon::Update()
{
	MAP->GetPaintPos(graph.mapPos.x, graph.mapPos.y, &graph.paintPos.x, &graph.paintPos.y);
}
void Weapon::Render()
{

}
D3DXVECTOR2 Weapon::GetMuzzlePos()
{
	D3DXVECTOR2 mos{ Mouse->GetMapPosX(),Mouse->GetMapPosY() };
	D3DXVECTOR2 gun{ graph.mapPos.x + rotateCenter.x,
					graph.mapPos.y + rotateCenter.y };
	D3DXVECTOR2 Ray = mos - gun;

	D3DXVec2Normalize(&Ray, &Ray);
	Ray *= gunLength;

	D3DXVECTOR2 muzzle = gun + Ray;

	return muzzle;
}


void WP_ChargeRifle::LoadTexture()
{
	D3DXIMAGE_INFO info;

	graph.texture = LoadTextureWithInfo(L"ChargeRifle.png", NULL, &info);
	
	width = info.Width;
	height = info.Height;
}

bool WP_ChargeRifle::HandleMessage(const Telegram & msg)
{
	return true;
}
void WP_ChargeRifle::SetPos(float x, float y)
{
	graph.mapPos.x = x;
	graph.mapPos.y = y;
}

void WP_ChargeRifle::RenderForPlayer()
{
	D3DXVECTOR2 mouseMapVector{ Mouse->GetMapPosX(),Mouse->GetMapPosY() };
	D3DXVECTOR2 weaponMapVector{ graph.mapPos.x,graph.mapPos.y };

	double rotation = getRadiansBytwoPoints(weaponMapVector, mouseMapVector);

	spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
	
	//缩放矩阵
	D3DXVECTOR2 scale(1.0, 1.0);
	//绘制坐标
	D3DXVECTOR2 trans(graph.paintPos.x, graph.paintPos.y);
	//旋转中心
	D3DXVECTOR2 rotate = rotateCenter;

	if (mouseMapVector.x < weaponMapVector.x)
	{
		scale.x = -1.0;
		trans.x += 2*rotateCenter.x;
		rotation -= 3.14159265359;
		rotate.x = -rotate.x;
	}

	//变换矩阵
	D3DXMATRIX mat;
	D3DXMATRIX origin;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &rotate, rotation, &trans);

	spriteOBJ->GetTransform(&origin);
	spriteOBJ->SetTransform(&mat);

	RECT srcRect = { 0,0,width,height };

	spriteOBJ->Draw(graph.texture, &srcRect, NULL, NULL, 0xffffffff);

	spriteOBJ->SetTransform(&origin);

	spriteOBJ->End();
}