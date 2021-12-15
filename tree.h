#pragma once
#include "Node.h"
#include "TransitionFunction.h"
#include "Transition.h"

template <class T>
class Tree {
public:
	Tree(T *headData);
	~Tree() {}

	bool endStateFound(list<string> endStates);
	void checkForEndState(Node<T>* head, bool& found, list<string> endStates);
	
	int growTree() { return 0; }
	int growTree(list<TransitionFunction> transitionFunctions);
	void displayTree(bool Truncate);
	void displayTreeInner(Node<Transition>* node, string prev_path, bool truncate);
	string getInitString();

private:
	list<Node<T>*> getLeaves(Node<T>* node);
	list<Node<T>*> getNextLevel(list<Node<T>*> prevLevelNodes);
	Node<T>* head;
};

template <class T> 
Tree<T>::Tree(T *headData)
{
	this->head = new Node<T>(NULL, headData, 0);
}


template<class T>
inline bool Tree<T>::endStateFound(list<string> endStates)
{
	bool found = false;
	checkForEndState(head, found, endStates);
	return found;
}

template<class T>
inline void Tree<T>::checkForEndState(Node<T>* head, bool& found, list<string> endStates)
{
	list<Node<T>*> headChildren = head->getChildren();
	if (headChildren.size() > 0)
	{
		for (typename list<Node<T>*>::iterator it = headChildren.begin(); it != headChildren.end(); it++)
		{
			checkForEndState(*it, found, endStates);
		}
	}
	else
	{
		for (list<string>::iterator it = endStates.begin(); it != endStates.end(); it++)
		{
			string s = *it;
			T *data = head->getData();
			if ( *data == s)
				found = true;
		}
	}
}


template<>
int Tree<Transition>::growTree(list<TransitionFunction> transitionFunctions) {
	int newNodes = 0;
	//get the leaf nodes, and add children to each of them
	list<Node<Transition>*> leaves = getLeaves(this->head);
	for (typename list<Node<Transition>*>::iterator it = leaves.begin(); it != leaves.end(); it++) {
		//for each leaf node:
		//cout << "leaf: " << (*it)->getData()->getInput() << " " << (*it)->getData()->getState() << " " << (*it)->getData()->getStack() << endl;
		list<Transition> childTransitions = (*it)->getData()->getNextTransitions(transitionFunctions);
		for (typename list<Transition>::iterator it2 = childTransitions.begin(); it2 != childTransitions.end(); it2++) {
			//create a child node for each child transition
			Transition *t = new Transition(it2->getState(), it2->getInput(), it2->getStack());
			Node<Transition>* newNode = new Node<Transition>((*it), t, (*it)->getDepth()+1);
			(*it)->addChild(newNode);
			newNodes++;
			//cout << "newNode: " << (*it)->getData()->getInput() << " " << (*it)->getData()->getState() << " " << (*it)->getData()->getStack() << endl;
		}
	}
	return newNodes;
}

template<>
void Tree<Transition>::displayTree(bool Truncate) {
	//display each path in the tree, start the recursive function
	Transition* transition = this->head->getData();
	if (Truncate)
	{
		displayTreeInner(this->head, "( " + transition->getInput() + ", " + transition->getState() + ")", true);
	}
	else
	{
		displayTreeInner(this->head, "( " + transition->getInput() + ", " + transition->getState() + ", " + transition->getStack() + " )", false);
	}
	
}

template<>
void Tree<Transition>::displayTreeInner(Node<Transition>* node, string prev_path, bool truncate) {
	//recursively display paths of the tree
	if (node->getChildrenSize()) {
		list<Node<Transition>*> children = node->getChildren();
		for (typename list<Node<Transition>*>::iterator it = children.begin(); it != children.end(); it++) {
			if (truncate)
			{
				Transition* transition = (*it)->getData();
				string new_path = prev_path + " -> ( " + transition->getInput() + ", " + transition->getState() + " )";
				displayTreeInner((*it), new_path, truncate);
			}
			else
			{
				Transition* transition = (*it)->getData();
				string new_path = prev_path + " -> ( " + transition->getInput() + ", " + transition->getState() + ", " + transition->getStack() + " )";
				displayTreeInner((*it), new_path, truncate);
			}
			
		}
	}
	else {
		cout << prev_path << endl;
	}
	return;
}

template<class T>
list<Node<T>*> Tree<T>::getNextLevel(list<Node<T>*> prevLevelNodes) {
	list<Node<T>*> nextLevelNodes;
	for (typename list<Node<T>*>::iterator it = prevLevelNodes.begin(); it != prevLevelNodes.end(); it++) {
		//nextLevelNodes.merge((*it)->getChildren());
		nextLevelNodes.splice(end(nextLevelNodes), (*it)->getChildren());
	}
	return nextLevelNodes;
}

template <class T>
list<Node<T>*> Tree<T>::getLeaves(Node<T>* node) {
	//recursive traversal function to get a list of all the leaf nodes
	list<Node<T>*> leafNodes;
	if (node->getChildrenSize()) {
		list<Node<T>*> children = node->getChildren();
		for (typename list<Node<T>*>::iterator it = children.begin(); it != children.end(); it++) {
			//leafNodes.merge(getLeaves(*it));
			leafNodes.splice(end(leafNodes), getLeaves(*it));
		}
	}
	else {
		leafNodes.push_back(node);
	}
	return leafNodes;
}

template <>
string Tree<Transition>::getInitString() {
	return this->head->getData()->getInput();
}
