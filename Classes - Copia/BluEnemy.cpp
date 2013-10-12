#include "BluEnemy.h"

#include "PathPlanner.h"
#include "GameLevelMap.h"

using namespace cocos2d;

BluEnemy::BluEnemy() : Enemy(100, 3)
{
	mEntitySprite = cocos2d::CCSprite::create("Blu.png");
	CCAssert(mEntitySprite != NULL, "Blu not created");
	mEntitySprite->retain();
}


BluEnemy::~BluEnemy(void)
{
}

void BluEnemy::CalculatePath()
{
	GameLevelMap* pLevelMap = PathPlanner::GetInstance()->GetLevelMap();

	//Get the source and destination Points
	CCPoint sourceTileCoords =  pLevelMap->tileCoordForPosition(mEntitySprite->getPosition());

	CCPoint destTileCoords = pLevelMap->tileCoordForPosition(PathPlanner::GetInstance()->GetPlayerPosition());

	/*** Predict the player movement, calculate the destination target using the player direction */
	CCPoint tmpDestTileCoords = ccp(destTileCoords.x + PathPlanner::GetInstance()->GetPlayerDirection().x,
		destTileCoords.y - PathPlanner::GetInstance()->GetPlayerDirection().y);

	if(pLevelMap->isValidAndNotWallTile(tmpDestTileCoords))
	{
		//if the next position of the player is valid, set as destination
		destTileCoords = tmpDestTileCoords;
	}
	


	this->mShortestPath = NULL;


	//check that there is a path
	if(sourceTileCoords.equals(destTileCoords))
		return;

	//check if the touch is in a wall
	if(PathPlanner::GetInstance()->GetLevelMap()->IsWallAtTileCoords(destTileCoords))
		return;

	mShortestPath = PathPlanner::GetInstance()->Start_A_Star(sourceTileCoords, destTileCoords);

} 