#include "DirectX.h"
#include "Sound.h"
#include "Map.h"
#include "Charcter.h"
#include "Player.h"
#include "Bullet.h"
#include "Cursor.h"
#include "Enemy.h"

#include "GlobalEffect.h"
#include "EffectType.h"

#include "EnityManager.h"
#include "MessageDispatcher.h"
#include "MessageType.h"

#include <sstream>

const wstring Tittle = L"移动测试";

const int SCREENW = 1366;
const int SCREENH = 768;
Player player(2);
Sound sound;
Bullet* bullet;

//Enemy cc(100);

stringstream str;

void BootUp()
{
	//Map::Instance()->LoadTexture(L"wallhaven-490620.jpg", NULL);
	//Map::Instance()->SetPos(0, -350);
	//Map::Instance()->AddOneWall(0, 0, 1, 8000);
	////Map::Instance()->AddOneWall(0, 650, 800, 700);
	//Map::Instance()->AddOneWall(0, 750, 8000, 800);
	//
	//Map::Instance()->AddOneWall(600, 500, 800, 750);//中间的突起
	


	Map::Instance()->LoadTexture(L"Map1.png", NULL);
	
	Map::Instance()->AddOneWall(150, 0, 160, 768);
	Map::Instance()->AddOneWall(0, 535, 1366, 555);
	Map::Instance()->AddOneWall(900, 333, 1116, 555);
	Map::Instance()->AddOneWall(1116, 460, 1366, 555);

	EntityMgr->RegisterEntity(MAP);
	EntityMgr->RegisterEntity(&player);

	//EntityMgr->RegisterEntity(&cc);


	player.BootUp(200, 400);
	player.LoadTexture(L"redlead.png", NULL);

	//cc.BootUp(400, 0);
	//cc.LoadTexture(L"redlead.png", NULL);
	//lEnemy.push_front(&cc);

	ENM->AddOneEnemy(400, 300, 1);
	ENM->AddOneEnemy(500, 300, 1);
	ENM->AddOneWalkEnemy(600, 0, 300,600,1);
}

bool Game_Init(HWND window)
{
	srand(time(NULL));

	if (!Direct_Init(window, SCREENW, SCREENH, false))return false;
	if (!DirectInput_Init(window))return false;
	sound.Initialize(window);

	BootUp();

	return true;
}

void Game_Run(HWND window)
{
	//发送那些延时发送的消息,同时更新队列
	Dispatch->DispatchDelayedMessages();

	if (!d3ddev)return;
	
	if (d3ddev->BeginScene())
	{
		//清空缓存
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 100, 100), 1, 0);

		//----------开始绘制

		//地图绘制
		Map::Instance()->Render();

		//玩家子弹绘制
		for (auto& var : *player.Bullets())
		{
			var.Update();
			var.Render();
		}
		//玩家绘制
		player.Render();

		str.str("");
		//敌人绘制
		for (auto& var : lEnemy)
		{			
			var->Render();
			str << var->GetMotionFSM()->GetCurrentState();
			str << "\n";
		}

		//特效绘制
		Effect->Render();


		/*if (bullet)
		{
			bullet->Update();
			bullet->Render();
		}*/
		float x1 = player.GetGraphic()->mapPos.x;
		float x2 = player.GetGraphic()->mapPos.y;

		static LPD3DXFONT font = MakeFont("微软雅黑", 30);
		//static string text = "随便的一段话2333,并且听说会自动换行，简直厉害的不要不要的，我就试试看，要不在加大一下字体的大小？";
		string text = str.str();
		RECT rect2 = { 100,100,600,500 };
		font->DrawTextA(NULL, text.c_str(), text.length(), &rect2, DT_WORDBREAK, D3DCOLOR_XRGB(255, 255, 255));

		d3ddev->EndScene();

		//绘制图像
		d3ddev->Present(NULL, NULL, NULL, NULL);

		DirectInput_Update();
	}

	Effect->Update();
	player.Update();

	for (auto& var : lEnemy)
	{
		var->Update();
	}
	ENM->Update();


	Key_Check();

	RECT windowRect;
	GetWindowRect(window, &windowRect);
	Cursor::Instance()->Update(windowRect);
}

void Key_Check()
{
	if (keys[DIK_ESCAPE])gameover = true;

	//if (keys[DIK_L])
	//{
	//	static LARGE_INTEGER t_start, t_end, t_lock, t_frequency;
	//	t_end = t_start;
	//	QueryPerformanceCounter(&t_start);
	//	QueryPerformanceFrequency(&t_frequency);
	//	
	//	//这个就是两次事件的时间间隔了>:3
	//	double TimePassed = (t_start.QuadPart - t_end.QuadPart)*1.0 / t_frequency.QuadPart;
	//	if(TimePassed>0.025&&TimePassed<0.25)
	//	{
	//		if (!p1.Walk2Long)
	//		{
	//			p1.Situation = 1;
	//			//QueryPerformanceCounter(&t_start);
	//		}
	//	}
	//	else if(p1.Situation!=0&&p1.Situation!=2)
	//	{
	//		p1.walk();
	//	}
	//}

	if (keys[DIK_A])
	{
		static MStateMachine<Charcter>* fsm = player.GetMotionFSM();

		static LARGE_INTEGER t_start, t_end, t_lock, t_frequency;

		t_end = t_start;
		QueryPerformanceCounter(&t_start);
		QueryPerformanceFrequency(&t_frequency);

		//这个就是两次事件的时间间隔了>:3
		double TimePassed = (t_start.QuadPart - t_end.QuadPart)*1.0 / t_frequency.QuadPart;
		if (TimePassed>0.025&&TimePassed<0.25)
		{
			player.Dash();
		}
		else if (true)
		{
			//fsm->ChangeState(MWalking::Instance());
			player.Walk();
		}
	}

	if (keys[DIK_D])
	{
		static MStateMachine<Charcter>* fsm = player.GetMotionFSM();

		static LARGE_INTEGER t_start, t_end, t_lock, t_frequency;

		t_end = t_start;
		QueryPerformanceCounter(&t_start);
		QueryPerformanceFrequency(&t_frequency);

		//这个就是两次事件的时间间隔了>:3
		double TimePassed = (t_start.QuadPart - t_end.QuadPart)*1.0 / t_frequency.QuadPart;
		if (TimePassed>0.025&&TimePassed<0.25)
		{
			player.Dash();
		}
		else if (true)
		{
			//fsm->ChangeState(MWalking::Instance());
			player.Walk();
		}
	}

	if (keys[DIK_W])
	{
		player.Jump();
	}

	if (keys[DIK_J])
	{
		//Effect->PlayEffectAt(500, 500, Eft_Explosion);
		
		player.SetPos(200, 400);
	}

	if (Mouse_State.rgbButtons[0])
	{
		player.Shoot();

	}
	//static LARGE_INTEGER t_start, t_end, t_lock, t_frequency;
	//
	//QueryPerformanceCounter(&t_start);
	//QueryPerformanceFrequency(&t_frequency);
	////两次的间隔，隔开两次激发
	//double TimePassed = (t_start.QuadPart - t_end.QuadPart)*1.0 / t_frequency.QuadPart;
	//if (TimePassed > 0.25)
	//{
	//	//str.str("");
	//	//str << "射击";
	//	//player.Shoot();
	//	t_end = t_start;
	//}
	//else
	//{
	//	//str.str("");
	//	//str << "间歇";
	//}

	/*CharcterDetailData* data = player.GetDetailData();
	Graphic* graph = player.GetGraphic();

	float Mx = Cursor::Instance()->MapPos.x;
	float My = Cursor::Instance()->MapPos.y;

	D3DXVECTOR2 start = { graph->mapPos.x,graph->mapPos.y };
	D3DXVECTOR2 mouse = { Mx,My };

	bullet = new Bullet(player.ID(), start, mouse);*/
}