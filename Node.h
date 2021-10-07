#pragma once
#include <list>
#include <string>

class Node {
public:
	Node* parent;
	std::string state;
	std::string remainingChars;
	std::string stack;
	std::list<Node*> children;

	Node(Node* parent, std::string state, std::string remainingChars, std::string stack);
	~Node();
	void addChild(Node* child); //PDA class can determine the children of a node using the list of transitions
};

Node::Node(Node* parent, std::string state, std::string remainingChars, std::string stack) {
	this->parent = parent;
	this->state = state;
	this->remainingChars = remainingChars;
	this->stack = stack;
}

Node::~Node() {}

void Node::addChild(Node* child) {
	this->children.push_back(child);
}