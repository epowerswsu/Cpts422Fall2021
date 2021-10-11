#pragma once

#include <list>

#include "TransitionFunction.h"
#include "Node.h"

/*
*	PDA 
*/
class PDA {
public:
	PDA(std::string definitionFilePath);
	~PDA();

	char* stackAlphabet;
	char* inputAlphabet;
	string* stateAlphabet;

	int stackAlphabetSize, transitionAlphabetSize, stateAlphabetSize;
	Node* head;
	

private:
	string initialState;
	char initialStack;

	char* stackAlphabet;
	char* inputAlphabet;
	string* stateAlphabet;
	list<TransitionFunction> transitionFunctions;

	list<string> endstates;
};

PDA::PDA(std::string definitionFilePath) {
	//open and parse the def file

	//count number of transition functions and alphabet size
	stackAlphabetSize = 10;
	transitionAlphabetSize = 10;
	stateAlphabetSize = 10;
	head = NULL;

	transitionFunctions = new TransitionFunction[transitionFunctionsSize];
	alphabet = new char[alphabetSize];

	//fill arrays

}

PDA::~PDA() {}