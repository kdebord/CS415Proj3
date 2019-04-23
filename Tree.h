#ifndef TREE_H
#define TREE_H

#include <iostream>

using namespace std;

struct Node {
	Node() { small = -1; large = -1; }
	Node(int nVal) { small = nVal; large = -1; }
	int small;
	int large;
	Node* left = NULL;
	Node* middle = NULL;
	Node* right = NULL;
	Node* parent = NULL;
	bool full = false;
};

class Tree {
public:
	Tree();

	Node* insert(int);

private:
	Node* insert(Node*, int);
	Node* split(Node*, int);


	Node* top;
};

#endif // TREE_H
