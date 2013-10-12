#include "PathPlanner.h"

#include "GameLevelMap.h"
#include "Player.h"

#include "EntityManager.h"

using namespace cocos2d;

PathPlanner* PathPlanner::GetInstance()
{
	static PathPlanner instance;
	return &instance;
}

PathPlanner::PathPlanner() : mOpenSteps(NULL), mClosedSteps(NULL), mShortestPath(NULL)
{
}


PathPlanner::~PathPlanner(void)
{

	if(mClosedSteps)
		mClosedSteps->release();
	mClosedSteps = NULL;

	if(mOpenSteps)
		mOpenSteps->release();
	mOpenSteps = NULL;

	if(mShortestPath)
		mShortestPath->release();
	mShortestPath = NULL;
}

void PathPlanner::SetLevelMap(GameLevelMap *_pLevelMap)
{
	m_pLevelMap = _pLevelMap;
}

GameLevelMap* PathPlanner::GetLevelMap()
{
	return m_pLevelMap;
}

CCPoint PathPlanner::GetPlayerDirection()
{
	return m_pPlayer->GetDirection();
}
CCPoint PathPlanner::GetPlayerPosition()
{
	return m_pPlayer->GetSpritePosition();
}
void PathPlanner::SetPlayer(Player* _player)
{
	m_pPlayer = _player;
}

std::vector<ShortestPathStep*> PathPlanner::Start_A_Star(CCPoint source, CCPoint dest)
{
	//init shortest path properties
	this->mOpenSteps = CCArray::create();
	this->mOpenSteps->retain();
	this->mClosedSteps = CCArray::create();
	this->mClosedSteps->retain();

	if(mShortestPath)
		mShortestPath->release();

	return Calculate_A_Star( source, dest );
}

std::vector<ShortestPathStep*> PathPlanner::Calculate_A_Star(CCPoint source, CCPoint dest)
{

//	bool isPathFound = false;
	bool forceStop = false;

	// 1. Insert the intial position in openList
	ShortestPathStep* tmp = new ShortestPathStep(source);
	tmp->autorelease();
	this->InsertInOpenSteps(tmp);

	do
	{
		// 1. get the Lowest F cost in the open list
		//because the list is ordered, the lowest is the first
		ShortestPathStep* currentStep = dynamic_cast<ShortestPathStep*>(mOpenSteps->objectAtIndex(0));

		//2. Add the current in the closed list
		mClosedSteps->addObject(currentStep);

		//3. remove from the open list
		mOpenSteps->removeObjectAtIndex(0);

		//check if is the current = destination, we have DONE!
		if(currentStep->GetTilePosition().equals(dest) )
		{
		
			// create the path and start the move action and animation
			mOpenSteps->release();
			this->mOpenSteps = NULL;
			mClosedSteps->release();
			this->mClosedSteps = NULL;
			

			return this->constructPathAndStartAnimationFromStep(currentStep);
		}

		//4. Get adj tile coord of the current step
		std::vector<CCPoint> tmpAdjArray = m_pLevelMap->GetWalkableAdjacentTiles(currentStep->GetTilePosition());
		std::vector<CCPoint>::iterator iter;

		for(iter = tmpAdjArray.begin(); iter < tmpAdjArray.end(); iter++)
		{
			CCPoint p = *iter;
			ShortestPathStep* step = new ShortestPathStep(p);

			// 4.1 // Check if the step isn't already in the closed set 
			CCObject* iterSteps;
			CCARRAY_FOREACH(mClosedSteps, iterSteps)
			{
				ShortestPathStep *tmpStep = dynamic_cast<ShortestPathStep*>(iterSteps);
				if(step->isEqualTile(tmpStep))
				{
					step->release();
					forceStop = true;
					break;
				}
			}
			if(forceStop)
			{
				forceStop = false;
				continue;

			}

			//4.2 //Compute the cost from the current to the step
			int moveCost = CostToMoveFromStep(currentStep, step);

			//4.3 //check if the step is already in the open list
			//int indexStep = mOpenSteps->indexOfObject(step);
			int indexStep = -1;
			bool isPresent = false;
			iterSteps = NULL;
			CCARRAY_FOREACH(mOpenSteps, iterSteps)
			{
				indexStep++;
				ShortestPathStep *tmpStep = dynamic_cast<ShortestPathStep*>(iterSteps);
				if(step->isEqualTile(tmpStep))
				{
					isPresent = true;
					break;
				}
			}

			if(!isPresent)
			{
				//4.4 // Add it, set parent
				step->SetParent(currentStep);

				//4.5 // set the G score
				step->SetGScore(currentStep->GetGScore() + moveCost);

				//4.6 // compute the H score, with manhattan
				step->SetHScore(this->ComputeH_Score(step->GetTilePosition(), dest));

				//4.7 //now add in Open list, in correct position
				this->InsertInOpenSteps(step);

				//done, release the step
				step->release();
			}
			else	//already in the open list, recalculate the Fscore
			{
				step->release();
				step = NULL;

				//get the old step
				step = dynamic_cast<ShortestPathStep*>(mOpenSteps->objectAtIndex(indexStep));

				//5. Check if the old G score is lower than that step
				if( (currentStep->GetGScore() + moveCost) < step->GetGScore())
				{
					//so we change the G score
					step->SetGScore(currentStep->GetGScore() + moveCost);

					// Because the G Score has changed, the F score may have changed too
					// So to keep the open list ordered we have to remove the step, and re-insert it with
					// the insert function which is preserving the list ordered by F score

					// We have to retain it before removing it from the list
					step->retain();

					// Now we can removing it from the list without be afraid that it can be released
					mOpenSteps->removeObjectAtIndex(indexStep);

					// Re-insert it with the function which is preserving the list ordered by F score
					this->InsertInOpenSteps(step);

					step->release();
				}

			}
				
		}

	}while(mOpenSteps->count() > 0 );


std::vector<ShortestPathStep*> tmpShortest;

return tmpShortest;

}


std::vector<ShortestPathStep*> PathPlanner::constructPathAndStartAnimationFromStep(ShortestPathStep* step)
{
//	mShortestPath = CCArray::create();
//	mShortestPath->retain();

	std::vector<ShortestPathStep*> tmpShortest;


	do
	{
		//don't add the last step that is the start position, because now the path is backward
		if(step->GetParent() != NULL)
		{
			tmpShortest.insert( tmpShortest.begin() ,step);

//			mShortestPath->insertObject(step ,0);
		}
		step = step->GetParent();
	}while(step!=NULL);
	
//	return mShortestPath;
	return tmpShortest;

}




void PathPlanner::InsertInOpenSteps(ShortestPathStep* step)
{
	int stepFscore = step->GetFScore();
	int count = this->mOpenSteps->count();
	int index = 0;	//we inserti the step in this position

	for(index = 0; index < count; index++)
	{
		ShortestPathStep *tmp = dynamic_cast<ShortestPathStep*> (this->mOpenSteps->objectAtIndex(index) );
		if(stepFscore < tmp->GetFScore())
			break;	//this is the index
	}

	//insert the new step in the ordered list
	this->mOpenSteps->insertObject(step,index );
}

int PathPlanner::ComputeH_Score(cocos2d::CCPoint source, cocos2d::CCPoint dest)
{
	// Here we use the Manhattan method, which calculates the total number of step moved horizontally and vertically to reach the
	// final desired step from the current step, ignoring any obstacles that may be in the way
	return abs(source.x - dest.x) + abs(source.y - dest.y);
}

int PathPlanner::CostToMoveFromStep(ShortestPathStep* fromStep, ShortestPathStep* toStep)
{
	// Because we can't move diagonally and because terrain is just walkable or unwalkable the cost is always the same.
	// But it have to be different if we can move diagonally and/or if there is swamps, hills, etc...

	//if there is another entity in the toStep, the cost is higher
	std::vector<Entity*>::iterator iter;
	
	for(iter = EntityManager::GetInstance()->GetEntityList()->begin();
		iter != EntityManager::GetInstance()->GetEntityList()->end(); iter++)
	{
		if((*iter)->Id != 1)
			if( m_pLevelMap->tileCoordForPosition( (*iter)->GetSpritePosition() ).equals(toStep->GetTilePosition()))
				return 8;
	}
	

	return 1;
}






/******* ShortestPathStep **********/
ShortestPathStep::ShortestPathStep(cocos2d::CCPoint pos)
{
	this->mTilePosition = pos;
	this->mGScore = 0;
	this->mHScore = 0;
	this->mParent = NULL;
}

bool ShortestPathStep::isEqualTile(ShortestPathStep* otherTile)
{
	return this->mTilePosition.equals(otherTile->mTilePosition);
}


int ShortestPathStep::GetFScore()
{
	return (this->mGScore + this->mHScore);
}