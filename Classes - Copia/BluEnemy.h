#pragma once

#include "Enemy.h"


/* The Blu Enemy try to anticipate the player movement */
class BluEnemy : public Enemy
{
public:
	BluEnemy();
	~BluEnemy(void);

	//For pathfinding
	void CalculatePath();

private:

};

