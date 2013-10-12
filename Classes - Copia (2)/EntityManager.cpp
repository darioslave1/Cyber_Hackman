#include "EntityManager.h"

#include "Entity.h"
#include "GameLevelMap.h"

//this is a singleton
EntityManager* EntityManager::GetInstance()
{
	static EntityManager instance;
	return &instance;
}

EntityManager::EntityManager(void)
{
}


EntityManager::~EntityManager(void)
{
//	mEntityList.clear();

	std::vector<Entity*>::iterator iter;

	for(iter = mEntityList.begin(); iter != mEntityList.end(); iter++)
		delete (*iter);

	delete m_pLevelMap;
}


void EntityManager::RegisterEntity(Entity* ent)
{
	mEntityList.push_back(ent);
}

void EntityManager::RemoveEntity(Entity* ent)
{
	std::vector<Entity*>::iterator iter;

	for(iter = mEntityList.begin(); iter != mEntityList.end(); )
	{
		if( (*iter)->Id == ent->Id )
			iter = mEntityList.erase(iter);
		else
			iter++;
	}
}

void EntityManager::RegisterLeveMap(GameLevelMap* _pLevelMap)
{
	m_pLevelMap = _pLevelMap;
}

GameLevelMap* EntityManager::GetLevelMap()
{
	return m_pLevelMap;
}

void EntityManager::Update( float dt )
{
	std::vector<Entity*>::iterator iter;

	for(iter = mEntityList.begin(); iter != mEntityList.end(); iter++)
	{
		(*iter)->Update(dt);
	}
}
