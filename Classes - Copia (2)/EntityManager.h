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

	void RegisterLeveMap(GameLevelMap* _pLevelMap);

	GameLevelMap* GetLevelMap();

	void Update( float dt );

	std::vector<Entity*>* GetEntityList(){return &mEntityList;}

private:
	EntityManager(void);

	std::vector<Entity*> mEntityList;

	GameLevelMap* m_pLevelMap;

};

