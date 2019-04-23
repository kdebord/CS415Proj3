#include <iostream>

#include "Tree.h"

using namespace std;

Tree::Tree() {
	top = NULL;
}

Node* Tree::insert(int nVal) {
	insert(top, nVal);
	return top;
}

Node* Tree::insert(Node* node, int val) {
	if (node == NULL) {
		top = new Node(val);
		return top;
	}

	if (val < node->small) {
		if (node->left == NULL) {
			if (node->full) {
				split(node, val);
			}
			else {
				node->large = node->small;
				node->small = val;
				node->full = true;
			}
		}
		else {
			insert(node->left, val);
		}
	}
	else if (val > node->large) {
		if (node->right == NULL) {
			if (node->full) {
				split(node, val);
			}
			else {
				node->large = val;
				node->full = true;
			}
		}
		else {
			insert(node->right, val);
		}
	}
	else {
		if (node->middle == NULL) {
			split(node, val);
		}
		else {
			insert(node->middle, val);
		}
	}

	return top;
}

Node* Tree::split(Node* node, int val) {
	int k1;
	int k2;
	int k3;

	Node* par = node->parent;

	if (val < node->small) {
		k1 = val;
		k2 = node->small;
		k3 = node->large;
	}
	else if (val > node->large) {
		k1 = node->small;
		k2 = node->large;
		k3 = val;
	}
	else {
		k1 = node->small;
		k2 = val;
		k3 = node->large;
	}
	
	if (par == NULL) {
		Node* sNode = new Node(k1);
		Node* mNode = new Node(k2);
		Node* lNode = new Node(k3);
		
		mNode->left = sNode;
		mNode->right = lNode;

		sNode->parent = mNode;
		lNode->parent = mNode;

		top = mNode;
		return top;
	}
	else if (par->full) {
		Node* t1 = new Node;
		Node* t2 = new Node;
		Node* t3 = new Node;
		Node* t4 = new Node;
		if (k2 < par->small) {
			t1->small = k1;
			t2->small = k3;
			t3 = par->middle;
			t4 = par->right;
		}
		else if (k2 > par->large) {
			t1 = par->left;
			t2 = par->middle;
			t3->small = k1;
			t4->small = k3;
		}
		else {
			t1 = par->left;
			t2->small = k1;
			t3->small = k3;
			t4 = par->right;
		}

		Node* temp = split(par, k2);

		temp->left->left = t1;
		temp->left->right = t2;
		temp->right->left = t3;
		temp->right->right = t4;

		t1->parent = temp->left;
		t2->parent = temp->left;
		t3->parent = temp->right;
		t4->parent = temp->right;

		return temp;

	}
	else {
		Node* sNode = new Node(k1);
		Node* lNode = new Node(k3);

		if (k2 < par->small) {
			par->large = par->small;
			par->small = k2;
			
			par->left = sNode;
			par->middle = lNode;
		}
		else {
			par->large = k2;
			
			par->middle = sNode;
			par->right = lNode;
		}

		sNode->parent = par;
		lNode->parent = par;
		par->full = true;

		return par;
	}
}