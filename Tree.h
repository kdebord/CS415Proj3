#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
	Node() { small = ""; large = ""; }
	Node(string nVal) { small = nVal; large = ""; }
	string small;
	string large;
	Node* left = NULL;
	Node* middle = NULL;
	Node* right = NULL;
	Node* parent = NULL;
	bool full = false;
};

class Tree {
public:
	Tree();

	Node* insert(string);

private:
	Node* insert(Node*, string);
	Node* split(Node*, string);


	Node* top;
};

#endif // TREE_H
