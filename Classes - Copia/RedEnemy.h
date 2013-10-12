#pragma once

#include "Enemy.h"

/* The Red Enemy follow the player movement */
class RedEnemy : public Enemy
{
public:
	RedEnemy();
	~RedEnemy(void);

	//For pathfinding
	void CalculatePath();

private:
};

