#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
	Node() { small = ""; large = ""; }
	Node(string nVal) { small = nVal; large = ""; lines.resize(0);}
	string small;
	string large;
	Node* left = NULL;
	Node* middle = NULL;
	Node* right = NULL;
	Node* parent = NULL;
	bool full = false;
	vector<int> lines;
};

class Tree {
public:
	Tree();

	Node* insert(string);
	void inorderPrint(Node *t);
	Node* top;
	void printTree(ostream & out = cout);
	void buildTree(ifstream & input);
	void contains();

private:
	Node* insertHelper(Node*, string, int, int &);
	Node* split(Node*, string);
    bool isEmpty();
	bool containsHelper(const string & x, Node * t, Node* &result);
	void printTreeHelper(Node *t, ostream & out);
	int findHeight(Node *t);

};

#endif // TREE_H
