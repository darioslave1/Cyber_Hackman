#pragma once

#include "cocos2d.h"

#include "GameLevelMap.h"

class Player;

// A class that represents a step of the computed path
class ShortestPathStep : public cocos2d::CCNode
{
public:

	ShortestPathStep(cocos2d::CCPoint pos);
	int GetFScore();
	bool isEqualTile(ShortestPathStep* otherTile);

	const cocos2d::CCPoint GetTilePosition(){ return mTilePosition; }
	int GetGScore(){ return mGScore; }
	int GetHSCore(){ return mHScore; }
	ShortestPathStep* GetParent(){ return mParent; }

	void SetParent(ShortestPathStep* parent){ mParent = parent; }
	void SetGScore(int val){ mGScore = val; }
	void SetHScore(int val){ mHScore = val; }

	

	//tile coordinate
protected:
	cocos2d::CCPoint mTilePosition;
	int mGScore;
	int mHScore;
	ShortestPathStep* mParent;
};


//Singleton
class PathPlanner
{
public:
	static PathPlanner* GetInstance();
	~PathPlanner(void);

	void SetLevelMap(GameLevelMap *_pLevelMap);

	GameLevelMap* GetLevelMap();
	cocos2d::CCPoint GetPlayerPosition();
	cocos2d::CCPoint GetPlayerDirection();
	void SetPlayer(Player* _player);

	cocos2d::CCArray* Start_A_Star(cocos2d::CCPoint source, cocos2d::CCPoint dest);

	

private:
	PathPlanner();

	GameLevelMap *m_pLevelMap;
	Player* m_pPlayer;

	cocos2d::CCArray *mOpenSteps;
	cocos2d::CCArray *mClosedSteps;
	cocos2d::CCArray *mShortestPath;

	cocos2d::CCArray* Calculate_A_Star(cocos2d::CCPoint source, cocos2d::CCPoint dest);

	// Insert a path step (ShortestPathStep) in the ordered open steps list (spOpenSteps)
	void InsertInOpenSteps(ShortestPathStep* step);

	// Compute the H score from a position to another (from the current position to the final desired position)
	int ComputeH_Score(cocos2d::CCPoint source, cocos2d::CCPoint dest);

	//Compute the cost of moving from a step to an adjacent one
	int CostToMoveFromStep(ShortestPathStep* fromStep, ShortestPathStep* toStep);

	cocos2d::CCArray* constructPathAndStartAnimationFromStep(ShortestPathStep* step);
};

