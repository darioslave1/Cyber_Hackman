#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

//------------------------------------------------------------------------
//
//  Name:   StateMachine.h
//
//  Desc:   Finite State Machine class. Inherit from this class and create some 
//          states to give your agents FSM functionality
//
//  Author: Dario Schiavone
//
//------------------------------------------------------------------------


template <class objectType>
class CStateMachine
{
private:

	objectType* m_pOwner;

	//a record of the last state the entity was in
	IState<objectType>* m_pPreviousState;

	IState<objectType>*   m_pCurrentState;

	//this is called every time the FSM is updated
	IState<objectType>*   m_pGlobalState;

public:
	CStateMachine(objectType* owner): m_pOwner(owner), m_pCurrentState(NULL), m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	virtual ~CStateMachine(){}

	//use these methods to initialize the FSM
	void SetCurrentState(IState<objectType>* s)
	{
		m_pCurrentState = s;
	}
	void SetGlobalState(IState<objectType>* s) 
	{
		m_pGlobalState = s;
	}
	void SetPreviousState(IState<objectType>* s)
	{
		m_pPreviousState = s;
	}

	//call this to update the FSM
	void  Update()const
	{
		//if a global state exists, call its execute method, else do nothing
		if(m_pGlobalState)   
			m_pGlobalState->Execute(m_pOwner);

		//same for the current state
		if (m_pCurrentState) 
			m_pCurrentState->Execute(m_pOwner);
	}

	//change to a new state
	void  ChangeState(IState<objectType>* pNewState)
	{

		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;

		//call the exit method of the existing state, if the state exisist (if not exisist we are in the init state)
		m_pCurrentState->Exit(m_pOwner);

		//change state to the new state
		m_pCurrentState = pNewState;

		//call the entry method of the new state
		m_pCurrentState->Enter(m_pOwner);
	}

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const IState<objectType>& st)const
	{
		if (typeid(*m_pCurrentState) == typeid(st)) 
			return true;
		return false;
	}

	IState<objectType>*  GetCurrentState()  const
	{
		return m_pCurrentState;
	}
	IState<objectType>*  GetGlobalState()   const
	{
		return m_pGlobalState;
	}
	IState<objectType>*  GetPreviousState() const
	{
		return m_pPreviousState;
	}

};

#endif //STATEMACHINE