
#include "WinnerScene.h"
#include "GameLevel.h"
#include "EntityManager.h"

using namespace cocos2d;

WinnerScene::WinnerScene() : mWinnerLayer(NULL) 
{

}

bool WinnerScene::init()
{
	if( CCScene::init())
	{
		this->mWinnerLayer = WinnerLayer::create();
		this->mWinnerLayer->retain();
		this->addChild(mWinnerLayer);

		return true;
	}else
		return false;
}

WinnerScene::~WinnerScene()
{
	if(mWinnerLayer)
	{
		mWinnerLayer->release();
		mWinnerLayer = NULL;
	}
}

WinnerLayer::WinnerLayer()
{

}

bool WinnerLayer::init()
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
		CCMenuItemLabel* itemNew = CCMenuItemLabel::create(labelNew, this, menu_selector(WinnerLayer::menuRestartCallback));

		CCLabelBMFont* labelQuit = CCLabelBMFont::create("Quit", "bitmapFontTest3.fnt");
		CCMenuItemLabel* itemQuit = CCMenuItemLabel::create(labelQuit, this, menu_selector(WinnerLayer::menuCloseCallback));

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

void WinnerLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void WinnerLayer::menuRestartCallback(CCObject* pSender)
{

	CCDirector::sharedDirector()->replaceScene( CCTransitionProgressOutIn::create(1, GameLevel::scene()) );
}


WinnerLayer::~WinnerLayer()
{
}
