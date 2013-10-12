#pragma once

#include "Entity.h"

/* The AI EFFECT*/
class AIEffect : public Entity
{
public:
	AIEffect();
	~AIEffect(void);

	bool Update(float dt);

	void Init();

	bool isActive(){return mIsActive;}
	void Disable(){ mIsActive = false;}
	void Enable(){mIsActive = true;}

	void DecreaseOpacityLevel();

private:

	int mOpacityLevel;
	bool mIsActive;
};

