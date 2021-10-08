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
bool PDA_RUNNING;
list<string> inputStr;

//configurations
int TRANSITIONS;
bool TRUNCATE_DISP;

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
	cout << "list of instructions\n"
		<< "   \'c\' or \'C\' | \n"
		<< "   \'d\' or \'D\' | \n"
		<< "   \'e\' or \'E\' | exits the application\n"
		<< "   \'h\' or \'H\' | \n"
		<< "   \'i\' or \'I\' | \n"
		<< "   \'l\' or \'L\' | \n"
		<< "   \'o\' or \'O\' | \n"
		<< "   \'p\' or \'P\' | \n"
		<< "   \'q\' or \'Q\' | \n"
		<< "   \'r\' or \'R\' | \n"
		<< "   \'s\' or \'S\' | \n"
		<< "   \'t\' or \'T\' | \n"
		<< "   \'v\' or \'V\' | \n\n";

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
		cout << "please close the current PDA before opening a new one!\n\n";
	//this is the big complex issue!!!
		//getPDADefinition Filename

		//CREATE or EDIT the PDA

}

//‘P’ or ‘p’ Display Paths
void displayPaths()
{
	cout << "paths\n\n";
}

//‘Q’ or ‘q' Quit Pushdown Automaton
void quitPDA()
{
	if (PDA_RUNNING)
		;//stop
	else
		;//why are you here?
}

//‘R’ or ‘r’ Run Pushdown Automaton
void RunPDA()
{
	if (!PDA_RUNNING)
	{
		PDA_RUNNING = true;//start it
	}
	else
	{
		//continue however many steps or until done.
		PDA_RUNNING = false;
	}
}

//‘S’ or ‘s’ Set Transitions
int setTransitions()
{
	cout << "set transitions: ";
	int t;
	cin >> t;
	cout << "\n\n";
	return t;
}

//‘T’ or ‘t’ Truncate Instantaneous Descriptions
void toggleTruncation()
{
	TRUNCATE_DISP = !TRUNCATE_DISP;
	cout << "truncate was turned o"
		<< ((TRUNCATE_DISP) ? "n" : "ff") << "\n\n";
}

//‘V’ or ‘v’ View Pushdown Automaton
void viewPDA()
{
	cout << "view PDA\n\n";
}

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
	char input = 'a';
	bool exitApp = false;
	displayInstructions();
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
		case 'L':
		case 'l':
			listInputStr();
			break;
		case 'O':
		case 'o':
			openPDA();
			break;
		case 'P':
		case 'p':
			displayPaths();
			break;
		case 'Q':
		case 'q':
			quitPDA();
			break;
		case 'R':
		case 'r':
			RunPDA();
			break;
		case 'S':
		case 's':
			TRANSITIONS = setTransitions();
			break;
		case 'T':
		case 't':
			toggleTruncation();
			break;
		case 'V':
		case 'v':
			viewPDA();
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
		<< "produce a different output. These automata incorporate a stack that the data is\n"
		<< "stored and consumed from.These models, depending on their transition rules can\n"
		<< "have one to many different states.There is an input tape that is parsed\n"
		<< "throughand depending on the transitions of the machine, the state of the machine\n"
		<< "may change and data can be put on or removed from the stack.\n\n";
}

int main(int argc, char** argv)
{
	//set some flags
	PDA_OPEN = false;
	PDA_RUNNING = false;

	//should be load config file
	TRANSITIONS = 1;
	TRUNCATE_DISP = false;

	//display a greeting 
	introduction();

	//this will run until user inputs the close application command
	mainProgramLoop();

	return 0;
}