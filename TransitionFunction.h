#pragma once

#include <list>
#include <string>
#include "EndState.h"
class TransitionFunction
{
public:
	TransitionFunction();
	TransitionFunction(string ss, char in, char st, EndState e) { startState = ss; stackTop = st; input = in; endStates.push_back(e); }
	~TransitionFunction();
	//operator== gonna need this probably
	
	int transition(EndState& endStates) {}
	
	bool newEndState(EndState e);
	void addEndState(EndState e) { endStates.push_back(e); }

	string getStartState() { return startState; }
	char getStackTop() { return stackTop; }
	char getInput() { return input; }

	list<EndState> getEndStates() { return endStates; }

private:
	string startState;
	char stackTop;
	char input;
	
	list<EndState> endStates;
};

TransitionFunction::TransitionFunction()
{
	//set the three identifiers and begin a list of end states
	startState = "";
}

TransitionFunction::~TransitionFunction()
{
}

bool TransitionFunction::newEndState(EndState e)
{
	for (list<EndState>::iterator it = endStates.begin(); it != endStates.end(); it++)
	{
		if (*it == e)
			return false;//duplicate, ignore
	}
	return true;
}
