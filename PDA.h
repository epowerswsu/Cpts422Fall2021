#pragma once
#include "TransitionFunction.h"
#include "Node.h"

class PDA {
public:
	TransitionFunction* transitionFunctions;
	char* alphabet;
	int transitionFunctionsSize, alphabetSize;
	Node* head;

	PDA(std::string definitionFilePath);
	~PDA();
	void start(std::string word);
	void step();
};

PDA::PDA(std::string definitionFilePath) {
	//open and parse the def file

	//count number of transition functions and alphabet size
	transitionFunctionsSize = 10;
	alphabetSize = 10;
	head = NULL;

	transitionFunctions = new TransitionFunction[transitionFunctionsSize];
	alphabet = new char[alphabetSize];

	//fill arrays

}

PDA::~PDA() {}