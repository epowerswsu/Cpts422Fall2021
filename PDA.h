#pragma once

//#include <list>

#include "TransitionFunction.h"
#include "Node.h"

/*
*	PDA 
*/
class PDA {
public:
	PDA(std::string definitionFilePath);
	~PDA();

	int stackAlphabetSize, transitionAlphabetSize, stateAlphabetSize;
	Node* head;
	bool findInList(string state, char input, char stack);
	void splitLineForTF(string line, string& iState, char& iInput, char& iStack, string& endstate, string& oStack);

private:
	string initialState;
	char initialStack;

	char* stackAlphabet;
	char* inputAlphabet;
	string* stateAlphabet;
	list<TransitionFunction> transitionFunctions;

	list<string> endstates;
};

//runs through the list of PDA state change functions to see if that state 
//already exists, if it exists, return true (yes it was found in list)
bool PDA::findInList(string state, char input, char stack)
{
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it!=transitionFunctions.end(); it++)
	{ 
		if (it->getStartState() == state && it->getInput() == stack && it->getStackTop() == stack)
		{
			return true;
		}
	}
	return false;
}

//splits the line for transition functions
void PDA::splitLineForTF(string line, string &iState, char &iInput, char &iStack, string &endstate, string &oStack)
{

}

PDA::PDA(std::string definitionFilePath) {
	//open and parse the def file

	//count number of transition functions and alphabet size
	stackAlphabetSize = 10;

	transitionAlphabetSize = 10;

	stateAlphabetSize = 10;

	head = NULL;
	
	//alphabet = new char[alphabetSize];

	//fill arrays
	string ex_pda_line = "s0 a X ";
	void splitLine(ex_pda_line);

	if (findInList())
	{

	}
	//
}

PDA::~PDA() {}