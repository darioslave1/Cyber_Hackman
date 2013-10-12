#include "PlayerNormalState.h"
#include "Player.h"

#include "cocos2d.h"
#include "PathPlanner.h"

using namespace cocos2d;

//------------------------------------------------------------------------
//
//  Name:   PlayerNormalState.h
//
//  Author: Dario Schiavone
//
//------------------------------------------------------------------------

PlayerNormalState* PlayerNormalState::Instance()
{
	static PlayerNormalState instance;
	return &instance;
}

void PlayerNormalState::Enter(Player* ptrPlayer)
{
	
}


void PlayerNormalState::Execute(Player* ptrPlayer)
{

	
}

void PlayerNormalState::Exit(Player* ptrPlayer)
{
	
}