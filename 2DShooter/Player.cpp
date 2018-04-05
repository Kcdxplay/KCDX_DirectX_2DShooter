#include "Player.h"
#include "PlayerOwnedMState.h"
#include "Map.h"

const int playerWidth = 67;	//玩家图像宽度
const int playerHeight = 94;
const double disX = 200;	//边框距离 横轴
const double disUp = 75;	//边框距离 上测
const double disDn = 130;	//边框距离 下侧

bool Player::HandleMessage(const Telegram & msg)
{
	return pMStateMachine->HandleMessage(msg);
}

void Player::Update()
{
	static CharcterDetailData* pData = GetDetailData();
	static Graphic* pGraph = GetGraphic();


	//状态机更新
	pMStateMachine->Update();

	RectSet();

	//判断脚下是否有平台，没有就开始掉落
	static RECT rect{ 0,0,0,0 };
	rect = preCheck[2];
	if (!Map::Instance()->CheckWallCollision(rect))
	{
		pMStateMachine->ChangeState(PlayerMFalling::Instance());
	}

	//=====由玩家自己控制镜头移动=====//

	double dis;//触发调整的距离
	double val;//应该修正的大小

	//向左判断
	dis = disX;
	if (graph.paintPos.x < dis)
	{
		val = dis - graph.paintPos.x;
		Map::Instance()->MoveToLeft(val);
	}

	//向右判断
	dis = SCREENW - disX;
	if (graph.paintPos.x + playerWidth > dis)
	{
		val = graph.paintPos.x + playerWidth - dis;
		Map::Instance()->MoveToRight(val);
	}

	//向上判断
	dis = disUp;
	if (graph.paintPos.y < dis)
	{
		val = dis - graph.paintPos.y;
		Map::Instance()->MoveToUp(val);
	}

	//向下判断
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

	//子弹的更新与判断
	list<Bullet*> LBulletsNeedToRemove;	//需删除子弹列表

	for (auto& var : bullets)
	{
		if(var.Ended())
		{
			//将要删掉的子弹丢到列表里
			LBulletsNeedToRemove.push_back(&var);
		}
	}
	for (auto& var : LBulletsNeedToRemove)
	{
		bullets.remove(*var);
	}

	//武器的更新与判断
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

	//两次的间隔，隔开两次激发
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