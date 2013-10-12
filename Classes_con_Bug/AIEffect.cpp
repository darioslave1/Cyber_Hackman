#include "AIEffect.h"

using namespace cocos2d;

AIEffect::AIEffect() : Entity(10), mOpacityLevel(255), mIsActive(true)
{
	mEntitySprite = cocos2d::CCSprite::create("AI-Effect_1.png");
	CCAssert(mEntitySprite != NULL, "AI-Effect_1 not created");
	mEntitySprite->retain();
	mEntitySprite->setVisible(true);

	mOpacityLevel = mEntitySprite->getOpacity();
}


AIEffect::~AIEffect(void)
{
}

void AIEffect::Init()
{

}

//The return value is for GameOver
bool AIEffect::Update(float dt)
{
	if(!mIsActive)
		mEntitySprite->setVisible(false);

	return false;
}

void AIEffect::DecreaseOpacityLevel()
{
	mEntitySprite->setOpacity(mOpacityLevel - 30);
	mOpacityLevel = mEntitySprite->getOpacity();
}