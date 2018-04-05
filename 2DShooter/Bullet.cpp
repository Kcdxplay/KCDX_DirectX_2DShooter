#include "Bullet.h"
#include "Charcter.h"
#include "Map.h"
#include "MessageDispatcher.h"
#include "MessageType.h"
#include "Enemy.h"

#include "EffectType.h"
#include "GlobalEffect.h"

Bullet::Bullet()
{
}
Bullet::Bullet(int owner, D3DXVECTOR2 startPos, D3DXVECTOR2 endPos) :startPos(startPos), deltaTime(2.0), damage(10),
																	 FramP1(startPos), FramP2(startPos)
{
	PaintPos = new D3DXVECTOR2[2];
	dir = endPos - startPos;

	D3DXVec2Normalize(&dir, &dir);
}

Bullet::Bullet(int owner, D3DXVECTOR2 startPos, D3DXVECTOR2 endPos, double deltaTime):startPos(startPos),deltaTime(deltaTime),  damage(10),
																					  FramP1(startPos), FramP2(startPos)
{
	PaintPos = new D3DXVECTOR2[2];
	dir = endPos-startPos;
	
	D3DXVec2Normalize(&dir, &dir);	
}

RectCollision * Bullet::FindClosestHit(list<RectCollision>* RC)
{
	RectCollision* rc = nullptr;
	float minRange=SCREENH+SCREENW;

	for (auto& var : *RC)
	{
		float newRange = abs(
			(var.collisionPoint.x - startPos.x) +
			(var.collisionPoint.y - startPos.y));

		if (newRange < minRange)
		{
			minRange = newRange;
			rc = &var;
		}
	}
	return rc;
}

void Bullet::Update()
{
	//�������ӵ�ײ�������ж���
	list<RectCollision> RC;

	//����ӵ����̫Զ���͵����Ѿ��ɵ���ĵط�ȥ�ˣ�������
	if ((FramP2.x - FramP1.x) > 3 * SCREENW || (FramP2.y - FramP1.y) > 3 * SCREENH)
	{
		ended = true;

		this->~Bullet();
		return;
	}

	FramP1 = FramP2;
	if (!ended)
	{
		FramP2 = startPos + dir;
		dir *= deltaTime;

		for (auto& var : lEnemy)
		{
			RECT rect = var->GetMainRect();
			if (LineRectCollision(FramP1, FramP2, rect))
			{
				D3DXVECTOR2 point;
				RectCollision rc;
				
				
				//�����ײ
				LineRectCollision(FramP1, FramP2, rect, &point);

				rc.mainRect = rect;
				rc.collisionPoint = point;

				rc.extraInfo.rectType = EnemyRect;
				rc.extraInfo.ID = var->ID();
				
				RC.push_front(rc);
			}
		}
		Map::Instance()->CheckBulletWallHit(FramP1, FramP2, &RC);	

		RectCollision* closestRect;
		closestRect = FindClosestHit(&RC);

		if (closestRect)
		{
			BulletEnd(*closestRect);
		}
	}



//if (Map::Instance()->CheckBulletWallHit(FramP1, FramP2,&RC))
//		{
//			D3DXVECTOR2 point;
//			Map::Instance()->CheckBulletWallHit(FramP1, FramP2,&point);
//
//			FramP2 = point;
//
//			ended = true;
//			Effect->PlayEffectAt(point.x, point.y, Eft_Explosion);
//			BulletEnd(point);
//		}
	//�������ĵ��˷���Ϣ�������Լ���������ֵ
	//Dispatch->DispatchMessageW(0, owner, receiver, Msg_IShootedYou, &damage);

	////ended = true;
	//BulletEnd(point);


	Map::Instance()->GetPaintPos(FramP1.x, FramP1.y, &PaintPos[0].x, &PaintPos[0].y);
	Map::Instance()->GetPaintPos(FramP2.x, FramP2.y, &PaintPos[1].x, &PaintPos[1].y);
}
void Bullet::Render()
{
	Line->SetAntialias(true);
	Line->SetWidth(2);
	Line->Draw(PaintPos,2, 0xffffffff);
}
bool Bullet::HandleMessage(const Telegram & msg)
{
	return false;
}

Bullet::~Bullet()
{
	ended = true;

}

void Bullet::BulletEnd()
{
	//this->~Bullet();
}

void Bullet::BulletEnd(RectCollision rc)
{
	ended = true;

	switch (rc.extraInfo.rectType)
	{
	//������е���ǽ
	case WallRect:
		Effect->PlayEffectAt(rc.collisionPoint.x, rc.collisionPoint.y, Eft_Explosion);
		break;
	//������е��ǵ���
	case EnemyRect:
		//�������ĵ��˷���Ϣ�������Լ���������ֵ
		Dispatch->DispatchMessageW(0, owner, rc.extraInfo.ID, Msg_IShootedYou, &damage);
		break;
	default:
		break;
	}
	//����ײ������

	//


	FramP2 = rc.collisionPoint;
	this->~Bullet();
}