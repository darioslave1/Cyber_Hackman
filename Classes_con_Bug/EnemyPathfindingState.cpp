#include "EnemyPathfindingState.h"
#include "EnemyPatrolState.h"
#include "Enemy.h"

#include "cocos2d.h"
#include "PathPlanner.h"

using namespace cocos2d;

//------------------------------------------------------------------------
//
//  Name:   EnemyPathfindingState.h
//
//  Author: Dario Schiavone
//
//------------------------------------------------------------------------

EnemyPathfindingState* EnemyPathfindingState::Instance()
{
	static EnemyPathfindingState instance;
	return &instance;
}

void EnemyPathfindingState::Enter(Enemy* ptrEnemy)
{
	CCPoint entityPos = ptrEnemy->GetEntitySprite()->getPosition();
	ptrEnemy->SetEntityTile(PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(entityPos));
	ptrEnemy->SetTargetTile( ptrEnemy->GetEntityTile());

	ptrEnemy->ResetNumOfTileMoved();
	mPreviousNumMoved = 0;
	mNumMovedOutLOS = 0;
	mTimer = 0.f;
}


void EnemyPathfindingState::Execute(Enemy* ptrEnemy)
{
	//if the player is in line of sight, continue to following
	if(ptrEnemy->IsPlayerInLOS())
	{
		mTimer = 0.f;
		ptrEnemy->CalculatePath();
	}
	else
	{
		//calculate 1 second
		mTimer += ptrEnemy->GetDeltaTime();

		if(mTimer > 2.0)
		{
			//only if it is in the center
			if(ptrEnemy->IsInCenterOfTile())
				ptrEnemy->ChangeState(EnemyPatrolState::Instance());
		}
		else
			ptrEnemy->CalculatePath();

	}

}

void EnemyPathfindingState::Exit(Enemy* ptrEnemy)
{
	ptrEnemy->ClearShortestPath();
}