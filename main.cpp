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
#include <iomanip>
#include <fstream>
#include <list>
#include <stack>
#include <string>

using namespace std;

//Additional Created files
#include "endState.h"
#include "TransitionFunction.h"

//Global variables for flagging
bool PDA_OPEN;
list<string> inputStr;

//'C' or 'c' Close Pushdown Automaton
void closePDA()
{
	if (PDA_OPEN)
	{
		//close pda
	}
	else
		cout << "there is no pda open\n\n";
}

//‘D’ or ‘d’ Delete Input Strings
void deleteInputStr()
{
	cout << "enter the number of the input string you want to delete\n";
	short int x;
	cin >> x;
}

//‘E’ or ‘e’ Exit Application
bool readyToExit()
{
	return true;
}

//'H' or 'h' help user
void displayInstructions()
{
	cout << "list of instructions"
	 	 << "\t\'c\' or \'C\' | \n"
		 << "\t\'d\' or \'D\' | \n"
		 << "\t\'e\' or \'E\' | exits the application\n"
		 << "\t\'h\' or \'H\' | \n"
		 << "\t\'i\' or \'I\' | \n"
		 << "\t\'l\' or \'L\' | \n"
		 << "\t\'o\' or \'O\' | \n"
		 << "\t\'p\' or \'P\' | \n"
		 << "\t\'q\' or \'Q\' | \n"
		 << "\t\'r\' or \'R\' | \n"
		 << "\t\'s\' or \'S\' | \n"
		 << "\t\'t\' or \'T\' | \n"
		 << "\t\'v\' or \'V\' | \n\n";

}

//‘I’ or ‘i’ Insert Input String
void addInputStr()
{
	string input;
	cin >> input;
	inputStr.push_back(input);
}

//‘L’ or ‘l’ List Input Strings
void listInputStr()
{
	list<string>::iterator it;
	int count = 0;
	for (it = inputStr.begin(); it != inputStr.end(); it++)
	{
		count++;
		cout << setw(3) << count << " - " << *it << endl;
	} 
}

//‘O’ or ‘o’ Open Pushdown Automaton
void openPDA()
{
	if (PDA_OPEN)
		cout << "please close the current PDA before opening a new one!\n";
//this is the big complex issue!!!
	//getPDADefinition Filename

	//CREATE or EDIT the PDA
	
}

//‘P’ or ‘p’ Display Paths

//‘Q’ or ‘q' Quit Pushdown Automaton

//‘R’ or ‘r’ Run Pushdown Automaton

//‘S’ or ‘s’ Set Transitions

//‘T’ or ‘t’ Truncate Instantaneous Descriptions

//‘V’ or ‘v’ View Pushdown Automaton

char getInput()
{
//UPDATE TO MAKE SURE INPUT IS VALID
	cout << "  > ";
	char x;
	cin >> x;
	return x;
}

void mainProgramLoop()
{
	char input = 'h';
	bool exitApp = false;
	while (!exitApp)
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
			break;
		case 'E':
		case 'e':
			exitApp = readyToExit();
			break;
		case 'H':
		case 'h':
			displayInstructions();
			break;
		case 'I':
		case 'i':
			addInputStr();
			break;
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