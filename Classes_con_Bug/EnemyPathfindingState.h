#include "State.h"

class Enemy;

//------------------------------------------------------------------------
//
//  Name:   EnemyPathfindingState.h
//
//  Desc:   Singleton Class to Pathfinding State
//
//  Author: Dario Schiavone
//
// The enemy follow a target tile
//------------------------------------------------------------------------

class EnemyPathfindingState : public IState<Enemy>
{
private: 
	EnemyPathfindingState(){}

	int mNumMovedOutLOS;
	int mPreviousNumMoved;

	float mTimer;

public:

	//this is a singleton
	static EnemyPathfindingState* Instance();

	//this will execute when the state is entered
	void Enter(Enemy* ptrEnemy);

	//this is the states normal update function
	void Execute(Enemy* ptrEnemy);
	
	//this will execute when the state is exited
	virtual void Exit(Enemy* ptrEnemy);

};