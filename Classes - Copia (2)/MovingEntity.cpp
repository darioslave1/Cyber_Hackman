#include "MovingEntity.h"

#include "PathPlanner.h"

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

void MovingEntity::Move(float dt)
{
	CCPoint entityPos = mEntitySprite->getPosition();

	float movement = 0.f;
	if(mSpeed*dt > 4)
		movement = 4.f;
	else
		movement = mSpeed*dt;

	CCPoint newPos = ccp( entityPos.x + mDirection.x * movement , entityPos.y + mDirection.y* movement );

	this->mEntitySprite->setPosition(newPos);
}

