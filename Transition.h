#pragma once
#include <string>
#include "TransitionFunction.h"
#include "endstate.h"



class Transition {
public:
	//Transition() { state = ""; input = ""; stack = ""; }
	Transition(string state, string input, string stack);
	list<Transition> getNextTransitions(list<TransitionFunction> transitionFunctions);
	string getState() { return this->state; }
	string getInput() { return this->input; }
	string getStack() { return this->stack; }
	
	Transition(const Transition& t) { state = t.state; input = t.input; stack = t.stack; }
	Transition& operator=(const Transition& rhs) { state = rhs.state; input = rhs.input; stack = rhs.stack; }
	bool operator==(std::string rhs) 
	{ 
		if (state+'\0' == rhs)
			return true; 
		else return false; 
	}
	bool operator==(Transition& rhs) 
	{ 
		if (state == rhs.getState()) 
			return true; 
		else return false; }
	//bool operator==(basic_string<char, char_traits<char>, allocator<char>>& rhs) 
	//{ if (state == rhs) return true; else return false;  }

private:
	string state;
	string input;
	string stack;
};

Transition::Transition(string state, string input, string stack) {
	this->state = state;
	this->input = input;
	this->stack = stack;
}

list<Transition> Transition::getNextTransitions(list<TransitionFunction> transitionFunctions) {
	//given a list of transition functions, determine all of the resulting transitions (child nodes), and a return them in a list
	list<Transition> transitions;
	for (list<TransitionFunction>::iterator it = transitionFunctions.begin(); it != transitionFunctions.end(); it++) {
		//cout << "start state: " << this->state << " == " << it->getStartState() << endl;
		//cout << "input: " << this->input[0] << " == " << it->getInput() << endl;
		//cout << "stacktop: " << this->stack[0] << " == " << it->getStackTop() << endl;
		if (it->getStartState() == this->state && it->getInput() == this->input[0] && it->getStackTop() == this->stack[0]) {
			list<EndState> endStates = it->getEndStates();
			for (list<EndState>::iterator it2 = endStates.begin(); it2 != endStates.end(); it2++) {
				string newStack;
				if (it2->getStack().size() > 1)
					newStack = it2->getStack()[0] + this->stack; //add top character to new stack
				else if (it2->getStack()[0] == '\\')
					newStack = this->stack.substr(1, this->stack.size() - 1); // '\' means pop from the stack
				else
					newStack = this->stack; //no change to stack
				string newInput = input.substr(1, input.size() - 1);

				//the \ character represents empty/epsilon
				if(newStack.size() == 0)
					newStack = "\\";
				if (newInput.size() == 0)
					newInput = "\\";

				transitions.push_back(Transition(it2->getState(), newInput, newStack));
			}
		}
	}

	return transitions;
}
