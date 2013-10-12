#include "Entity.h"

#include "PathPlanner.h"

using namespace cocos2d;

Entity::Entity(long _id) : Id(_id), mEntitySprite(NULL)
{
	
}


Entity::~Entity(void)
{
}

void Entity::SetSpritePosition(CCPoint pos)
{
	mEntitySprite->setPosition(pos);
}

CCPoint Entity::GetSpritePosition()
{
	return mEntitySprite->getPosition();
}

CCSprite* Entity::GetEntitySprite()
{
	return mEntitySprite;
}

CCPoint Entity::GetSpriteTile()
{
	return PathPlanner::GetInstance()->GetLevelMap()->tileCoordForPosition(GetSpritePosition());
}