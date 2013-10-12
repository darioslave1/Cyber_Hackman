#include "GameLevelMap.h"

using namespace cocos2d;

GameLevelMap::GameLevelMap(void)
{
}


GameLevelMap::~GameLevelMap(void)
{
	mTileMap->release();
}

void GameLevelMap::InitLevel(int levelNum)
{
	if(levelNum <0 || levelNum > 1)
		return;

	char* levelName = (char*) malloc(100);
	sprintf(levelName, "MapLightBlue_%d.tmx",levelNum);

	mTileMap = CCTMXTiledMap::create("MapLightBlue_1.tmx");
	mTileMap->retain();
	
	free(levelName);

	this->mBackground = mTileMap->layerNamed("Background");
//		this->mForeground = mTileMap->layerNamed("Foreground");
	this->mMeta = mTileMap->layerNamed("Meta");
	mMeta->setVisible(false);

}

cocos2d::CCPoint GameLevelMap::GetInitEntityPos(char* name)
{
	CCTMXObjectGroup *spawnPointEntity = mTileMap->objectGroupNamed("SpawnEntity");
	CCAssert(spawnPointEntity != NULL, "'SpawnEntity' object group not found");

	/* random more than 1 object 
	CCArray* spawnPointsA = spawnPointsPlayer->getObjects();
	int range = spawnPointsA->count();

	cocos2d::cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	srand(now.tv_sec);
	int actualPosition = rand() % range;

	CCDictionary* spawnPoint = dynamic_cast<CCDictionary*>( spawnPointsA->objectAtIndex(actualPosition));
	*/
	CCDictionary* spawnPoint = spawnPointEntity->objectNamed(name);

	CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
	int x = (int) spawnPoint->valueForKey("x")->intValue();
	int y = (int) spawnPoint->valueForKey("y")->intValue();

	return  positionForTileCoord( tileCoordForPosition(ccp(x, y)) ) ;
}


/*************  Helper Functions ***********************/

CCPoint GameLevelMap::tileCoordForPosition(CCPoint position)
{
	int x = position.x / mTileMap->getTileSize().width;
    int y = ((mTileMap->getMapSize().height * mTileMap->getTileSize().height) - position.y) / mTileMap->getTileSize().height;
    return ccp(x, y);
}

CCPoint GameLevelMap::positionForTileCoord(CCPoint tileCoord)
{
	int x = (tileCoord.x * mTileMap->getTileSize().width) + mTileMap->getTileSize().width/2;
    int y = (mTileMap->getMapSize().height * mTileMap->getTileSize().height) - 
		(tileCoord.y * mTileMap->getTileSize().height) - mTileMap->getTileSize().height/2;
    return ccp(x, y);
}

bool GameLevelMap::IsWallAtTileCoords(CCPoint pos)
{
	int tileGid = mMeta->tileGIDAt(pos);
	if (tileGid)
	{
		CCDictionary *properties = mTileMap->propertiesForGID(tileGid);
		if (properties)
		{
			const CCString *collision = properties->valueForKey("Collidable");
			if (collision && (collision->compare("true") == 0))
			{
				return true;
			}
		}
	}

	return false;
}


bool GameLevelMap::isValidTileCoord(CCPoint tileCoord) 
{
	if (tileCoord.x < 0 || tileCoord.y < 0 || 
		tileCoord.x >= mTileMap->getMapSize().width ||
		tileCoord.y >= mTileMap->getMapSize().height) 
	{
		return false;
	} else {
		return true;
	}
}

bool GameLevelMap::isValidAndNotWallTile(cocos2d::CCPoint tile)
{
	if(!isValidTileCoord(tile) || IsWallAtTileCoords(tile))
		return false;		//not valid
	
	if(isValidTileCoord(tile) && !IsWallAtTileCoords(tile))
		return true;	//valid

	return false;
}



std::vector<CCPoint> GameLevelMap::GetWalkableAdjacentTiles(CCPoint tileCoord)
{
	std::vector<CCPoint> tmpArray;


	//top
	CCPoint point =	CCPointMake( tileCoord.x, tileCoord.y -1);
	if(this->isValidTileCoord(point) && !this->IsWallAtTileCoords(point))
	{
		tmpArray.push_back(point);
	}


	//left
	point =	CCPointMake( tileCoord.x -1, tileCoord.y );
	if(this->isValidTileCoord(point) && !this->IsWallAtTileCoords(point))
	{
		tmpArray.push_back(point);
	}

	//bottom
	point =	CCPointMake( tileCoord.x , tileCoord.y+1 );
	if(this->isValidTileCoord(point) && !this->IsWallAtTileCoords(point))
	{
		tmpArray.push_back(point);
	}

	//right
	point =	CCPointMake( tileCoord.x +1, tileCoord.y );
	if(this->isValidTileCoord(point) && !this->IsWallAtTileCoords(point))
	{
		tmpArray.push_back(point);
	}


	return tmpArray;
}