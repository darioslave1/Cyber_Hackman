#pragma once

#include "cocos2d.h"

#include "PathPlanner.h"

#include "SimpleAudioEngine.h"

class GameLevel : public cocos2d::CCLayerColor
{
public:
	GameLevel(void);
	~GameLevel(void);

	virtual bool init();  

	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameLevel);

	/*
	void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	*/
	void Update(float dt);


private:

	bool mStopGame;
	bool mExitLevel;
	float mDoorScale;

	cocos2d::CCSprite* mDoorSprite;


	GameLevelMap* mLevelMap;
	
};

