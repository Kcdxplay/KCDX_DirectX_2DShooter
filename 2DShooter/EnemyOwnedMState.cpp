#include "EnemyOwnedMState.h"
#include "MessageType.h"
#include "GlobalEffect.h"
#include "EffectType.h"
#include "Enemy.h"

struct Telegram;

//ȫ��״̬
EnemyMGloable * EnemyMGloable::Instance()
{
	static EnemyMGloable instance;
	return &instance;
}
void EnemyMGloable::Enter(Charcter * pCharcter)
{
}
void EnemyMGloable::Execute(Charcter * pCharcter)
{
	if (pCharcter->Health() <= 0)
	{
		Effect->PlayEffectAt(pCharcter->GetGraphic()->mapPos.x,
							pCharcter->GetGraphic()->mapPos.y, 
							Eft_Explosion);

		ENM->listOfRemove.push_front((Enemy*)pCharcter);
	}
}
void EnemyMGloable::Exit(Charcter * pCharcter)
{
}
bool EnemyMGloable::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	switch (msg.Msg)
	{
	case Msg_IShootedYou:
		pCharcter->GotHited(*(float*)msg.ExtraInfo);
		return true;
		break;
	default:
		break;
	}

	return false;
}

//վ��״̬
EnemyMStanding * EnemyMStanding::Instance()
{
	static EnemyMStanding instance;
	return &instance;
}
void EnemyMStanding::Enter(Charcter * pCharcter)
{
}
void EnemyMStanding::Execute(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}
void EnemyMStanding::Exit(Charcter * pCharcter)
{
}
bool EnemyMStanding::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//��������״̬
EnemyMWalkLeft * EnemyMWalkLeft::Instance()
{
	static EnemyMWalkLeft instance;
	return &instance;
}
void EnemyMWalkLeft::Enter(Charcter * pCharcter)
{
}
void EnemyMWalkLeft::Execute(Charcter * pCharcter)
{
	//��ʼ����Ҫʹ�õ�����
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	//���º�����ٶ�
	pData->SetASpeedX(pData->ASpeedX() + pData->Damp());

	//�ж��Ƿ�ỹ���ٴ�����	true-��	false-����
	if (fabs(pData->ASpeedX()) + pData->Force1() < pData->MaxForce1())
	{
		pData->SetASpeedX(pData->ASpeedX() - pData->Force1());
	}
	else
	{
		pData->SetASpeedX(0 - pData->MaxForce1());
	}

	//=====׼�����»���λ��=====//
	RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

	//�жϼ��ٶȷ����Ƿ�����
	if (pData->ASpeedX() > 0)
	{
		rect = pCharcter->GetPreCheckRect(1);

		rect.left += pData->ASpeedX();
		rect.right += pData->ASpeedX();

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.x += pData->ASpeedX();
		}
	}

	//�жϼ��ٶȷ����Ƿ�����
	if (pData->ASpeedX() < 0)
	{
		rect = pCharcter->GetPreCheckRect(0);

		rect.left += pData->ASpeedX();
		rect.right += pData->ASpeedX();

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.x += pData->ASpeedX();
		}
	}

	pCharcter->RectSet();

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}
void EnemyMWalkLeft::Exit(Charcter * pCharcter)
{
}
bool EnemyMWalkLeft::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//��������״̬
EnemyMWalkRight * EnemyMWalkRight::Instance()
{
	static EnemyMWalkRight instance;
	return &instance;
}
void EnemyMWalkRight::Enter(Charcter * pCharcter)
{
}
void EnemyMWalkRight::Execute(Charcter * pCharcter)
{
	//��ʼ����Ҫʹ�õ�����
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	//���º�����ٶ�
	pData->SetASpeedX(pData->ASpeedX() - pData->Damp());

	//�ж��Ƿ�ỹ���ٴ�����	true-��	false-����
	if (fabs(pData->ASpeedX()) + pData->Force1() < pData->MaxForce1())
	{
		pData->SetASpeedX(pData->ASpeedX() + pData->Force1());
	}
	else
	{
		pData->SetASpeedX(pData->MaxForce1());
	}


	//=====׼�����»���λ��=====//
	RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

							//�жϼ��ٶȷ����Ƿ�����
	if (pData->ASpeedX() > 0)
	{
		rect = pCharcter->GetPreCheckRect(1);

		rect.left += pData->ASpeedX();
		rect.right += pData->ASpeedX();

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.x += pData->ASpeedX();
		}
	}

	//�жϼ��ٶȷ����Ƿ�����
	if (pData->ASpeedX() < 0)
	{
		rect = pCharcter->GetPreCheckRect(0);

		rect.left += pData->ASpeedX();
		rect.right += pData->ASpeedX();

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.x += pData->ASpeedX();
		}
	}

	pCharcter->RectSet();

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);

}
void EnemyMWalkRight::Exit(Charcter * pCharcter)
{
}
bool EnemyMWalkRight::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//����״̬
EnemyMFalling * EnemyMFalling::Instance()
{
	static EnemyMFalling instance;
	return &instance;
}
void EnemyMFalling::Enter(Charcter * pCharcter)
{
}
void EnemyMFalling::Execute(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	pData->SetASpeedY(pData->ASpeedY() + pData->DampG());

	//������ٶ��Ƿ񳬹���������ٶ�	true-�� false-����
	if (pData->ASpeedY() > pData->MaxFallingSpeed())
	{
		pData->SetASpeedY(pData->MaxFallingSpeed());
	}

	RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

	if (pData->ASpeedY() < 0)
	{
		pGraph->mapPos.y += pData->ASpeedY();
	}

	else if (pData->ASpeedY() >= 0)
	{
		rect = pCharcter->GetPreCheckRect(2);

		/*rect.bottom += pData->ASpeedY();
		rect.top += pData->ASpeedY();*/

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.y += pData->ASpeedY();
		}
		else
		{
			pCharcter->GetMotionFSM()->ChangeState(EnemyMStanding::Instance());
		}
	}


	////�жϼ��ٶȷ����Ƿ�����
	//if (pData->ASpeedX() > 0)
	//{
	//	rect = pCharcter->GetPreCheckRect(1);

	//	rect.left += pData->ASpeedX();
	//	rect.right += pData->ASpeedX();

	//	if (!Map::Instance()->CheckWallCollision(rect, &wall))
	//	{
	//		pGraph->mapPos.x += pData->ASpeedX();
	//	}
	//}

	////�жϼ��ٶȷ����Ƿ�����
	//else if (pData->ASpeedX() < 0)
	//{
	//	rect = pCharcter->GetPreCheckRect(0);

	//	rect.left += pData->ASpeedX();
	//	rect.right += pData->ASpeedX();

	//	if (!Map::Instance()->CheckWallCollision(rect, &wall))
	//	{
	//		pGraph->mapPos.x += pData->ASpeedX();
	//	}
	//}

	pCharcter->RectSet();

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}
void EnemyMFalling::Exit(Charcter * pCharcter)
{
}
bool EnemyMFalling::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}
