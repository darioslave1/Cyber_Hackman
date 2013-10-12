#include "EnemyPatrolState.h"
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

}


void EnemyPatrolState::Execute(Enemy* ptrEnemy)
{
	if( ptrEnemy->mHasReachedTarget)
	{
		ptrEnemy->RandomMovement();
	}
	
}

void EnemyPatrolState::Exit(Enemy* ptrEnemy)
{

}