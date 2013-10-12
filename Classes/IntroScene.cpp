#include "IntroScene.h"

#include "GameLevel.h"


using namespace cocos2d;

IntroScene::IntroScene(void)
{
}


IntroScene::~IntroScene(void)
{
}



CCScene* IntroScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        IntroScene *layer = IntroScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool IntroScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(94, 63, 107, 255) ));


        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(IntroScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("IntroScene.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

		//Add the menu choice
		CCMenuItemFont::setFontSize( 100 );
		CCMenuItemFont::setFontName("Courier New");
		CCLabelBMFont* labelNew = CCLabelBMFont::create("New Game!", "bitmapFontTest3.fnt");
		CCMenuItemLabel* itemNew = CCMenuItemLabel::create(labelNew, this, menu_selector(IntroScene::menuNewCallback));

		CCLabelBMFont* labelQuit = CCLabelBMFont::create("Quit", "bitmapFontTest3.fnt");
		CCMenuItemLabel* itemQuit = CCMenuItemLabel::create(labelQuit, this, menu_selector(IntroScene::menuCloseCallback));

		CCMenu* menu = CCMenu::create( itemNew, itemQuit, NULL);
	//	menu->alignItemsVertically();
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

        bRet = true;
    } while (0);

    return bRet;
}

void IntroScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void IntroScene::menuNewCallback(CCObject* pSender)
{
	// "close" menu item clicked
//	GameLevel *gameLevel = new GameLevel();
//	gameLevel->autorelease();

	CCScene *pScene = GameLevel::scene();
	
//	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressOutIn::create(1, gameLevel->scene()) );
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressOutIn::create(1, pScene) );

}