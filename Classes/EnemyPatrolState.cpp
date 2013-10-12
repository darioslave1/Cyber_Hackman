#include "EnemyPatrolState.h"
#include "EnemyPathfindingState.h"
#include "Enemy.h"

#include "cocos2d.h"
#include "PathPlanner.h"

using namespace cocos2d;

//------------------------------------------------------------------------
//
//  Name:   EnemyPatrolState.h
//
//  Author: Dario Schiavone
//
//------------------------------------------------------------------------

EnemyPatrolState* EnemyPatrolState::Instance()
{
	static EnemyPatrolState instance;
	return &instance;
}

void EnemyPatrolState::Enter(Enemy* ptrEnemy)
{
	ptrEnemy->ResetNumOfTileMoved();

	ptrEnemy->SetTargetTile( ptrEnemy->GetEntityTile());
}


void EnemyPatrolState::Execute(Enemy* ptrEnemy)
{
	if( ptrEnemy->IsPlayerInLOS() || ptrEnemy->GetNumOfTileMoved() > 14)
	{
		//only if it is in the center
		if(ptrEnemy->IsInCenterOfTile())
			ptrEnemy->ChangeState(EnemyPathfindingState::Instance());
	}
	else
		if( ptrEnemy->mHasReachedTarget)
		{
			ptrEnemy->RandomMovement();
		}
	
}

void EnemyPatrolState::Exit(Enemy* ptrEnemy)
{
	ptrEnemy->ClearShortestPath();
}