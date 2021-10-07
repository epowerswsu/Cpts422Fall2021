/******************************************************************************
 * PDA main function
 *	Class: cpts422 Fall 2021
 *  Professor: Luis DeLaTorre
 * 
 *	Authors: Jacob Halter 
 *			 Ethan Powers
 *			 Nathan cross
 ******************************************************************************
 * Description:
 *	The PDA function does ... etc.
 ******************************************************************************/

//C++ libraries
#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <string>

//Additional Created files
#include "endState.h"
#include "TransitionFunction.h"

using namespace std;

//Global variables for flagging
bool PDA_OPEN;

void displayInstructions()
{
	cout << "list of instructions"
		 << "\t";
}

char getInput()
{
//UPDATE TO MAKE SURE INPUT IS VALID
	char x;
	cin >> x;
	return x;
}

void mainProgramLoop()
{
	char input = 'h';
	while (input != 'E' && input != 'e')
	{
		input = getInput();
		switch (input)
		{
		case 'C':
		case 'c':
			closePDA();
			break;
		case'D':
		case'd':
			deleteInputStr();
		default:
			break;
		}
	}
}

void introduction()
{
	cout << "Pushdown automata is an abstract mathematical model of a computer. Pushdown\n"
		 << "automata are nondeterministic, meaning that for the same input the program may\n" 
		 <<	"produce a different output. These automata incorporate a stack that the data is\n"
		 << "stored and consumed from.These models, depending on their transition rules can\n" 
		 << "have one to many different states.There is an input tape that is parsed\n" 
		 << "throughand depending on the transitions of the machine, the state of the machine\n"
		 << "may change and data can be put on or removed from the stack.\n\n";
}

int main(int argc, char ** argv)
{
	//set some flags
	PDA_OPEN = false;

	//display a greeting 
	introduction();

	//this will run until user inputs the close application command
	mainProgramLoop();

	return 0;
}