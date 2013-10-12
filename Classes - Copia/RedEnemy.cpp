#include "RedEnemy.h"

#include "PathPlanner.h"
#include "GameLevelMap.h"

using namespace cocos2d;

RedEnemy::RedEnemy() : Enemy(120, 2)
{
	mEntitySprite = cocos2d::CCSprite::create("Red.png");
	CCAssert(mEntitySprite != NULL, "Red not created");
	mEntitySprite->retain();

}


RedEnemy::~RedEnemy(void)
{
}

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

	mShortestPath = PathPlanner::GetInstance()->Start_A_Star(sourceTileCoords, destTileCoords);

} 