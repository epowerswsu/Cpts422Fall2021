#pragma once
#include <list>
#include <string>

template <class T> class Node {
public:
	Node(Node<T>* parent, T info);
	Node(T info);
	~Node();

	void addChild(Node<T>* child) { this->children.push_back(child); }
	int getChildrenSize() { return children->size(); }


private:
	T data;
	
	Node<T>* parent;
	std::list<Node<T>*> children;
};

template<class T>
Node<T>::Node(Node* parent, T data)
{
	this->parent = parent;
	this->data = data;
}

template<class T>
Node<T>::Node(T info)
{
	this->parent = parent;
	data = info;
}

template <class T> 
Node<T>::~Node() 
{

}
