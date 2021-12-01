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
	
	bool newEndState(EndState e);
	void addEndState(EndState e) { endStates.push_back(e); }

	string getStartState() { return startState; }
	char getStackTop() { return stackTop; }
	char getInput() { return input; }

	list<EndState> getEndStates() { return endStates; }
	
	void displayEndStates();
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

void TransitionFunction::displayEndStates() 
{
	list<EndState>::iterator it = endStates.begin();
	cout << "\t" << it->getState() << "\t" << it->getStack() << endl;
	it++;
	for (; it != endStates.end(); it++)
	{
		cout << "\t\t\t\t" << it->getState() << "\t" << it->getStack() << endl;
	}
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
