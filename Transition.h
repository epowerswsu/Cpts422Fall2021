#pragma once
#include "TransitionFunction.h"
#include "endstate.h"


class Transition {
public:
	Transition(string state, string input, string stack);
	list<Transition> getNextTransitions(list<TransitionFunction> transitionFunctions);
	string getState() { return this->state; }
	string getInput() { return this->input; }
	string getStack() { return this->stack; }

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

		if (it->getStartState() == this->state && it->getInput() == this->input[0] && it->getStackTop() == this->stack[0]) {
			list<EndState> endStates = it->getEndStates();
			for (list<EndState>::iterator it2 = endStates.begin(); it2 != endStates.end(); it2++) {
				string newStack;
				if (it2->getStack().size() > 1)
					newStack = it2->getStack()[0] + this->stack; //add top character to new stack
				else
					newStack = this->stack; //no change to stack
				string newInput = input.substr(1, input.size() - 1);
				transitions.push_back(Transition(it2->getState(), newInput, newStack));
			}
		}
	}

	return transitions;
}
