#include "State.h"

class Enemy;

//------------------------------------------------------------------------
//
//  Name:   EnemyPatrolState.h
//
//  Desc:   Singleton Class to PatrolState
//
//  Author: Dario Schiavone
//
// The enemy follow a random path
//------------------------------------------------------------------------


class EnemyPatrolState : public IState<Enemy>
{
private: 
	EnemyPatrolState(){}

public:

	//this is a singleton
	static EnemyPatrolState* Instance();

	//this will execute when the state is entered
	void Enter(Enemy* ptrEnemy);

	//this is the states normal update function
	void Execute(Enemy* ptrEnemy);
	
	//this will execute when the state is exited
	virtual void Exit(Enemy* ptrEnemy);

};