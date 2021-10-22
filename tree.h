#pragma once
#include "Node.h"
#include "TransitionFunction.h"
#include "Transition.h"

template <class T>
class Tree {
public:
	Tree(T *headData);
	int growTree() { return 0; }
	int growTree(list<TransitionFunction> transitionFunctions);

private:
	list<Node<T>*> getLeaves(Node<T>* node);
	Node<T>* head;
};

template <class T> 
Tree<T>::Tree(T *headData)
{
	this->head = new Node<T>(NULL, headData, 0);
}

template<>
int Tree<Transition>::growTree(list<TransitionFunction> transitionFunctions) {
	//get the leaf nodes, and add children to each of them
	list<Node<Transition>*> leaves = getLeaves(this->head);
	for (typename list<Node<Transition>*>::iterator it = leaves.begin(); it != leaves.end(); it++) {
		//for each leaf node:
		cout << "leaf: " << (*it)->getData()->getInput() << " " << (*it)->getData()->getState() << " " << (*it)->getData()->getStack() << endl;
		list<Transition> childTransitions = (*it)->getData()->getNextTransitions(transitionFunctions);
		for (typename list<Transition>::iterator it2 = childTransitions.begin(); it2 != childTransitions.end(); it2++) {
			//create a child node for each child transition
			Transition *t = new Transition(it2->getState(), it2->getInput(), it2->getStack());
			Node<Transition>* newNode = new Node<Transition>((*it), t, (*it)->getDepth()+1);
			(*it)->addChild(newNode);
			cout << "newNode: " << (*it)->getData()->getInput() << " " << (*it)->getData()->getState() << " " << (*it)->getData()->getStack() << endl;
		}
	}
	return 0;
}

template <class T>
list<Node<T>*> Tree<T>::getLeaves(Node<T>* node) {
	//recursive traversal function to get a list of all the leaf nodes
	list<Node<T>*> leafNodes;
	if (node->getChildrenSize()) {
		list<Node<T>*> children = node->getChildren();
		for (typename list<Node<T>*>::iterator it = children.begin(); it != children.end(); it++) {
			leafNodes.merge(getLeaves(*it));
		}
	}
	else {
		leafNodes.push_back(node);
	}
	return leafNodes;
}