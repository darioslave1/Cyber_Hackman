#include "Enemy.h"

#include "PathPlanner.h"
#include "GameLevelMap.h"

using namespace cocos2d;

Enemy::Enemy(int speed, long _id) : MovingEntity(speed, _id),  mShortestPath(NULL), mHasReachedTarget(true)
{
	tmpCounter = 0;
}


Enemy::~Enemy(void)
{
}

void Enemy::Init()
{
	CCPoint entityPos = mEntitySprite->getPosition();
	mEntityTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(entityPos);
	mTargetTile = mEntityTile;

	randomPoints.addObject( new CCPoint(2,2));
	randomPoints.addObject( new CCPoint(22,12));
	randomPoints.addObject( new CCPoint(22,2));
	randomPoints.addObject( new CCPoint(2,13));
}

void Enemy::Update(float dt)
{

//	CalculatePath();

	if(mHasReachedTarget)
	{
		RandomMovement(dt);
	}

	PopStepAndAnimate(dt);

}

void Enemy::RandomMovement(float dt)
{
	cocos2d::cc_timeval now;
	//Get the source and destination Points
	CCPoint sourceTileCoords =  this->GetSpriteTile();

	//Get a random point
	CCSize sizeMap = PathPlanner::GetInstance()->GetLevelMap()->getTileMap()->getMapSize();

	CCTime::gettimeofdayCocos2d(&now, NULL);
	srand(now.tv_sec);
	int index = rand() % (int)randomPoints.count();
	CCPoint destTileCoords = *(dynamic_cast<CCPoint*>(randomPoints.objectAtIndex(index)));	// in case of a tentative number of get a valid tile > 3

	CCPoint tmpDestTile;
	int counter = 0;

	do{
		counter++;

		CCTime::gettimeofdayCocos2d(&now, NULL);
		srand(now.tv_sec);
		tmpDestTile.x = rand() % (int)sizeMap.width;
		tmpDestTile.y = rand() % (int)sizeMap.height;

		
		if( PathPlanner::GetInstance()->GetLevelMap()->isValidAndNotWallTile(tmpDestTile) )
		{	//valid tile
			destTileCoords = tmpDestTile;
			break;
		}

	}while(counter <=3);

	

	this->mShortestPath = NULL;


	//check that there is a path
	if(sourceTileCoords.equals(destTileCoords))
		return;


	mShortestPath = PathPlanner::GetInstance()->Start_A_Star(sourceTileCoords, destTileCoords);
	mHasReachedTarget = false;

}

void Enemy::PopStepAndAnimate(float dt)
{

	//check if remains path steps to go through
	if(mShortestPath)
	{
		if(mShortestPath->count() == 0 )
		{
			mHasReachedTarget = true;
			return;
		}
	}
	else
		return;

	MoveToNextTile(dt);
}


void Enemy::MoveToNextTile(float dt)
{

	CCPoint entityPos = mEntitySprite->getPosition();
	mEntityTile = this->GetSpriteTile();

	///////////////////// MOve to next step ////////////////////////
		
	/*** move until the center of the tile is reached ***/
	CCPoint targetPos = PathPlanner::GetInstance()->GetLevelMap()->positionForTileCoord(mTargetTile);

	//calculate the distance by two point, euclidean distance
	CCPoint distance = ccp( abs(targetPos.x - entityPos.x), abs(targetPos.y - entityPos.y) );

	//check if the center of tile is reached, so if the distance by center is the minimum possible
	if( (mDirection.x != 0 && distance.x > 4.1) ||  (mDirection.y != 0 && distance.y > 4.1) )	//at 60fps circa 4pixel
	{
		//not near the target, contiune to move to
		this->Move(dt);
	}
	else	
	{
		/*** central target point reached, set the position at the center of the target tile (for change direction correctly) ***/
		ChangeDirection();
	
	}//end else

////////////////////////////////////////


}

void Enemy::ChangeDirection()
{
	/*** central target point reached, set the position at the center of the target tile (for change direction correctly) ***/

	//set the position at the center of the target tile
	this->mEntitySprite->setPosition( PathPlanner::GetInstance()->GetLevelMap()->positionForTileCoord(mEntityTile) );

	//Get the next step to move to
	ShortestPathStep* step = dynamic_cast<ShortestPathStep*>(mShortestPath->objectAtIndex(0));

	mTargetTile = step->GetTilePosition();

	this->mDirection = ccpSub( mTargetTile, mEntityTile);

	// -m-Dir.y because the tile y is opposite of the cocos2d coordinate !!! IMPORTANT!!!
	mDirection.y *= -1;

	mShortestPath->removeObjectAtIndex(0);

}