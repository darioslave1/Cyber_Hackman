#pragma once

#include "MovingEntity.h"

#include "StateMachine.h"

#include <vector>

class ShortestPathStep;

class Enemy : public MovingEntity
{
public:
	Enemy(int speed, long _id);
	~Enemy(void);

	void Init();

	void Update(float dt);

	//For pathfinding
	virtual void CalculatePath(){}

	void RandomMovement();

	bool mHasReachedTarget;

protected:

	CStateMachine<Enemy>* m_pEnemyFSM;

	cocos2d::CCArray* mShortestPath;
	std::vector<ShortestPathStep*> mShortestPathArray;

	void PopStepAndAnimate(float dt);

	

	void MoveToNextTile(float dt);
	void ChangeDirection();
	

	cocos2d::CCArray randomPoints;

	int tmpCounter;
};

