#pragma once

#include "Enemy.h"


/* The Blu Enemy try to anticipate the player movement */
class BluEnemy : public Enemy
{
public:
	BluEnemy();
	~BluEnemy(void);

	//For pathfinding, the difference from the Red is that it calculate the next step of the player and predict his movement
	void CalculatePath();

private:

};

