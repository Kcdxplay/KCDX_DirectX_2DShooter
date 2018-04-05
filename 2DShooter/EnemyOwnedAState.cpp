#include "EnemyOwnedAState.h"
#include "MessageType.h"
#include "GlobalEffect.h"
#include "EffectType.h"
#include "Enemy.h"

#define pEnemyMFSM pCharcter->GetMotionFSM()

EnemyAWalkAround * EnemyAWalkAround::Instance()
{
	static EnemyAWalkAround instance;
	return &instance;
}

void EnemyAWalkAround::Enter(Charcter * pCharcter)
{
}
void EnemyAWalkAround::Execute(Charcter * pCharcter)
{
	pGraph = pCharcter->GetGraphic();

	Enemy* enm = (Enemy*)pCharcter;

	if (pEnemyMFSM->GetCurrentState() != EnemyMFalling::Instance())
	{
		//如果他站着不动>:3
		if (pEnemyMFSM->GetCurrentState() == EnemyMStanding::Instance())
		{
			pEnemyMFSM->ChangeState(EnemyMWalkLeft::Instance());
			return;
		}

		//如果他在往左走
		if (pEnemyMFSM->GetCurrentState() == EnemyMWalkLeft::Instance())
		{
			if (pGraph->mapPos.x < enm->AreaLeft())
			{
				pEnemyMFSM->ChangeState(EnemyMWalkRight::Instance());
				return;
			}
		}

		//如果他在往右走
		if (pEnemyMFSM->GetCurrentState() == EnemyMWalkRight::Instance())
		{
			if (pGraph->mapPos.x > enm->AreaRight())
			{
				pEnemyMFSM->ChangeState(EnemyMWalkLeft::Instance());
				return;
			}
		}
	}
}
void EnemyAWalkAround::Exit(Charcter * pCharcter)
{
}
bool EnemyAWalkAround::OnMessage(Charcter * pCharcter, const Telegram & msg)
{
	return false;
}
