 #ifndef _GAME_OVER_SCENE_H_
 #define _GAME_OVER_SCENE_H_
 
#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
	virtual ~GameOverLayer();
	GameOverLayer();
	virtual bool init();
	CREATE_FUNC(GameOverLayer);

	// a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);

};

class GameOverScene : public cocos2d::CCScene
{
public:
	virtual ~GameOverScene();
	GameOverScene();
	virtual bool init();
	CREATE_FUNC(GameOverScene);

	CC_SYNTHESIZE_READONLY(GameOverLayer*, mGameOverLayer, GameOverLayer);	// 3 param: Get+GameOverLayer
};



#endif // _GAME_OVER_SCENE_H_