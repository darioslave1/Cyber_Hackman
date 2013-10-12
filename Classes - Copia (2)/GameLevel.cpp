#include "GameLevel.h"

#include "EntityManager.h"
#include "RedEnemy.h"
#include "BluEnemy.h"

using namespace cocos2d;

GameLevel::GameLevel(void)
{
}


GameLevel::~GameLevel(void)
{
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
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(94, 63, 107, 255) ));

		this->setTouchEnabled(true);

		//////////// TileMap, deleted in entitymanager
        GameLevelMap* mLevelMap = new GameLevelMap();
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
/*		RedEnemy* red = new RedEnemy();
		red->retain();
		red->SetSpritePosition(mLevelMap->GetInitEntityPos("Red") );
		this->addChild(red->GetEntitySprite());
		red->Init();
		EntityManager::GetInstance()->RegisterEntity(red);
*/		

		//BluEnemy
		BluEnemy* blu = new BluEnemy();
		blu->retain();
		blu->SetSpritePosition(mLevelMap->GetInitEntityPos("Blu") );
		this->addChild(blu->GetEntitySprite());
		blu->Init();
		EntityManager::GetInstance()->RegisterEntity(blu);


		//now call the update every frame
		this->schedule( schedule_selector(GameLevel::Update));

        bRet = true;
    } while (0);

    return bRet;
}


void GameLevel::Update(float dt)
{
	EntityManager::GetInstance()->Update(dt);
}