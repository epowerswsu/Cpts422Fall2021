#pragma once

#include <fstream>
//#include <list>

#include "TransitionFunction.h"
#include "Node.h"
#include "Tree.h"
#include "Transition.h"

/*
*	PDA 
*/
class PDA {
public:
	PDA(string definitionFilePath);
	~PDA();

	//int stackAlphabetSize, inputAlphabetSize, stateAlphabetSize;
	bool isNewStartState(string state, char input, char stack, list<TransitionFunction>::iterator& found);
	bool addToTFList(string state, char input, char stack, EndState e);
	void splitLineForTF(string line, string& iState, char& iInput, char& iStack, string& endstate, string& oStack);

	void displayTF();
	
	//Getters
	string getInitialState() { return initialState; }
	char getInitialStack() { return initialStack; }
	int getStateAlphabetSize() { return stateAlphabet.size(); }
	int getStackAlphabetSize() { return stackAlphabet.size(); }
	int getinputAlphabetSize() { return inputAlphabet.size(); }

	//tree operations
	int setInputStrings(list<string> inputStrings);
	int run(int steps, int stringIndex);
	void displayTrees(bool truncate);
	void clearTrees(); //called when q is pressed

private:
	string initialState;
	char initialStack;

	list<string> stateAlphabet;
	list<char> stackAlphabet;
	list<char> inputAlphabet;
	list<TransitionFunction> transitionFunctions;
	list<string> endStates;
	list<Tree<Transition>> trees;
};

//
void PDA::displayTF()
{
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it != transitionFunctions.end(); it++)
	{
		cout << it->getStartState() << "\t" << it->getInput() << "\t" << it->getStackTop() << "\t";
		it->displayEndStates();
	}
	cout << endl;
}

bool PDA::isNewStartState(string state, char input, char stack, list<TransitionFunction>::iterator &found)
{
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it != transitionFunctions.end(); it++)
	{
		if (it->getStartState() == state && it->getInput() == input && it->getStackTop() == stack)
		{
			found = it;
			return false;
		}
	}
	return true;
}

//If a new state is added to the PDA, return true. If the state passed in is a duplicate return false
bool PDA::addToTFList(string state, char input, char stack, EndState e)
{
	list<TransitionFunction>::iterator it = transitionFunctions.begin();
	if (isNewStartState(state, input, stack, it))
	{
		TransitionFunction tf(state, input, stack, e);
		transitionFunctions.push_back(tf);
		return true;
	}
	else
	{
		if (it->newEndState(e))
		{
			it->addEndState(e);
			return true;
		}
		else
			return false;
	}

	return false;
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

PDA::PDA(string definitionFilePath) 
{
	//open and parse the def file
	ifstream fin;
	fin.open(definitionFilePath, ios::in);
	if (fin.fail())
	{
		cout << "Error opening file " << definitionFilePath << "\n\n";
		return;
	}
	string line;
	string addToList = "";
	int i = 0;

	//get the state alphabet **this one works**
	while (getline(fin, line))
	{
		if (!line.find("STATES:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
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
			break;
		}
	}

	//get the input alphabet
	while (getline(fin, line))
	{
		if (!line.find("INPUT_ALPHABET:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (!addToList.empty())
						inputAlphabet.push_back(addToList[0]);
					addToList = "";
				}
				else
					addToList += line[i];
			}
			if (!addToList.empty())
				inputAlphabet.push_back(addToList[0]);
			addToList = "";
			break;
		}
	}

	//get the stack alphabet
	while (getline(fin, line))
	{
		if (!line.find("STACK_ALPHABET:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (!addToList.empty())
						stackAlphabet.push_back(addToList[0]);
					addToList = "";
				}
				else
					addToList += line[i];
			}
			if (!addToList.empty())
				stackAlphabet.push_back(addToList[0]);
			addToList = "";
			break;
		}
	}
	
	//get to transition function
	while (getline(fin, line))
	{
		if (!line.find("TRANSITION_FUNCTION:"))
			break;
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
	
	//Initial State
	while (getline(fin, line))
	{
		if (!line.find("INITIAL_STATE:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (!addToList.empty())
						initialState = addToList;
					addToList = "";
				}
				else
					addToList += line[i];
			}
			addToList = "";
			break;
		}
	}

	//Start character
	while (getline(fin, line))
	{
		if (!line.find("START_CHARACTER:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (!addToList.empty())
						initialStack = addToList[0];
					addToList = "";
				}
				else
					addToList += line[i];
			}
			if (!addToList.empty())
				initialStack = addToList[0];
			addToList = "";
			break;
		}
	}

	//Final States
	while (getline(fin, line))
	{
		if (!line.find("FINAL_STATES:"))
		{
			i = 0;
			addToList = "";
			while (line[i] != ' ') { i++; }
			for (i; i <= line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (!addToList.empty())
						endStates.push_back(addToList);
					addToList = "";
				}
				else
					addToList += line[i];
			}
			if (!addToList.empty())
				endStates.push_back(addToList);
			addToList = "";
			break;
		}
	}

	//end file
	fin.close();
}

PDA::~PDA()
{

}

//tree operations
int PDA::setInputStrings(list<string> inputStrings) {
	//create a tree for each input string
	int total_trees = 0;
	bool stringExists;

	for (list<string>::iterator it = inputStrings.begin(); it != inputStrings.end(); it++) {
		//check if the string already exists in the trees list or not
		stringExists = false;
		for (list<Tree<Transition>>::iterator it2 = trees.begin(); it2 != trees.end(); it2++) {
			if (it2->getInitString() == *it) {
				stringExists = true;
				break;
			}
		}
		//if string was not alreay added as a tree before, then add it now
		if (!stringExists) {
			Transition* t = new Transition(initialState, *it, string(1, initialStack));
			Tree<Transition> tree(t);
			trees.push_back(tree);
			total_trees++;
		}
	}
	return total_trees;
}

int PDA::run(int steps, int stringIndex) {
	if (stringIndex >= this->trees.size()) {
		cout << "Error: string number was out of bounds, please enter a string" <<
			" number less than " << this->trees.size() << endl;
		return 0;
	}
	int nodesAdded = 0;
	list<Tree<Transition>>::iterator it = trees.begin();
	advance(it, stringIndex);
	for (int i = 0; i < steps; i++) {
		//for each tree, grow a certain number of steps
		nodesAdded += it->growTree(this->transitionFunctions);
	}

	return nodesAdded;
}

void PDA::displayTrees(bool truncate) {
	int i = 0;
	for (list<Tree<Transition>>::iterator it = trees.begin(); it != trees.end(); it++) {
		cout << "string " << i << ": " << it->getInitString() << endl;
		it->displayTree(truncate);
		cout << endl;
		i++;
	}
}

//void PDA::viewTrees()
/*{
	for (list<Tree<Transition>>::iterator it = trees.begin(); it != trees.end(); it++) {
		it->viewTree();
	}
}*/
void PDA::clearTrees()
{
	this->trees.clear();
}

