#pragma once
#include <list>
#include <string>

template <class T> class Node {
public:
	Node(Node* parent, T info);
	Node(T info);
	~Node();

	void addChild(Node* child) { this->children.push_back(child); }
	int getChildrenSize() { return children->size(); }


private:
	T data;
	
	Node* parent;
	std::list<Node*> children;
};

template<class T>
Node<T>::Node(Node* parent, T info)
{
	this->parent = parent;
	data = info
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
