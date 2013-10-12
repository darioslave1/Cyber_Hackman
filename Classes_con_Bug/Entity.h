#pragma once

#include "cocos2d.h"

class PathPlanner;

class Entity : public cocos2d::CCNode
{
public:
	Entity(long _id);
	~Entity(void);

	virtual bool Update(float dt){return true;}

	void SetSpritePosition(cocos2d::CCPoint pos);
	cocos2d::CCPoint GetSpritePosition();

	cocos2d::CCPoint GetSpriteTile();

	virtual void Init(){}

	cocos2d::CCSprite* GetEntitySprite();

	bool IsInCenterOfTile(){ return mIsInCenterOfTile; }

	long Id;
	

protected:
	cocos2d::CCSprite* mEntitySprite;

	bool mIsInCenterOfTile;
};

