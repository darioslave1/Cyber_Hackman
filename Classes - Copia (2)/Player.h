#pragma once

#include "MovingEntity.h"

class GameLevelMap;

class Player : public MovingEntity, public cocos2d::CCTargetedTouchDelegate
{
public:
	Player();
	~Player(void);

	void Update(float dt);

	void Init();

	void SetMoveVector(cocos2d::CCPoint vec);
	void MoveToDirection(cocos2d::CCPoint nextDirection, float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();

private:

	cocos2d::CCPoint touchBegan;
	cocos2d::CCPoint mNextTouchedDirection;
};

