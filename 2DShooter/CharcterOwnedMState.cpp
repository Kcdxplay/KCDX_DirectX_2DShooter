#include "Charcter.h"
#include "Telegram.h"
#include "MessageType.h"
#include "Map.h"

//全局判断状态
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

//站立状态
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


//行走状态
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
	//是否离静止状态很近
	if (fabs(pData->ASpeedX()) > pData->Damp())
	{
		//如果加速度向右
		if (pData->ASpeedX() > 0)
		{
			pData->SetASpeedX(pData->ASpeedX() - pData->Damp());
		}
		//如果加速度向左
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

//冲刺状态
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

//掉落状态
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

	//是否离向下掉状态很远	true-是 false-不是
	if (pData->ASpeedY() > pData->MaxFallingSpeed())
	{
		pData->SetASpeedY(pData->MaxFallingSpeed());
	}

	static RECT rect{ 0,0,0,0 };	//预测碰撞的矩阵
	static RECT wall{ 0,0,0,0 };	//有碰撞的墙体

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

	//判断加速度方向，是否向右
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

	//判断加速度方向，是否向左
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