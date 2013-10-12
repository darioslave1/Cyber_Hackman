#include "RedEnemy.h"

#include "PathPlanner.h"
#include "GameLevelMap.h"

#include "EnemyPatrolState.h"

using namespace cocos2d;

RedEnemy::RedEnemy() : Enemy(80, 2)
{
	mEntitySprite = cocos2d::CCSprite::create("Red.png");
	CCAssert(mEntitySprite != NULL, "Red not created");
	mEntitySprite->retain();

	/*** State Machine Code ***/
	m_pEnemyFSM = new CStateMachine<Enemy>(this);
	m_pEnemyFSM->SetPreviousState(EnemyPatrolState::Instance());
	m_pEnemyFSM->SetCurrentState(EnemyPatrolState::Instance());
	m_pEnemyFSM->SetGlobalState(NULL);

}


RedEnemy::~RedEnemy(void)
{
}

//For pathfinding, follow the player, calculate the path toward the player position
void RedEnemy::CalculatePath()
{
	//Get the source and destination Points
	CCPoint sourceTileCoords =  PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(mEntitySprite->getPosition());
	CCPoint destTileCoords =  PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(
		PathPlanner::GetInstance()->GetPlayerPosition());

	this->mShortestPath = NULL;


	//check that there is a path
	if(sourceTileCoords.equals(destTileCoords))
		return;

	//check if the touch is in a wall
	if(PathPlanner::GetInstance()->GetLevelMap()->IsWallAtTileCoords(destTileCoords))
		return;

	mShortestPathArray = PathPlanner::GetInstance()->Start_A_Star(sourceTileCoords, destTileCoords);

} 