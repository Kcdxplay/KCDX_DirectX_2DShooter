#include "Charcter.h"
#include "Telegram.h"
#include "MessageType.h"
#include "Map.h"

//ȫ���ж�״̬
MGlobalChecking * MGlobalChecking::Instance()
{
	static MGlobalChecking instance;
	return &instance;
}
void MGlobalChecking::Enter(Charcter * pCharcter)
{
}
void MGlobalChecking::Execute(Charcter * pCharcter)
{
}
void MGlobalChecking::Exit(Charcter * pCharcter)
{
}
bool MGlobalChecking::OnMessage(Charcter * pCharcter, const Telegram & msg)
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
MStanding* MStanding::Instance()
{
	static MStanding instance;
	return &instance;
}

void MStanding::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	pData->SetASpeedX(0);
	pData->SetASpeedY(0);
}
void MStanding::Execute(Charcter * pCharcter)
{
	//Map::Instance()->GetPaintPos(
	//	pGraph->mapPos.x,
	//	pGraph->mapPos.y,
	//	&pGraph->paintPos.x,
	//	&pGraph->paintPos.y);
}
void MStanding::Exit(Charcter * pCharcter)
{

}
bool MStanding::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}


//����״̬
MWalking* MWalking::Instance()
{
	static MWalking instance;
	return &instance;
}

void MWalking::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();
	
}
void MWalking::Execute(Charcter * pCharcter)
{
	//�Ƿ��뾲ֹ״̬�ܽ�
	if (fabs(pData->ASpeedX()) > pData->Damp())
	{
		//������ٶ�����
		if (pData->ASpeedX() > 0)
		{
			pData->SetASpeedX(pData->ASpeedX() - pData->Damp());
		}
		//������ٶ�����
		else if (pData->ASpeedX()<0)
		{
			pData->SetASpeedX(pData->ASpeedX() + pData->Damp());
		}
	}
	else
	{
		pData->SetASpeedX(0);
		static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

		fsm->ChangeState(MStanding::Instance());
	}

	if (pData->ASpeedX() < pData->MaxForce1())
	{
		pData->SetASpeedX(1 + pData->ASpeedX());
	}

	pCharcter->RectSet();
	
	RECT rect{ 0,0,0,0 };
	//if (!Map::Instance()->CheckWallCollision(rect));
	{
		pGraph->mapPos.x += pData->ASpeedX();
		pGraph->mapPos.y += pData->ASpeedY();
		//pData->SetASpeedX(pData->ASpeedX() - pData->Damp());
	}




	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
	
}
void MWalking::Exit(Charcter * pCharcter)
{
}
bool MWalking::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//���״̬
MDashing * MDashing::Instance()
{
	static MDashing instance;
	return &instance;
}

void MDashing::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	pData->SetASpeedX(pData->MaxForce2());
}
void MDashing::Execute(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	RECT rect{ 0,0,0,0 };
	if (!Map::Instance()->CheckWallCollision(rect));
	{
		pGraph->mapPos.x += pData->ASpeedX();
		pGraph->mapPos.y += pData->ASpeedY();
		pData->SetASpeedX(pData->ASpeedX() - pData->Damp());
	}

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x, 
		pGraph->mapPos.y, 
		&pGraph->paintPos.x, 
		&pGraph->paintPos.y);
	if (pData->ASpeedX() <= pData->MaxForce1())
	{
		pCharcter->GetMotionFSM()->ChangeState(MWalking::Instance());
	}
}
void MDashing::Exit(Charcter * pCharcter)
{
}
bool MDashing::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//����״̬
MFalling* MFalling::Instance()
{
	static MFalling instance;
	return &instance;
}
void MFalling::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();
}
void MFalling::Execute(Charcter * pCharcter)
{
	pData->SetASpeedY(pData->ASpeedY() + pData->DampG());

	//�Ƿ������µ�״̬��Զ	true-�� false-����
	if (pData->ASpeedY() > pData->MaxFallingSpeed())
	{
		pData->SetASpeedY(pData->MaxFallingSpeed());
	}

	static RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	static RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

	if (pData->ASpeedY() < 0)
	{
		pGraph->mapPos.y += pData->ASpeedY();
	}

	if (pData->ASpeedY() >= 0)
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
			//pGraph->mapPos.y = wall.top - ();

			static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

			fsm->ChangeState(MStanding::Instance());
		}
	}

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
	else if (pData->ASpeedX() < 0)
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
void MFalling::Exit(Charcter * pCharcter)
{
}
bool MFalling::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}