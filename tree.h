#pragma once
#include "Node.h"

template <class T>
class Tree {
public:
	Tree(Node<T>* head);

private:
	Node<T>* head;
};

template <class T> 
Tree<T>::Tree(Node<T>* head)
{
	this->head = head;
}