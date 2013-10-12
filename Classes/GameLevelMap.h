#pragma once

#include "cocos2d.h"
#include <vector>

class AIEffect;

#define NUM_AI_BARRIER 21

enum TileContain
{
	NOTHING,
	WALL,
	CHUNK,
	NUKE
};

class GameLevelMap
{
public:
	GameLevelMap(AIEffect* aiEffect);
	GameLevelMap(void);
	~GameLevelMap(void);

	void InitLevel(int levelNum);


	CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, mTileMap, TileMap);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mBackground, Background);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mPwdChunksForeground, PwdChunksForeground);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mMeta, Meta);

	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint tileCoord);
	bool IsWallAtTileCoords(cocos2d::CCPoint tile);
	//@get the tileCoord adjacent walkable tiles, for A*
	std::vector<cocos2d::CCPoint> GetWalkableAdjacentTiles(cocos2d::CCPoint tileCoord);

	bool isValidTileCoord(cocos2d::CCPoint);

	bool isValidAndNotWallTile(cocos2d::CCPoint tile);

	int GetItemInTile(cocos2d::CCPoint tile);

	bool IsInChipTiles(cocos2d::CCPoint tile);

	cocos2d::CCPoint GetInitEntityPos(char* name);
	cocos2d::CCPoint AddNewNuke();

	int GetChunkNum() { return mChunkNum; } 
	void DecreaseChunkNum() { mChunkNum--;}

	bool IsPlayerWinner(){ return mPlayerWinner; }
	void SetPlayerWinner(bool val){ mPlayerWinner = val; }

	AIEffect* GetAIEffect(){return pAIEffect;}
	void EnableChipAITile();

private:

	AIEffect* pAIEffect;
	int mChunkNum;

	cocos2d::CCPoint mIAWallChipTiles[NUM_AI_BARRIER];
	cocos2d::CCPoint mIAChipTiles[9];

	bool mPlayerWinner;

};

