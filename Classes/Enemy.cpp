#include "Enemy.h"

#include "PathPlanner.h"
#include "GameLevelMap.h"



using namespace cocos2d;

Enemy::Enemy(int speed, long _id) : MovingEntity(speed, _id), mHasReachedTarget(true), m_pEnemyFSM(NULL),
	mDeltaTime(0.f), mNumOfTileMoved(0)
{
	tmpCounter = 0;
}


Enemy::~Enemy(void)
{
	randomPoints.removeAllObjects();

	if(m_pEnemyFSM)
		delete m_pEnemyFSM;
}

void Enemy::Init()
{
	randomPoints.addObject( new CCPoint(2,2));
	randomPoints.addObject( new CCPoint(22,12));
	randomPoints.addObject( new CCPoint(22,2));
	randomPoints.addObject( new CCPoint(2,13));

	this->mEntityTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(this->GetSpritePosition());

	m_pEnemyFSM->ChangeState(m_pEnemyFSM->GetCurrentState());
}

void Enemy::ChangeState(IState<Enemy>* state)
{
	m_pEnemyFSM->ChangeState(state);
}

bool Enemy::Update(float dt)
{
	mDeltaTime = dt;

	//has finished he's movement only at the center of tile
	if(mIsInCenterOfTile)
		mNumOfTileMoved++;

	m_pEnemyFSM->Update();	

	bool exitGame = MoveToNextTile(dt);
	
	return exitGame;

}

void Enemy::RandomMovement()
{
	mShortestPathArray.clear();

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


	//check that there is a path
	if(sourceTileCoords.equals(destTileCoords))
		return;

	mShortestPathArray = PathPlanner::GetInstance()->Start_A_Star(sourceTileCoords, destTileCoords);
	mHasReachedTarget = false;

}


bool Enemy::MoveToNextTile(float dt)
{

	CCPoint entityPos = mEntitySprite->getPosition();
//	mEntityTile = this->GetSpriteTile();

	///////////////////// MOve to next step ////////////////////////
		
	/*** move until the center of the tile is reached ***/
	CCPoint targetPos = PathPlanner::GetInstance()->GetLevelMap()->positionForTileCoord(mTargetTile);

	//calculate the distance by two point, euclidean distance
	CCPoint distance = ccp( abs(targetPos.x - entityPos.x), abs(targetPos.y - entityPos.y) );

	if(distance.x > 32.f || distance.y > 32.f)
		distance = distance;

	//check if the center of tile is reached, so if the distance by center is the minimum possible
	if( (mDirection.x != 0 && distance.x > 4.f) ||  (mDirection.y != 0 && distance.y > 4.f) )	//at 60fps circa 4pixel
	{
		//not near the target, contiune to move to
		bool exitGame = this->Move(dt);
		if(exitGame)
			return true;

		mIsInCenterOfTile = false;
	}
	else	
	{
		/*** central target point reached, set the position at the center of the target tile (for change direction correctly) ***/
		ChangeDirection();
	
	}//end else

////////////////////////////////////////

	return false;
}

void Enemy::ChangeDirection()
{
	/*** central target point reached, set the position at the center of the target tile (for change direction correctly) ***/

		if(mShortestPathArray.size() != 0 )
		{

			//set the position at the center of the target tile
			this->mEntitySprite->setPosition( PathPlanner::GetInstance()->GetLevelMap()->positionForTileCoord(mEntityTile) );

			//Get the next step to move to
			ShortestPathStep* step = mShortestPathArray.at(0);

			mTargetTile = step->GetTilePosition();

			this->mDirection = ccpSub( mTargetTile, mEntityTile);

			// -m-Dir.y because the tile y is opposite of the cocos2d coordinate !!! IMPORTANT!!!
			mDirection.y *= -1;

			mShortestPathArray.erase(mShortestPathArray.begin());

			mIsInCenterOfTile = true;
		}
		else
			mHasReachedTarget = true;	//new random movement

		
}


bool Enemy::IsPlayerInLOS()
{
	CCPoint playerTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition( 
		PathPlanner::GetInstance()->GetPlayerPosition());

	CCPoint entTile = this->GetEntityTile();

	//1. Condition: Player and entity in the same row or column
	if( playerTile.x == this->GetEntityTile().x || playerTile.y == this->GetEntityTile().y )
	{
		float dist = 0.f;

		//same column
		if( playerTile.x == this->GetEntityTile().x )
		{
			dist = fabs(playerTile.y - entTile.y);

			//2. condition: distance between player and entity < 5 cels
			if ( dist > 5.f)
				return false;
			else
			{
				float dir = (playerTile.y - entTile.y) / dist;
				CCPoint tmpTile = entTile;
				while(tmpTile.y != playerTile.y)
				{
					tmpTile.y += dir;
					
					//3. condition, if there is a wall in the path, no LOS
					if(PathPlanner::GetInstance()->GetLevelMap()->IsWallAtTileCoords(tmpTile))
						return false;
				}//end while

				//if the while end, there are no walls
				return true;
			}
		}

		//same row
		if( playerTile.y == this->GetEntityTile().y )
		{
			dist = fabs(playerTile.x - entTile.x);

			//2. condition: distance between player and entity < 5 cels
			if ( dist > 5.f)
				return false;
			else
			{	
				float dir = (playerTile.x - entTile.x) / dist;
				CCPoint tmpTile = entTile;
				while(tmpTile.x != playerTile.x)
				{
					tmpTile.x += dir;

					//3. condition, if there is a wall in the path, no LOS
					if(PathPlanner::GetInstance()->GetLevelMap()->IsWallAtTileCoords(tmpTile))
						return false;
				}//end while

				//if the while end, there are no walls
				return true;
			}
		}

	}


	return false;

}