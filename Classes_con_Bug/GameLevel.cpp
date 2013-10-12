#include "GameLevel.h"

#include "EntityManager.h"
#include "RedEnemy.h"
#include "BluEnemy.h"

#include "AIEffect.h"

#include "GameOverScene.h"

using namespace cocos2d;

GameLevel::GameLevel(void): mStopGame(false), mExitLevel(false)
{
}


GameLevel::~GameLevel(void)
{
	EntityManager::GetInstance()->RemoveAllEntity();
}


CCScene* GameLevel::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLevel *layer = GameLevel::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void GameLevel::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

bool GameLevel::init()
{
    bool bRet = false;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Cyberbite_SMclubCommercial.ogg",true);
	
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(94, 63, 107, 255) ));

		this->setTouchEnabled(true);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		// Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameLevel::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

/*		AIEffect* aiEffect = new AIEffect();
		aiEffect->GetEntitySprite()->setPosition( ccp(visibleSize.width/2 , visibleSize.height/2 ));
		this->addChild( aiEffect->GetEntitySprite(),1 );
		EntityManager::GetInstance()->RegisterEntity(aiEffect);
*/
		//////////// TileMap, deleted in entitymanager
  //      mLevelMap = new GameLevelMap(aiEffect);
		mLevelMap = new GameLevelMap();
		mLevelMap->InitLevel(1);

		this->addChild( mLevelMap->getTileMap());

		EntityManager::GetInstance()->RegisterLeveMap(mLevelMap);

		//Path Planner
		PathPlanner::GetInstance()->SetLevelMap(mLevelMap);

		//Create Player
		Player* mPlayer = new Player();
		mPlayer->retain();
		mPlayer->SetSpritePosition( mLevelMap->GetInitEntityPos("Player") );
		this->addChild( mPlayer->GetEntitySprite() );
		mPlayer->Init();
		EntityManager::GetInstance()->RegisterEntity(mPlayer);
		PathPlanner::GetInstance()->SetPlayer(mPlayer);
		

		/*** Create Enemies ***/

		//RedEnemy
		RedEnemy* red = new RedEnemy();
		red->retain();
		red->SetSpritePosition(mLevelMap->GetInitEntityPos("Red") );
		this->addChild(red->GetEntitySprite());
		red->Init();
		EntityManager::GetInstance()->RegisterEntity(red);
		
		//BluEnemy
		BluEnemy* blu = new BluEnemy();
		blu->retain();
		blu->SetSpritePosition(mLevelMap->GetInitEntityPos("Blu") );
		this->addChild(blu->GetEntitySprite());
		blu->Init();
		EntityManager::GetInstance()->RegisterEntity(blu);

		//now call the update every frame
		this->schedule( schedule_selector(GameLevel::Update));

		EntityManager::GetInstance()->SetGameOver(false);

		//CCSprite* nuke = CCSprite::create("nuke_low.png");
		//nuke->setPosition( mLevelMap->AddNewNuke() );
		//this->addChild( nuke);

		//CCActionInterval* blinkNuke = CCBlink::create(1.f, 1);
		//CCRepeatForever* rep2 = CCRepeatForever::create(blinkNuke);
		//nuke->runAction( rep2);

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GITS_Enter.ogg");
		
		
        bRet = true;
    } while (0);

    return bRet;
}


void GameLevel::Update(float dt)
{

	if(mStopGame)
	{
		if(mExitLevel == false)
		{

			// create a scene. it's an autorelease object
			GameOverScene *gameOverScene = GameOverScene::create();

			CCNode* node = CCNode::create();
			CCActionInterval* effect = CCShaky3D::create(5, false, ccg(15,10), 0.8f);
			node->runAction(effect);
			addChild(node, 0);

			mExitLevel = true;
			CCDirector::sharedDirector()->replaceScene(CCTransitionProgressInOut::create(0.8f, gameOverScene) );
			
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GITS_explosion.ogg");
		}

		//	CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}
	else
	{
		if(mLevelMap->GetChunkNum() <= 0)
		{
			mLevelMap->GetAIEffect()->Disable();
			mLevelMap->EnableChipAITile();
		}

		mStopGame = EntityManager::GetInstance()->Update(dt);
	}


}
