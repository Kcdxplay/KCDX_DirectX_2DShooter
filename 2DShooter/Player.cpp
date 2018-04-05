#include "Player.h"
#include "PlayerOwnedMState.h"
#include "Map.h"

const int playerWidth = 67;	//���ͼ����
const int playerHeight = 94;
const double disX = 200;	//�߿���� ����
const double disUp = 75;	//�߿���� �ϲ�
const double disDn = 130;	//�߿���� �²�

bool Player::HandleMessage(const Telegram & msg)
{
	return pMStateMachine->HandleMessage(msg);
}

void Player::Update()
{
	static CharcterDetailData* pData = GetDetailData();
	static Graphic* pGraph = GetGraphic();


	//״̬������
	pMStateMachine->Update();

	RectSet();

	//�жϽ����Ƿ���ƽ̨��û�оͿ�ʼ����
	static RECT rect{ 0,0,0,0 };
	rect = preCheck[2];
	if (!Map::Instance()->CheckWallCollision(rect))
	{
		pMStateMachine->ChangeState(PlayerMFalling::Instance());
	}

	//=====������Լ����ƾ�ͷ�ƶ�=====//

	double dis;//���������ľ���
	double val;//Ӧ�������Ĵ�С

	//�����ж�
	dis = disX;
	if (graph.paintPos.x < dis)
	{
		val = dis - graph.paintPos.x;
		Map::Instance()->MoveToLeft(val);
	}

	//�����ж�
	dis = SCREENW - disX;
	if (graph.paintPos.x + playerWidth > dis)
	{
		val = graph.paintPos.x + playerWidth - dis;
		Map::Instance()->MoveToRight(val);
	}

	//�����ж�
	dis = disUp;
	if (graph.paintPos.y < dis)
	{
		val = dis - graph.paintPos.y;
		Map::Instance()->MoveToUp(val);
	}

	//�����ж�
	dis = SCREENH - disDn;
	if (graph.paintPos.y + playerHeight > dis)
	{
		val = graph.paintPos.y + playerHeight - dis;
		Map::Instance()->MoveToDown(val);
	}


	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);

	//�ӵ��ĸ������ж�
	list<Bullet*> LBulletsNeedToRemove;	//��ɾ���ӵ��б�

	for (auto& var : bullets)
	{
		if(var.Ended())
		{
			//��Ҫɾ�����ӵ������б���
			LBulletsNeedToRemove.push_back(&var);
		}
	}
	for (auto& var : LBulletsNeedToRemove)
	{
		bullets.remove(*var);
	}

	//�����ĸ������ж�
	float wpPosX = (graph.mapPos.x + playerWidth / 2) - pWeapon->HandleX();
	float wpPosY = (graph.mapPos.y + playerHeight / 2) - pWeapon->HandleY();
	pWeapon->SetPos(wpPosX, wpPosY);
	pWeapon->Update();
}
void Player::Render()
{
	spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
	//spriteOBJ->Draw(graph.texture, NULL, NULL, &graph.paintPos, D3DCOLOR_XRGB(255, 255, 255));
	Sprite_Draw_Frame(graph.texture, &graph.paintPos, graph.frameNum, graph.frameW, graph.frameH, graph.columns);
	spriteOBJ->End();

	for (auto& var : bullets)
	{
		var.Render();
	}

	pWeapon->RenderForPlayer();
}

void Player::Walk()
{
	if (pMStateMachine->GetCurrentState()!=PlayerMFalling::Instance() && 
		pMStateMachine->GetCurrentState() != PlayerMDashing::Instance())
	{
		QueryPerformanceCounter(&tWalkStart);
		pMStateMachine->ChangeState(PlayerMWalking::Instance());
	}
}
void Player::Dash()
{
	if (!Walk2Long &&
		pMStateMachine->GetCurrentState() != PlayerMFalling::Instance())
	{
		pMStateMachine->ChangeState(PlayerMDashing::Instance());
	}
}
void Player::Jump()
{
	if (pMStateMachine->GetCurrentState() != PlayerMFalling::Instance())
	{
		data.SetASpeedY(data.Force3());

		pMStateMachine->ChangeState(PlayerMFalling::Instance());
	}
}
void Player::Shoot()
{
	
	static LARGE_INTEGER t_start, t_end, t_lock, t_frequency;


	QueryPerformanceCounter(&t_start);
	QueryPerformanceFrequency(&t_frequency);

	//���εļ�����������μ���
	double TimePassed = (t_start.QuadPart - t_end.QuadPart)*1.0 / t_frequency.QuadPart;

	if (TimePassed > pWeapon->FireRate())
	{
		CharcterDetailData* pData = GetDetailData();
		Graphic* graph = GetGraphic();

		float Mx = Cursor::Instance()->GetMapPosX();
		float My = Cursor::Instance()->GetMapPosY();

		//D3DXVECTOR2 start = { graph->mapPos.x,graph->mapPos.y };
		D3DXVECTOR2 start = pWeapon->GetMuzzlePos();
		D3DXVECTOR2 mouse = { Mx,My };

		Bullet bul(this->ID(), start, mouse,pWeapon->BulletSpeed());

		bullets.push_front(bul);

		t_end = t_start;
	}
}