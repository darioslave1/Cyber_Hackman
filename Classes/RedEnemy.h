#pragma once

#include "Enemy.h"

/* The Red Enemy follow the player movement */
class RedEnemy : public Enemy
{
public:
	RedEnemy();
	~RedEnemy(void);

	//For pathfinding, follow the player, calculate the path toward the player position
	void CalculatePath();

private:
};

