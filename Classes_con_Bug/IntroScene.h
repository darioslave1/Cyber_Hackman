#pragma once

#include "cocos2d.h"

class IntroScene : public cocos2d::CCLayerColor
{
public:
	IntroScene(void);
	~IntroScene(void);

    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuNewCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(IntroScene);
};

