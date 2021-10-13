#pragma once

#include <fstream>
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
	bool addToList(string state, char input, char stack,EndState e);
	void splitLineForTF(string line, string& iState, char& iInput, char& iStack, string& endstate, string& oStack);

	void displayTF();

private:
	string initialState;
	char initialStack;

	char* stackAlphabet;
	char* inputAlphabet;
	string* stateAlphabet;
	list<TransitionFunction> transitionFunctions;

	list<string> endstates;
};

//I havent tested this, but it **should** work...
void PDA::displayTF()
{
	for (list<TransitionFunction>::iterator TFit = transitionFunctions.begin(); TFit != transitionFunctions.end(); TFit++)
	{
		cout << TFit->getStartState() << "\t" << TFit->getInput() << "\t" << TFit->getStackTop() << "\t";
		list<EndState>::iterator ESit = TFit->getEndStates().begin();
		cout << ESit->getState() << "\t" << ESit->getStack() << "\t\n";
		TFit++;
		for(; ESit != TFit->getEndStates().end(); ESit++)
		{
			cout << TFit->getStartState() << "\t" << TFit->getInput() << "\t" << TFit->getStackTop() << "\t";
			cout << ESit->getState() << "\t" << ESit->getStack() << "\t\n";
		}
	}
}

//runs through the list of PDA state change functions to see if that state 
//already exists, if it exists, return true (yes it was found in list)
bool PDA::addToList(string state, char input, char stack,EndState e)
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
void PDA::splitLineForTF(string line, string &iState, char &iInput, char &iStack, string &endState, string &oStack)
{
	const char splitToken = ' ';
	const char* delim = &splitToken;
	string lineSplit[5];
	char* token = strtok(const_cast<char*>(line.c_str()), &splitToken);
	int i = 0;
	while (i < 5)
	{
		lineSplit[i] = string(token);
		token = strtok(nullptr, delim);	//this needs to check for errors**
		i++;
	}
	iState = lineSplit[0]; iInput = lineSplit[1][0]; iStack = lineSplit[2][0];
	endState = lineSplit[3]; oStack = lineSplit[4];
}

PDA::PDA(std::string definitionFilePath) {
	string fileEX = "pda.def";
	//open and parse the def file
	std::ifstream fin;
	fin.open(fileEX);
	//count number of transition functions and alphabet size
	stackAlphabetSize = 10;

	transitionAlphabetSize = 10;

	stateAlphabetSize = 10;

	head = NULL;
	
	//alphabet = new char[alphabetSize];

	//fill arrays
	string transition_line;
	string iState, eState, oStack;
	char iInput, iStack;
	while (/* getting lines from pda.def */0)
	{
		string ex_pda_line = "s0 a X s1 XY";
		splitLineForTF(ex_pda_line, iState, iInput, iStack, eState, oStack);
		EndState e(eState, oStack);
		addToList(iState, iInput, iStack, e);
	}
	//
}

PDA::~PDA() {}