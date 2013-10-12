
#include "GameOverScene.h"
#include "GameLevel.h"
#include "EntityManager.h"

using namespace cocos2d;

GameOverScene::GameOverScene() : mGameOverLayer(NULL) 
{

}

bool GameOverScene::init()
{
	if( CCScene::init())
	{
		this->mGameOverLayer = GameOverLayer::create();
		this->mGameOverLayer->retain();
		this->addChild(mGameOverLayer);

		return true;
	}else
		return false;
}

GameOverScene::~GameOverScene()
{
	if(mGameOverLayer)
	{
		mGameOverLayer->release();
		mGameOverLayer = NULL;
	}
}

GameOverLayer::GameOverLayer()
{

}

bool GameOverLayer::init()
{
	if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
	{
		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create("IntroScene.png");
		if(!pSprite)
			return false;

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);

		//Add the menu choice
		CCMenuItemFont::setFontSize( 100 );
		CCMenuItemFont::setFontName("Courier New");
		CCLabelBMFont* labelNew = CCLabelBMFont::create("Restart Game!", "bitmapFontTest3.fnt");
		CCMenuItemLabel* itemNew = CCMenuItemLabel::create(labelNew, this, menu_selector(GameOverLayer::menuRestartCallback));

		CCLabelBMFont* labelQuit = CCLabelBMFont::create("Quit", "bitmapFontTest3.fnt");
		CCMenuItemLabel* itemQuit = CCMenuItemLabel::create(labelQuit, this, menu_selector(GameOverLayer::menuCloseCallback));

		CCMenu* menu = CCMenu::create( itemNew, itemQuit, NULL);
		menu->alignItemsVerticallyWithPadding(50);

		int i=0;
		CCNode* child;
		CCArray * pArray = menu->getChildren();
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(pArray, pObject)
		{
			if(pObject == NULL)
				break;

			child = (CCNode*)pObject;

			CCPoint dstPoint = child->getPosition();
			int offset = (int) (size.width/2 + 50);
			if( i % 2 == 0)
				offset = -offset;

			child->setPosition( ccp( dstPoint.x + offset, dstPoint.y) );
			child->runAction( 
				CCEaseElasticOut::create(CCMoveBy::create(2, ccp(dstPoint.x - offset,0)), 0.35f) 
				);
			i++;
		}

		addChild(menu);
		menu->setPosition(ccp(size.width/2, size.height/2));

		EntityManager::GetInstance()->SetGameOver(false);

		return true;
	}
	else
		return false;
}

void GameOverLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void GameOverLayer::menuRestartCallback(CCObject* pSender)
{

	CCDirector::sharedDirector()->replaceScene( CCTransitionProgressOutIn::create(1, GameLevel::scene()) );
}


GameOverLayer::~GameOverLayer()
{
}
