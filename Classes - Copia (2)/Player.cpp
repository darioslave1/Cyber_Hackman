#include "Player.h"


#include "PathPlanner.h"


using namespace cocos2d;

Player::Player() : MovingEntity(100, 1), touchBegan(ccp(0,0)), mNextTouchedDirection(ccp(0,0))
{

	this->mEntitySprite = cocos2d::CCSprite::create("1.png");
	CCAssert(mEntitySprite != NULL, "Player not created");
	mEntitySprite->retain();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


Player::~Player(void)
{
	mEntitySprite->release();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void Player::Init()
{
	CCPoint playerPos = mEntitySprite->getPosition();
	mEntityTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(playerPos);
	mTargetTile = mEntityTile;
}


/*** touch delegates implements ***/

bool Player::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	touchBegan = PathPlanner::GetInstance()->GetLevelMap()->getTileMap()->convertTouchToNodeSpace(touch);

    return true;
}

void Player::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchEnd = PathPlanner::GetInstance()->GetLevelMap()->getTileMap()->convertTouchToNodeSpace(touch);
	CCPoint moveVec;

	//create the vector of player movement
	float deltaX = fabs(touchEnd.x - touchBegan.x);
	float deltaY = fabs(touchEnd.y - touchBegan.y);


	if(deltaX >= deltaY)	//move left or right
	{
		if(touchEnd.x >= touchBegan.x)	//move right
		{
			moveVec = ccp(1, 0);
			newRotation = 90.f;
		}
		else
		{
			moveVec = ccp(-1, 0);	//move left
			newRotation = -90.f;
		}
	}
	else	//move up or down
	{
		if(touchEnd.y >= touchBegan.y)	//move up
		{
			moveVec = ccp(0, 1);
			newRotation = 0.f;
		}
		else
		{
			moveVec = ccp(0, -1);	//move down
			newRotation = 180.f;
		}
	}
	
	SetMoveVector(moveVec);

}


void Player::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

	ccTouchMoved(touch, event);
	
} 

/******end Touch ****/




void Player::Update(float dt)
{

	MoveToDirection(mNextTouchedDirection, dt);

}

void Player::SetMoveVector(cocos2d::CCPoint vec)
{
	mNextTouchedDirection = vec;

}


void Player::MoveToDirection(cocos2d::CCPoint nextDirection, float dt)
{
	//helper
	GameLevelMap* pLevelMap = PathPlanner::GetInstance()->GetLevelMap();

	CCPoint entityPos = mEntitySprite->getPosition();
	mEntityTile = pLevelMap->tileCoordForPosition(entityPos);

	//check the target tile is a valid tile
	if(!pLevelMap->isValidAndNotWallTile(mTargetTile))
	{
		mTargetTile = mEntityTile;	//not a valid tile
	}

	/*** move until the center of the tile is reached ***/

	CCPoint targetPos = pLevelMap->positionForTileCoord(mTargetTile);

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

		//set the position at the center of the target tile
		this->mEntitySprite->setPosition( pLevelMap->positionForTileCoord(mEntityTile) );

		// to change direction?
		if(!nextDirection.equals(mDirection))
		{
			/*** yes, the entity should be change it's direction **/

			//calculate the new target
			CCPoint tmpTarget = ccp(mEntityTile.x + nextDirection.x, mEntityTile.y - nextDirection.y);

			//check if is a valid coordinate
			if(pLevelMap->isValidAndNotWallTile(tmpTarget))
			{	
				/** is valid, change direction **/

				mDirection = nextDirection;

				//rotate to the new direction
				mEntitySprite->setRotation(newRotation);

			}
		}

		//calculate the new target tile
		mTargetTile = ccp(mEntityTile.x + mDirection.x, mEntityTile.y - mDirection.y);
		//check validity
		if(!pLevelMap->isValidAndNotWallTile(mTargetTile))
		{	//not valid
			mTargetTile = mEntityTile;
		}

	}//end else
}


/*** TOUCH DELEGATE ***/

void Player::touchDelegateRetain()
{
    this->retain();
}

void Player::touchDelegateRelease()
{
	this->release();
}