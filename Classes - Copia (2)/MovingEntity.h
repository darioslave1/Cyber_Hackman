#pragma once

#include "Entity.h"

//Interface

class MovingEntity : public Entity
{
public:
	MovingEntity(int speed, long _id);
	~MovingEntity(void);

	void Move(float dt);

	void MoveToDirection(cocos2d::CCPoint nextDirection, float dt);

	cocos2d::CCPoint GetDirection();

	void SetEntityTile(cocos2d::CCPoint tile) { mEntityTile = tile; }
	void SetTargetTile(cocos2d::CCPoint tile) { mTargetTile = tile; };

	cocos2d::CCPoint GetEntityTile(){ return mEntityTile; }
	cocos2d::CCPoint GetTargetTile(){ return mTargetTile; }

protected:
	cocos2d::CCPoint mTargetTile;
	cocos2d::CCPoint mEntityTile;
	cocos2d::CCPoint mDirection;
//	cocos2d::CCPoint mNextDirection;
	int mSpeed;

	float newRotation;

};

