#pragma once

#include <vector>

#include "Player.h"
#include "GameLevelMap.h"

class EntityManager
{
public:

	static EntityManager* GetInstance();

	~EntityManager(void);

	void RegisterEntity(Entity* ent);
	void RemoveEntity(Entity* ent);

	void RemoveAllEntity();

	void RegisterLeveMap(GameLevelMap* _pLevelMap);

	GameLevelMap* GetLevelMap();

	bool Update( float dt );

	std::vector<Entity*>* GetEntityList(){return &mEntityList;}

	bool IsGameOver(){ return mIsGameOver; }
	void SetGameOver(bool isGameOver){ mIsGameOver = isGameOver; }

private:
	EntityManager(void);

	std::vector<Entity*> mEntityList;

	GameLevelMap* m_pLevelMap;

	bool mIsGameOver;

};

