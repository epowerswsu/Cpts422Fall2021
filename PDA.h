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
	PDA() {}
	PDA(string definitionFilePath);
	~PDA();

	int stackAlphabetSize, inputAlphabetSize, stateAlphabetSize;
	Node* head;
	bool addToTFList(string state, char input, char stack, EndState e);
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
bool PDA::addToTFList(string state, char input, char stack, EndState e)
{
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it!=transitionFunctions.end(); it++)
	{ 
		if (it->getStartState() == state && it->getInput() == stack && it->getStackTop() == stack)
		{
			//check for copy in the list of matching transition functions
			return true;
		}
		else
		{
			TransitionFunction tf(state, input, stack, e);
			transitionFunctions.push_back(tf);
		}
	}
	return false;
}

//splits the line for transition functions
void PDA::splitLineForTF(string line, string &iState, char &iInput, char &iStack, string &endState, string &oStack)
{
	string lineSplit[5];
	string currentData;
	int count = 0;
	int i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			currentData += line[i];
		}
		else
		{
			lineSplit[count] = currentData;
			count++;
			currentData = "";
		}
		i++;
	}
	lineSplit[count] = currentData;
	iState = lineSplit[0]; iInput = lineSplit[1][0]; iStack = lineSplit[2][0];
	endState = lineSplit[3]; oStack = lineSplit[4];
}

PDA::PDA(string definitionFilePath) {
	string fileEX = "pda.def";
	//open and parse the def file
	ifstream fin;
	fin.open(fileEX);
	char line[256];
	
	//get the state alphabet
	while (fin.getline(line, 256))
	{
		string sline = line;
		if (sline.find("STATES:"))
		{
			// splitLineForString();
			stateAlphabetSize = 5;
			break;
		}
	}

	//get the input alphabet
	while (fin.getline(line, 256))
	{
		string sline = line;
		if (sline.find("INPUT_ALPHABET:"))
		{
			//splitLineForChar();
			inputAlphabetSize = 5;
			break;
		}
	}

	//get the stack function
	while (fin.getline(line, 256))
	{
		string sline = line;
		if (sline.find("STACK_ALPHABET:"))
		{
			//splitLineForChar();
			stackAlphabetSize = 5;
			break;
		}
	}
	
	//get to transition function
	while (fin.getline(line, 256))
	{
		string sline = line;
		if (sline.find("TRANSITION_FUNCTION:"))
		{
			break;
		}
	}


	//fill arrays
	string transition_line;
	string iState, eState, oStack;
	char iInput, iStack;
	while (fin.getline(line, 256))
	{
		if (line[0] != 's')
			break;
		string ex_pda_line = "s0 a X s1 XY";
		splitLineForTF(ex_pda_line, iState, iInput, iStack, eState, oStack);
		EndState e(eState, oStack);
		addToTFList(iState, iInput, iStack, e);
	}
	//


}

PDA::~PDA() {}