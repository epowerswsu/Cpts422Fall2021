#pragma once

#include <list>
#include <string>
#include "EndState.h"
class TransitionFunction
{
public:
	TransitionFunction();
	~TransitionFunction();
	//operator== gonna need this probably
	int transition(EndState &endStates);

private:
	string startState;
	string input;
	string stackTop;	//could be a char
	list<EndState> endStates;

};

TransitionFunction::TransitionFunction()
{
	startState = "";
}

TransitionFunction::~TransitionFunction()
{
}