#include "PlayerOwnedMState.h"

#include "MessageType.h"

//վ��״̬
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

//����״̬
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
	//�Ƿ��뾲ֹ״̬��Զ	true-�� false-����
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
		//�ٶȺܵ��ˣ�����վ��״̬
		pData->SetASpeedX(0);
		static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

		fsm->ChangeState(MStanding::Instance());
	}

	Player* pPlayer = (Player*)pCharcter;

	//�ж��Ƿ�ᳬ������ٶ�
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
			//��������ʱ�� 
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
			//��������ʱ�� 
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
	


	//=====׼�����»���λ��=====//
	static RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	static RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

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
void PlayerMWalking::Exit(Charcter * pCharcter)
{
}
bool PlayerMWalking::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//���״̬
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
	//�Ƿ�������״̬��Զ	true-�� false-����
	if (fabs(pData->ASpeedX()) > pData->MaxForce1())
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
		//�ٶȺܵ��ˣ���������״̬
		if (pData->ASpeedX() > 0) {
			pData->SetASpeedX(pData->MaxForce1());

		}
		else if (pData->ASpeedX() < 0) {
			pData->SetASpeedX(0 - pData->MaxForce1());
		}
		static MStateMachine<Charcter>* fsm = pCharcter->GetMotionFSM();

		fsm->ChangeState(PlayerMWalking::Instance());
	}

	//=====׼�����»���λ��=====//
	static RECT rect{ 0,0,0,0 };	//Ԥ����ײ�ľ���
	static RECT wall{ 0,0,0,0 };	//����ײ��ǽ��

	//�����������ʹ��
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

	//�жϼ��ٶȷ����Ƿ�����
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

	//�жϼ��ٶȷ����Ƿ�����
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

//����״̬
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

	//������ٶ��Ƿ񳬹���������ٶ�	true-�� false-����
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

	//=======����Walking�Ĵ����=======//
	//=======�����Ǻ��������=======//
	{
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
			//�ٶȺܵ��ˣ���ˮƽ�ٶ�����Ϊ0
			pData->SetASpeedX(0);
		}

		Player* pPlayer = (Player*)pCharcter;

		//�ж��Ƿ�ᳬ������ٶ�
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
				//��������ʱ�� 
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
				//��������ʱ�� 
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
	//=======�����Ǻ��������=======//


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
void PlayerMFalling::Exit(Charcter * pCharcter)
{
}
bool PlayerMFalling::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}

//ȫ��״̬
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