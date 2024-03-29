#include "GameLevelMap.h"

#include "AIEffect.h"

using namespace cocos2d;

/*
GameLevelMap::GameLevelMap(AIEffect* aiEffect): mChunkNum(8), pAIEffect(aiEffect)
{
	//fill the AI Chip array tiles to remove when the AI is disabled
	mIAChipTiles[0] = ccp(15,6);
	mIAChipTiles[1] = ccp(15,7);
	mIAChipTiles[2] = ccp(15,8);
	
	mIAChipTiles[3] = ccp(9,6);
	mIAChipTiles[4] = ccp(9,7);
	mIAChipTiles[5] = ccp(9,8);
	mIAChipTiles[6] = ccp(9,9);
	mIAChipTiles[7] = ccp(10,5);
	mIAChipTiles[8] = ccp(11,5);
	mIAChipTiles[9] = ccp(12,5);
	mIAChipTiles[10] = ccp(13,5);
	mIAChipTiles[11] = ccp(14,5);
	mIAChipTiles[12] = ccp(15,5);

	mIAChipTiles[13] = ccp(10,9);
	mIAChipTiles[14] = ccp(11,9);
	mIAChipTiles[15] = ccp(12,9);
	mIAChipTiles[16] = ccp(13,9);
	mIAChipTiles[17] = ccp(14,9);
	mIAChipTiles[18] = ccp(15,9);

	mIAChipTiles[19] = ccp(9,5);
	
}
*/

GameLevelMap::GameLevelMap(): mChunkNum(8)
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

	mTileMap = CCTMXTiledMap::create("MapLightBlue_2.tmx");
	mTileMap->retain();
	
	free(levelName);

	this->mBackground = mTileMap->layerNamed("Background");
	
	this->mMeta = mTileMap->layerNamed("Meta");

//	this->mPwdChunksForeground = mTileMap->layerNamed("PwdChunks_Foreground");

	mMeta->setVisible(false);

	cocos2d::cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	srand(now.tv_sec);

	 //Backdoor Animation
/*	CCSprite *tile0 = mPwdChunksForeground->tileAt(ccp(5,5));
	CCActionInterval* opacityIn = CCFadeIn::create(2.f);
	CCRepeatForever* rep2 = CCRepeatForever::create( opacityIn);
	tile0->runAction( rep2);
	*/

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

cocos2d::CCPoint GameLevelMap::AddNewNuke()
{
	CCTMXObjectGroup *spawnNukePoint = mTileMap->objectGroupNamed("Nuke_Positions");
	CCAssert(spawnNukePoint != NULL, "'Nuke_Positions' object group not found");

	CCArray* spawnPointsA = spawnNukePoint->getObjects();
	int range = spawnPointsA->count();

	int actualPosition = rand() % range;

	CCDictionary* spawnPoint = dynamic_cast<CCDictionary*>( spawnPointsA->objectAtIndex(actualPosition));

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

bool GameLevelMap::IsWallAtTileCoords(CCPoint tile)
{
	int tileGid = mMeta->tileGIDAt(tile);
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

int GameLevelMap::GetItemInTile(CCPoint tile)
{
	int tileGid = mMeta->tileGIDAt(tile);

	if (tileGid)
	{
		CCDictionary *properties = mTileMap->propertiesForGID(tileGid);
		if (properties)
		{
			const CCString *collision = properties->valueForKey("Collectable");
			if (collision && (collision->compare("True") == 0))
			{
				const CCString *type = properties->valueForKey("Type");
				if (type && (type->compare("Chunk") == 0))
				{
					mMeta->removeTileAt(tile);
					mPwdChunksForeground->removeTileAt(tile);
					return CHUNK;
				}
			}
		}
	}

	return NOTHING;
}

void GameLevelMap::EnableChipAITile()
{
	for(int i=0; i<20; i++)
	{
		mMeta->removeTileAt(mIAChipTiles[i]);
	}

}