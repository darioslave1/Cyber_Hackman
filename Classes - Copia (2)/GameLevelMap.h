#pragma once

#include "cocos2d.h"
#include <vector>

class GameLevelMap
{
public:
	GameLevelMap(void);
	~GameLevelMap(void);

	void InitLevel(int levelNum);


	CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, mTileMap, TileMap);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mBackground, Background);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mForeground, Foreground_);
	CC_SYNTHESIZE(cocos2d::CCTMXLayer*, mMeta, Meta);

	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint tileCoord);
	bool IsWallAtTileCoords(cocos2d::CCPoint pos);
	//@get the tileCoord adjacent walkable tiles, for A*
	std::vector<cocos2d::CCPoint> GetWalkableAdjacentTiles(cocos2d::CCPoint tileCoord);

	bool isValidTileCoord(cocos2d::CCPoint);

	bool isValidAndNotWallTile(cocos2d::CCPoint tile);

	cocos2d::CCPoint GetInitEntityPos(char* name);

private:

	
};

