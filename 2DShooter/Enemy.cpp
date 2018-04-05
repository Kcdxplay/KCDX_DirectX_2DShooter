#include "Enemy.h"
#include "CharcterOwnedMState.h"
#include "Map.h"

//真的可以改善生活2333
#define NewEnemy listOfEnemy.front()

EnemyList * EnemyList::Instance()
{
	static EnemyList instance;
	return &instance;
}
void EnemyList::Update()
{
	for (auto& var : listOfRemove)
	{
		listOfEnemy.remove(var);

		delete(var);
	}
	listOfRemove.clear();
}
void EnemyList::AddOneEnemy(float x, float y, int type)
{
	listOfEnemy.push_front(new Enemy(EID));

	NewEnemy->BootUp(x, y, type);
	NewEnemy->LoadTexture(L"redlead.png", NULL);

	EntityMgr->RegisterEntity(NewEnemy);

	EID++;
}

void EnemyList::AddOneWalkEnemy(float x, float y, float map1, float map2, int type)
{
	if (map1 > map2)
	{
		AddOneEnemy(x, y, type);
		return;
	}

	listOfEnemy.push_front(new Enemy(EID));

	NewEnemy->BootUp(x, y, type);
	NewEnemy->LoadTexture(L"redlead.png", NULL);
	NewEnemy->GetAIFSM()->SetCurrentState(EnemyAWalkAround::Instance());

	NewEnemy->SetAreaLeft(map1);
	NewEnemy->SetAreaRight(map2);

	EntityMgr->RegisterEntity(NewEnemy);

	EID++;

}

bool Enemy::HandleMessage(const Telegram & msg)
{
	return pMStateMachine->HandleMessage(msg);
}

void Enemy::Update()
{
	CharcterDetailData* pData = GetDetailData();
	Graphic* pGraph = GetGraphic();

	pAStateMachine->Update();
	pMStateMachine->Update();

	RectSet();

	//判断脚下是否有平台，没有就开始掉落
	RECT rect{ 0,0,0,0 };
	rect = preCheck[2];
	if (!Map::Instance()->CheckWallCollision(rect))
	{
		pMStateMachine->ChangeState(EnemyMFalling::Instance());
	}

	Map::Instance()->GetPaintPos(
		pGraph->mapPos.x,
		pGraph->mapPos.y,
		&pGraph->paintPos.x,
		&pGraph->paintPos.y);
}
void Enemy::Render()
{
	spriteOBJ->Begin(D3DXSPRITE_ALPHABLEND);
	spriteOBJ->Draw(graph.texture, NULL, NULL, &graph.paintPos, D3DCOLOR_XRGB(255, 255, 255));
	spriteOBJ->End();
}