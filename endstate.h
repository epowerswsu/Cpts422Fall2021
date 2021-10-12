#pragma once
#include <string>

class EndState
{
public:
	EndState() {}
	EndState(string s, string a) { state = s; addToStack = a; }
	bool operator==(EndState &a);

	string getState() { return state; }
	string getStack() { return addToStack; }

private:
	string state;
	string addToStack;
};

bool EndState::operator==(EndState& a)
{
	if (this->getState() == a.getState() && this->getStack() == a.getStack())
		return true;
	else return false;
}