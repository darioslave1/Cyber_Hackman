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

	bool Update(float dt);

	//For pathfinding
	virtual void CalculatePath(){}

	//For patrol
	void RandomMovement();

	//Is player in the line of sight of the enemy?
	bool IsPlayerInLOS();

	bool mHasReachedTarget;

	void ChangeState(IState<Enemy>* state);

	float GetDeltaTime(){ return mDeltaTime;}

	const int GetNumOfTileMoved(){ return mNumOfTileMoved; }
	void ResetNumOfTileMoved(){ mNumOfTileMoved = 0; }

	void ClearShortestPath(){ mShortestPathArray.clear();}

protected:

	CStateMachine<Enemy>* m_pEnemyFSM;

	std::vector<ShortestPathStep*> mShortestPathArray;

	void PopStepAndAnimate(float dt);

	bool MoveToNextTile(float dt);
	void ChangeDirection();
	
	cocos2d::CCArray randomPoints;

	int tmpCounter;

	float mDeltaTime;
	int mNumOfTileMoved;
};

