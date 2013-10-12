#ifndef ISTATE_H
#define ISTATE_H
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Dario Schiavone
//
//------------------------------------------------------------------------

#include <typeinfo>


template <class objectType>
class IState
{
public:

	virtual ~IState(){}

	//this will execute when the state is entered
	virtual void Enter(objectType*)=0;

	//this is the states normal update function
	virtual void Execute(objectType*)=0;

	//this will execute when the state is exited. 
	virtual void Exit(objectType*)=0;
};


#endif
