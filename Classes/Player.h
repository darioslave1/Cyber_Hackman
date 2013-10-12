#pragma once

#include "MovingEntity.h"

class GameLevelMap;

class Player : public MovingEntity, public cocos2d::CCTargetedTouchDelegate
{
public:

	Player();
	~Player(void);

	bool Update(float dt);
	
	void Init();

	void SetMoveVector(cocos2d::CCPoint vec);
	bool MoveToDirection(cocos2d::CCPoint nextDirection, float dt);

	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();

//touch effect
	int m_iCount;
    void resetMotionStreak();
    void addMotionStreakPoint(cocos2d::CCPoint point);

private:

	cocos2d::CCPoint touchBegan;
	cocos2d::CCPoint mNextTouchedDirection;
	
	cocos2d::CCMotionStreak* mStreakPlayer;

	bool winner;
};

