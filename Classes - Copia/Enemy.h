#pragma once

#include "MovingEntity.h"

class Enemy : public MovingEntity
{
public:
	Enemy(int speed, long _id);
	~Enemy(void);

	void Init();

	void Update(float dt);

	//For pathfinding
	virtual void CalculatePath(){}

	

protected:

	cocos2d::CCArray *mShortestPath;

	void PopStepAndAnimate(float dt);

	void RandomMovement(float dt);

	void MoveToNextTile(float dt);
	void ChangeDirection();

	bool mHasReachedTarget;

	cocos2d::CCArray randomPoints;

	int tmpCounter;
};

