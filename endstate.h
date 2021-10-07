#pragma once
#include <string>

class EndState
{
public:
	EndState() {}
	EndState(string s, string a) { state = s; addToStack = a; }

private:
	string state;
	string addToStack;
};
