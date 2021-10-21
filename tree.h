#pragma once
#include "Node.h"

template <class T>
class Tree {
public:
	Tree(T *headData);
	int growTree();

private:
	list<Node<T>*> getLeaves(Node<T>* node);
	Node<T>* head;
};

template <class T> 
Tree<T>::Tree(T *headData)
{
	this->head = new Node<T>(NULL, headData, 0);
}

template <class T>
int Tree<T>::growTree() {
	list<Node<T>*> leaves = getLeaves(this->head);

	for (typename list<Node<T>*>::iterator it = leaves.begin(); it != leaves.end(); it++) {
		cout << "leaf" << endl;
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