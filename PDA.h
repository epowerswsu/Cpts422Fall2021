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
	PDA();
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

	list<string> stateAlphabet;
	list<char> stackAlphabet;
	list<char> inputAlphabet;
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
	bool add = false;
	if (transitionFunctions.empty()) 
	{
		TransitionFunction tf(state, input, stack, e);
		transitionFunctions.push_back(tf);
		return true;
	}

	//go through the list and search for the same start state
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it!=transitionFunctions.end(); it++)
	{ 
		if (it->getStartState() == state && it->getInput() == input && it->getStackTop() == stack)
		{
			add = it->newEndState(e);
			if (add)
				it->addEndState(e);
			return add;
		}
	/*	else
		{
			TransitionFunction tf(state, input, stack, e);
			transitionFunctions.push_back(tf);
			return true;
		}*/
	}
	TransitionFunction tf(state, input, stack, e);
	transitionFunctions.push_back(tf);
	return true;
}

//splits the line for transition functions
void PDA::splitLineForTF(string line, string &iState, char &iInput, char &iStack, string &endState, string &oStack)
{
	string lineSplit[6];
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
			if (currentData != "")
			{
				lineSplit[count] = currentData;
				count++;
				currentData = "";
			}
		}
		i++;
	}
	lineSplit[count] = currentData;
	iState = lineSplit[0]; iInput = lineSplit[1][0]; iStack = lineSplit[2][0];
	endState = lineSplit[3]; oStack = lineSplit[4];
}

PDA::PDA()
{

}

PDA::PDA(string definitionFilePath) 
{
	//open and parse the def file
	ifstream fin;
	fin.open(definitionFilePath, ios::in);
	
	string line;
	string addToList = "";
	
	//get the state alphabet **this one works**
	while (getline(fin, line))
	{
		bool x = line.find("STATES:");
		if (!x)
		{
			int i = 0;
			while (line[i] != ' ') { i++; }
			i++;
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if(!addToList.empty())
						stateAlphabet.push_back(addToList);
					addToList = "";
				}
				else
					addToList += line[i];
			}
			if (!addToList.empty())
				stateAlphabet.push_back(addToList);
			addToList = "";
			stateAlphabetSize = stateAlphabet.size();
			break;
		}
		//cout << line;
		//getline(fin, line);
	}

	//get the input alphabet
	while (getline(fin, line))
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
	while (getline(fin, line))
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
	while (getline(fin, line))
	{
		if (!line.find("TRANSITION_FUNCTION:"))
		{
			break;
		}
	}


	//fill arrays
	string transition_line;
	string iState, eState, oStack;
	char iInput, iStack;
	while (getline(fin, line))
	{
		if (line == "")
			break;
		//string ex_pda_line = "s0 a X  s1 XY";
		//splitLineForTF(ex_pda_line, iState, iInput, iStack, eState, oStack);
		
		splitLineForTF(line, iState, iInput, iStack, eState, oStack);
		EndState e(eState, oStack);
		addToTFList(iState, iInput, iStack, e);
	}
	
	//get the endstate and other stuff too.

	fin.close();
}

PDA::~PDA() {}