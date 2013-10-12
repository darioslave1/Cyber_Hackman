#include "State.h"

class Player;

//------------------------------------------------------------------------
//
//  Name:   PlayerNormalState.h
//
//  Desc:   Singleton Class to PlayerNormalState
//
//  Author: Dario Schiavone
//
// The player is vulnerable 
//------------------------------------------------------------------------


class PlayerNormalState : public IState<Player>
{
private: 
	PlayerNormalState(){}

public:

	//this is a singleton
	static PlayerNormalState* Instance();

	//this will execute when the state is entered
	void Enter(Player* ptrPlayer);

	//this is the states normal update function
	void Execute(Player* ptrPlayer);
	
	//this will execute when the state is exited
	virtual void Exit(Player* ptrPlayer);

};