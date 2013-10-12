 #ifndef _WINNER_SCENE_H_
 #define _WINNER_SCENE_H_
 
#include "cocos2d.h"

class WinnerLayer : public cocos2d::CCLayerColor
{
public:
	virtual ~WinnerLayer();
	WinnerLayer();
	virtual bool init();
	CREATE_FUNC(WinnerLayer);

	// a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);

};

class WinnerScene : public cocos2d::CCScene
{
public:
	virtual ~WinnerScene();
	WinnerScene();
	virtual bool init();
	CREATE_FUNC(WinnerScene);

	CC_SYNTHESIZE_READONLY(WinnerLayer*, mWinnerLayer , WinnerLayer);	// 3 param: Get+GameOverLayer
};



#endif // _WINNER_SCENE_H_