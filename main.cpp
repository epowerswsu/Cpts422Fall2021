/******************************************************************************
 * PDA main function
 *	Class: cpts422 Fall 2021
 *  Professor: Luis DeLaTorre
 *
 *	Authors: Jacob Halter
 *			 Ethan Powers
 *			 Nathan Cross
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
#include "PDA.h"
#include "Node.h"
#include "Config.h"
#include "tree.h"

//Global variables for flagging
bool PDA_OPEN;
bool PDA_RUNNING;
bool PDA_HAS_RUN;
list<string> inputStr;
int currentStringIndex;
PDA *pushDownAutomata = nullptr;

string getString(string query)
{
	string answer;
	while (true)
	{
		cout << query;
		cin >> answer;
		if (cin.fail())
		{
			cout << "Please enter valid input\n";
			cin.clear();
		}
		else 
			return answer;
	}
	return answer;
}

//'C' or 'c' Close Pushdown Automaton
void closePDA()
{
	if (PDA_OPEN)
	{
		//close pda
		PDA_OPEN = false;
		delete pushDownAutomata;
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
	if (inputStr.size() < x || x <= 0)
	{
		cout << "no input found at position: " << x << ".\n";
	}
	else
	{
		int count = 0;
		list<string>::iterator it = inputStr.begin();
		x--;
		while (count < x)
		{
			count++;
			it++;
		}
		inputStr.remove(*it);
	}
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
		<< "   \'c\' or \'C\' | Close Pushdown Automaton\n"
		<< "   \'d\' or \'D\' | Delete Input Strings\n"
		<< "   \'e\' or \'E\' | exits the application\n"
		<< "   \'h\' or \'H\' | help user\n"
		<< "   \'i\' or \'I\' | Insert Input String\n"
		<< "   \'l\' or \'L\' | List Input Strings\n"
		<< "   \'o\' or \'O\' | Open Pushdown Automaton\n"
		<< "   \'p\' or \'P\' | Display Paths\n"
		<< "   \'q\' or \'Q\' | Quit Pushdown Automaton\n"
		<< "   \'r\' or \'R\' | Run Pushdown Automaton\n"
		<< "   \'s\' or \'S\' | Set number of Transitions\n"
		<< "   \'t\' or \'T\' | Truncate Instantaneous Descriptions\n"
		<< "   \'v\' or \'V\' | View Pushdown Automaton\n\n";
}

//‘I’ or ‘i’ Insert Input String
void addInputStr(int maxChars)
{
	string addToInputStr;
	addToInputStr = getString("Input string to add to the list of input strings: ");
	if (addToInputStr.size() > maxChars) {
		cout << "Error: string size was greater than character limit (" << maxChars << ")" << endl;
		cout << "MAXIMUM_CHARACTERS is defined in ConfigFile.txt" << endl;
		return;
	}
	inputStr.push_back(addToInputStr);
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
	else
	{
		string PDADefFile;
		while (true) //make sure file is a .def file and then make sure we can open it.
		{
			PDADefFile = getString("Enter file path to your PDA definition file: ");
			if (!PDADefFile.find(".def"))
			{
				cout << "Please enter a \'.def\' file\n";
			}
			else
			{
				ifstream fin;
				fin.open(PDADefFile);
				if (fin.fail())
				{
					cout << "Error opening file, please try again\n";
				}
				else 
				{
					fin.close();
					break;
				}
			}
		}
		pushDownAutomata = new PDA(PDADefFile);
		pushDownAutomata->displayTF();
		PDA_OPEN = true;
	}
}
	


//‘P’ or ‘p’ Display Paths
void displayPaths(bool Truncate)
{
	if (!PDA_OPEN) {
		cout << "Error: no PDA was open, open a PDA with 'o'" << endl;
		return;
	}
	cout << "paths\n\n";
	pushDownAutomata->displayTrees(Truncate);
}

//‘Q’ or ‘q' Quit Pushdown Automaton
void quitPDA()
{
	if (PDA_OPEN && PDA_HAS_RUN)
	{
		cout << "clearing current PDA\n";//stop
		//pushDownAutomata->displayTrees();
		pushDownAutomata->clearTrees();
		PDA_RUNNING = false;
		PDA_HAS_RUN = false;
		//delete the current trees and stop current 'runs'
		
	}
	else
		cout << "there is no PDA open\n";//why are you here?
}

//‘R’ or ‘r’ Run Pushdown Automaton
void RunPDA(int transitions)
{
	if (!PDA_OPEN) {
		cout << "There is no PDA open! Please open a PDA with 'o'" << endl;
		return;
	}

	if (inputStr.size() == 0)
	{
		cout << "There are no input strings! Add an input string with 'i'\n";
		return;
	}

	int newNodes = 0;

	if (!PDA_RUNNING)
	{
		//list out input strings for user to select from
		cout << "Select an input string to run:" << endl;
		int i = 0;
		for(list<string>::iterator it = inputStr.begin(); it!= inputStr.end() ;it++)
		{
			cout << i << ": " << *it << endl;
			i++;
		}
		cin >> currentStringIndex;
		list<string>::iterator it = inputStr.begin();
		if (currentStringIndex >= inputStr.size() || currentStringIndex < 0) {
			cout << "Error: string number was out of bounds, please enter a string" <<
				" number in the range 0 to " << inputStr.size() << endl;
			return;
		}
		advance(it, currentStringIndex);

		
		PDA_RUNNING = true;//start it
		PDA_HAS_RUN = true;
		pushDownAutomata->setInputStrings(inputStr); //only adds input strings that don't already exist in the PDA
		newNodes = pushDownAutomata->run(transitions, currentStringIndex);
		cout << "ran string " << currentStringIndex << " for " << transitions << " step(s)" << endl;
	}
	else
	{
		//continue however many steps or until done.
		newNodes = pushDownAutomata->run(transitions, currentStringIndex);
		cout << "ran string " << currentStringIndex << " for " << transitions << " step(s)" << endl;
		//PDA_RUNNING = false;
	}
	
	if (newNodes == 0) {
		cout << "finished running string " << currentStringIndex << ", press 'p' to view paths" << endl;
		for (int i = 0; i < pushDownAutomata->getNumTrees(); i++)
		{
			bool pda_success = pushDownAutomata->endStateAchieved(i);
			cout << "input string #" << i << ". ";
			if (pda_success)
				cout << "This input string was accepted\n\n";
			else
				cout << "this input string failed\n\n";
		}
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
bool toggleTruncation(bool currentTruncation)
{
	if (!currentTruncation)
	{
		cout << "truncate was turned on" << endl;
		return true;
	}
	else
	{
		cout << "truncate was turned off" << endl;
		return false;
	}
}

//‘V’ or ‘v’ View Pushdown Automaton
void viewPDA()
{
	//cout << "view PDA\n\n";
	if (PDA_OPEN)
	{
		pushDownAutomata->displayTF();
	}
	else
	{
		cout << "There is no open PDA file to view" << endl;
	}
}

char getInput()
{
	//UPDATE TO MAKE SURE INPUT IS VALID
	cout << "  > ";
	char x;
	cin >> x;
	cin.clear();
	return x;
}

void mainProgramLoop()
{
	Config config("ConfigFile.txt"); //read initial settings from config file
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
			addInputStr(config.maxCharacters);
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
			displayPaths((bool)config.truncated);
			break;
		case 'Q':
		case 'q':
			quitPDA();
			break;
		case 'R':
		case 'r':
			RunPDA(config.transitionsPerStep);
			break;
		case 'S':
		case 's':
			config.transitionsPerStep = setTransitions();
			break;
		case 'T':
		case 't':
			config.truncated = toggleTruncation(config.truncated);
			break;
		case 'V':
		case 'v':
			viewPDA();
			break;
		default:
			break;
		}
	}
	//save changes to input strings file
	//save changes to config file
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
	PDA_HAS_RUN = false;

	//display a greeting 
	introduction();

	//this will run until user inputs the close application command
	mainProgramLoop();

	return 0;
}