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
	mIsGameOver = false;
}


EntityManager::~EntityManager(void)
{
	
}


void EntityManager::RegisterEntity(Entity* ent)
{
	mEntityList.push_back(ent);
}

void EntityManager::RemoveAllEntity()
{
	std::vector<Entity*>::iterator iter;

	for(iter = mEntityList.begin(); iter != mEntityList.end(); iter++)
		delete (*iter);

	mEntityList.clear();
	std::vector<Entity*>().swap(mEntityList);

	delete m_pLevelMap;
}


void EntityManager::RemoveEntity(Entity* ent)
{
	if(mEntityList.size() > 0 )
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
}

void EntityManager::RegisterLeveMap(GameLevelMap* _pLevelMap)
{
	m_pLevelMap = _pLevelMap;
}

GameLevelMap* EntityManager::GetLevelMap()
{
	return m_pLevelMap;
}

bool EntityManager::Update( float dt )
{
	std::vector<Entity*>::iterator iter;
	for(iter = mEntityList.begin(); iter != mEntityList.end(); iter++)
	{
		bool exitGame = (*iter)->Update(dt);
		if(exitGame)
			return true;
	}

	return false;
}
