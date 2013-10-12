#include "MovingEntity.h"

#include "PathPlanner.h"
#include "EntityManager.h"
#include "Enemy.h"


using namespace cocos2d;

MovingEntity::MovingEntity(int speed, long _id) : Entity(_id), mSpeed(speed), 
	newRotation(0.f), mDirection(ccp(0,0)), mTargetTile(ccp(0,0)),
	mEntityTile(ccp(0,0))
{
}


MovingEntity::~MovingEntity(void)
{
}

CCPoint MovingEntity::GetDirection()
{
	return mDirection;
}

bool MovingEntity::Move(float dt)
{
	CCPoint entityPos = mEntitySprite->getPosition();

	//limit the movement to 4 pixel per frame, important for center tile check
	float movement = 0.f;
	if(mSpeed*dt > 4)
		movement = 4.f;
	else
		movement = mSpeed*dt;

	CCPoint newPos = ccp( entityPos.x + mDirection.x * movement , entityPos.y + mDirection.y* movement );

	
	if(CollisionDetection(newPos))
	{
		return true;
	}

	//Set new position and tile for entity 
	this->mEntitySprite->setPosition(newPos);
	this->mEntityTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(newPos);

	return false;
}


bool MovingEntity::CollisionDetection(CCPoint nextPos)
{

	//check if in the tile of the map there is another entity
	CCPoint newTile = PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(nextPos);
	std::vector<Entity*>* list = EntityManager::GetInstance()->GetEntityList();
	for(std::vector<Entity*>::iterator iter = list->begin(); iter != list->end(); iter++)
	{
		//if there is another entity in the tile, don't move
		if( this->Id != (*iter)->Id)
		{
			//if 2 different entities are on the same tile
			if(newTile.equals( (*iter)->GetSpriteTile()) )
			{	//collision detected!

				//Reflection (RTTI: Runtime type identification)
				//This is not the player, so if the *iter is tha player we have collision with player
				//else collision beetwen enemy
				Player* p = dynamic_cast<Player*>(*iter);

				//check player
				if(this->Id == 1 )
				{	//collision detected with Player!
	//				EntityManager::GetInstance()->SetGameOver(true);
					return true;
				}

				if(p)
				{
	//				EntityManager::GetInstance()->SetGameOver(true);
					return true;
				}
				else
				{// two enemy
					Enemy* enemy = dynamic_cast<Enemy*>(*iter);
					if(enemy)
					{
						//two enemy with opposite direction
						return false;	//bypass
					}
				}

			}
		}
	}

	return false;
}