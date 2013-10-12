#include "EnemyPathfindingState.h"
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
}


void EnemyPathfindingState::Execute(Enemy* ptrEnemy)
{
	ptrEnemy->CalculatePath();
}

void EnemyPathfindingState::Exit(Enemy* ptrEnemy)
{

}