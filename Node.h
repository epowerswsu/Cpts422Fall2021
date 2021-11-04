#pragma once
#include <list>
#include <string>

template <class T> class Node {
public:
	Node(Node<T>* parent, T* data, int depth);
	Node(T info);
	~Node();

	void addChild(Node<T>* child) { this->children.push_back(child); }
	std::list<Node<T>*> getChildren() { return this->children; }
	int getChildrenSize() { return children.size(); }
	int getDepth() { return this->depth; }
	T* getData() { return this->data; }


private:
	T *data;
	int depth;
	Node<T>* parent;
	std::list<Node<T>*> children;
};

template<class T>
Node<T>::Node(Node* parent, T* data, int depth)
{
	this->parent = parent;
	this->data = data;
	this->depth = depth;
}

template<class T>
Node<T>::Node(T info)
{
	this->parent = parent;
	data = info;
	this->depth = 0;
}

template <class T> 
Node<T>::~Node() 
{

}
