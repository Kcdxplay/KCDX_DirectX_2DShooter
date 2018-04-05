#include "PlayerOwnedMState.h"

#include "MessageType.h"

//站立状态
PlayerMStanding * PlayerMStanding::Instance()
{
	static PlayerMStanding instance;
	return &instance;
}
void PlayerMStanding::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	/*pData->SetASpeedX(0);
	pData->SetASpeedY(0);*/
}
void PlayerMStanding::Execute(Charcter * pCharcter)
{
	pData->SetASpeedX(0);
	pData->SetASpeedY(0);
}
void PlayerMStanding::Exit(Charcter * pCharcter)
{
}
bool PlayerMStanding::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//行走状态
PlayerMWalking * PlayerMWalking::Instance()
{
	static PlayerMWalking instance;
	return &instance;
}
void PlayerMWalking::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();
}
void PlayerMWalking::Execute(Charcter * pCharcter)
{
	//是否离静止状态很远	true-是 false-不是
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
		//速度很低了，进入站立状态
		pData->SetASpeedX(0);
		static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

		fsm->ChangeState(MStanding::Instance());
	}

	Player* pPlayer = (Player*)pCharcter;

	//判断是否会超出最大速度
	if (fabs(pData->ASpeedX()) + pData->Force1() < pData->MaxForce1())
	{
		if (keys[DIK_D])
		{			
			pData->SetASpeedX(pData->ASpeedX() + pData->Force1());
		}
		else if (keys[DIK_A])
		{
			pData->SetASpeedX(pData->ASpeedX() - pData->Force1());
		}
		else
		{
			//计算行走时长 
			QueryPerformanceCounter(&pPlayer->tWalkEnd);
			QueryPerformanceFrequency(&pPlayer->tFrequency);
			pPlayer->tWalking = (pPlayer->tWalkEnd.QuadPart - pPlayer->tWalkStart.QuadPart)*1.0 / pPlayer->tFrequency.QuadPart;

			if (pPlayer->tWalking > 0.25)
			{
				pPlayer->Walk2Long = true;
			}
			else
			{
				pPlayer->Walk2Long = false;
			}
		}
	}
	else 
	{
		if (keys[DIK_D])
		{
			pData->SetASpeedX(pData->MaxForce1());
		}
		else if (keys[DIK_A])
		{
			pData->SetASpeedX(0 - pData->MaxForce1());
		}
		else
		{
			//计算行走时长 
			QueryPerformanceCounter(&pPlayer->tWalkEnd);
			QueryPerformanceFrequency(&pPlayer->tFrequency);
			pPlayer->tWalking = (pPlayer->tWalkEnd.QuadPart - pPlayer->tWalkStart.QuadPart)*1.0 / pPlayer->tFrequency.QuadPart;

			if (pPlayer->tWalking > 0.25)
			{
				pPlayer->Walk2Long = true;
			}
			else
			{
				pPlayer->Walk2Long = false;
			}
		}
	}
	


	//=====准备更新绘制位置=====//
	static RECT rect{ 0,0,0,0 };	//预测碰撞的矩阵
	static RECT wall{ 0,0,0,0 };	//有碰撞的墙体

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
void PlayerMWalking::Exit(Charcter * pCharcter)
{
}
bool PlayerMWalking::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//冲刺状态
PlayerMDashing * PlayerMDashing::Instance()
{
	static PlayerMDashing instance;
	return &instance;
}
void PlayerMDashing::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();

	Player* pPlayer = (Player*)pCharcter;
	pPlayer->Walk2Long = true;

	if (pData->ASpeedX() < pData->MaxForce2())
	{
		if (keys[DIK_A])
		{
			pData->SetASpeedX(0 - pData->Force2());
		}
		else if(keys[DIK_D])
		{
			pData->SetASpeedX(pData->Force2());
		}
	}
}
void PlayerMDashing::Execute(Charcter * pCharcter)
{
	//是否离行走状态很远	true-是 false-不是
	if (fabs(pData->ASpeedX()) > pData->MaxForce1())
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
		//速度很低了，进入行走状态
		if (pData->ASpeedX() > 0) {
			pData->SetASpeedX(pData->MaxForce1());

		}
		else if (pData->ASpeedX() < 0) {
			pData->SetASpeedX(0 - pData->MaxForce1());
		}
		static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

		fsm->ChangeState(PlayerMWalking::Instance());
	}

	//=====准备更新绘制位置=====//
	static RECT rect{ 0,0,0,0 };	//预测碰撞的矩阵
	static RECT wall{ 0,0,0,0 };	//有碰撞的墙体

	//添加阻滞力的使用
	/*if (pData->ASpeedX() < pData->MaxForce2())
	{
		if (keys[DIK_A])
		{
			pData->SetASpeedX(0 - pData->Force2());
		}
		else if (keys[DIK_D])
		{
			pData->SetASpeedX(pData->Force2());
		}
	}*/

	//判断加速度方向，是否向右
	if (pData->ASpeedX() > 0)
	{
		rect = pCharcter->GetPreCheckRect(1);

		rect.left += pData->ASpeedX();
		rect.right += pData->ASpeedX();

		if (!Map::Instance()->CheckWallCollision(rect, &wall))
		{
			pGraph->mapPos.x += pData->ASpeedX();
			pGraph->mapPos.y += pData->ASpeedY();
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
			pGraph->mapPos.y += pData->ASpeedY();
		}
	}

	pCharcter->RectSet();

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}
void PlayerMDashing::Exit(Charcter * pCharcter)
{
	Player* pPlayer = (Player*)pCharcter;
	pPlayer->Walk2Long = false;
}
bool PlayerMDashing::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//掉落状态
PlayerMFalling * PlayerMFalling::Instance()
{
	static PlayerMFalling instance;
	return &instance;
}
void PlayerMFalling::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();
}
void PlayerMFalling::Execute(Charcter * pCharcter)
{
	pData->SetASpeedY(pData->ASpeedY() + pData->DampG());

	//纵轴加速度是否超过掉落最大速度	true-是 false-不是
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
			//pGraph->mapPos.y = wall.top - ();

			static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

			fsm->ChangeState(PlayerMStanding::Instance());
		}
	}

	//=======来自Walking的代码段=======//
	//=======以下是横向处理代码=======//
	{
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
			//速度很低了，将水平速度设置为0
			pData->SetASpeedX(0);
		}

		Player* pPlayer = (Player*)pCharcter;

		//判断是否会超出最大速度
		if (fabs(pData->ASpeedX()) + pData->Force1() < pData->MaxForce1())
		{
			if (keys[DIK_D])
			{
				pData->SetASpeedX(pData->ASpeedX() + pData->Force1());
			}
			else if (keys[DIK_A])
			{
				pData->SetASpeedX(pData->ASpeedX() - pData->Force1());
			}
			else
			{
				//计算行走时长 
				QueryPerformanceCounter(&pPlayer->tWalkEnd);
				QueryPerformanceFrequency(&pPlayer->tFrequency);
				pPlayer->tWalking = (pPlayer->tWalkEnd.QuadPart - pPlayer->tWalkStart.QuadPart)*1.0 / pPlayer->tFrequency.QuadPart;

				if (pPlayer->tWalking > 0.25)
				{
					pPlayer->Walk2Long = true;
				}
				else
				{
					pPlayer->Walk2Long = false;
				}
			}
		}
		else
		{
			if (keys[DIK_D])
			{
				//pData->SetASpeedX(pData->MaxForce1());
			}
			else if (keys[DIK_A])
			{
				//pData->SetASpeedX(0 - pData->MaxForce1());
			}
			else
			{
				//计算行走时长 
				QueryPerformanceCounter(&pPlayer->tWalkEnd);
				QueryPerformanceFrequency(&pPlayer->tFrequency);
				pPlayer->tWalking = (pPlayer->tWalkEnd.QuadPart - pPlayer->tWalkStart.QuadPart)*1.0 / pPlayer->tFrequency.QuadPart;

				if (pPlayer->tWalking > 0.25)
				{
					pPlayer->Walk2Long = true;
				}
				else
				{
					pPlayer->Walk2Long = false;
				}
			}
		}
	}
	//=======以上是横向处理代码=======//


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
void PlayerMFalling::Exit(Charcter * pCharcter)
{
}
bool PlayerMFalling::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//全局状态
PlayerGlobal * PlayerGlobal::Instance()
{
	static PlayerGlobal instance;
	return &instance;
}
void PlayerGlobal::Enter(Charcter * pCharcter)
{
	pData = pCharcter->GetDetailData();
	pGraph = pCharcter->GetGraphic();
}
void PlayerGlobal::Execute(Charcter * pCharcter)
{

}
void PlayerGlobal::Exit(Charcter * pCharcter)
{
}
bool PlayerGlobal::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	static int time;

	switch (msg.Msg)
	{
	case Msg_IStabedYou:
		if (GetTickCount() > time + 2000)
		{
			pCharcter->SetHealth(pCharcter->Health() - 10);

			time = GetTickCount();
		}
		return true;
		break;
	default:
		break;
	}
	return false;
}