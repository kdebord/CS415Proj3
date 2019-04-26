#include <iostream>

#include "Tree.h"
#include "time.h"
#include <iomanip>
#include <sstream>

using namespace std;

Tree::Tree() {
	top = NULL;
}

Node* Tree::insert(string nVal) {
	int dist = 0;
	insertHelper(top, nVal, 0, dist);
	return top;
}

Node* Tree::insertHelper(Node* node, string val, int line, int &distWords) {
	if (node == NULL) {
		top = new Node(val);
		top->lines.push_back(line);
		distWords++;
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
				node->lines.push_back(line);
				node->full = true;
			}
		}
		else {
			insertHelper(node->left, val, line, distWords);
		}
	}
	else if (val > node->large) {
		if (node->right == NULL) {
			if (node->full) {
				split(node, val);
			}
			else {
				node->large = val;
				node->lines.push_back(line);
				node->full = true;
			}
		}
		else {
			insertHelper(node->right, val, line, distWords);
		}
	}
	else {
		if (node->middle == NULL) {
			split(node, val);
		}
		else {
			insertHelper(node->middle, val, line, distWords);
		}
	}

	return top;
}

void Tree::contains() {
	string input;
	Node *foundNode = NULL;
	cout << "Search word: ";
	cin >> input;
	if(containsHelper(input, top, foundNode)) {
		cout << "Line Numbers: " << foundNode->lines[0];
		for(int i = 1; i < foundNode->lines.size(); i++)
			cout << ", " << foundNode->lines[i];
		cout << '\n';
	} else
		cout << '\"' << input << "\" is not in the document\n";
}

bool Tree::containsHelper(const string &x, Node *t, Node *&result) {
	if (t == NULL)
		return false;
	if (t->small.compare(x) == 0 || t->large.compare(x) == 0){
		result = t;
		return true;
	}
	if(x < t->small)
	    containsHelper(x, t->left, result);
	if(t->small < t->large)
	    containsHelper(x, t->right, result);
	else if(x > t->large)
	    containsHelper(x, t->right, result);
	else
		return false;
}

Node* Tree::split(Node* node, string val) {
	string k1;
	string k2;
	string k3;

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

bool Tree::isEmpty(){
	return top == NULL;
}

void Tree::inorderPrint(Node *t){
	if(t->left == NULL && t->right == NULL && t->middle == NULL)
	{
		std:: cout << t->small << endl;
		if(t->large != "")
			std::cout << t->large << endl;
	}
	else if(t->left != NULL && t->right != NULL)
	{
		inorderPrint(t->left);
		std:: cout << t->small << endl;
		if(t->large != "")
			std::cout << t->large << endl;
		inorderPrint(t->right);
	}
	else if(t->left != NULL && t->right != NULL && t->middle != NULL)
	{
		inorderPrint(t->left);
		std::cout << t->small << endl;
		inorderPrint(t->middle);
		std::cout << t->large << endl;
		inorderPrint(t->right);
	}

}

void Tree::printTree(ostream &out) {
	out << "2-3 Tree Index:\n-------------------------\n";
	printTreeHelper(top, out);
}

void Tree::printTreeHelper(Node *t, ostream &out) {
	if(t == NULL)
		return;
	if(t->left == NULL && t->right == NULL && t->middle == NULL) {
		out << setw(30) << std::left;
		out << t->small << " " << t->lines[0];
		for (int i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
	}
	else if(t->left != NULL && t->right != NULL) {
		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->small << " " << t->lines[0];
		for (int i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
		printTreeHelper(t->right, out);
	}
	else if(t->left != NULL && t->right != NULL && t->middle != NULL) {
		printTreeHelper(t->left, out);
		out << setw(30) << std::left;
		out << t->small << " " << t->lines[0];
		for (int i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
		printTreeHelper(t->middle, out);
		out << setw(30) << std::left;
		out << t->small << " " << t->lines[0];
		for (int i = 1; i < t->lines.size(); i++)
			out << ", " << t->lines[i];
		out << endl;
		printTreeHelper(t->right, out);
	}

}

void Tree::buildTree(ifstream &input) {
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while(!input.eof()) {
		string tempLine, tempWord;

		//Reading a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
			while(tempLine[i] != ' ' && tempLine[i] != '\n' && i < tempLine.length() ){
				tempWord.insert(tempWord.end(), tempLine[i]);
				i++;
			}

			while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
				tempWord.resize(tempWord.size() -1);

			if(tempWord.length() > 0)
			{
				insertHelper(top, tempWord, line, distWords);
				numWords++;
				tempWord.clear();
			}
		}
		line++;
	}

	finishTime = clock();
	totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
	treeHeight = findHeight(top);

	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords<< endl;

	cout << setw(40) << std::left
		 << "Total number of distinct words: " << distWords << endl;

	cout << setw(40) << std::left
		 <<"Total time spent building index: " << totalTime << endl;

	cout << setw(40) << std::left
		 <<"Height of BST is : " << treeHeight << endl;

}


int Tree::findHeight(Node *t) {
	if(t == NULL)
		return 0;
	else{
		int leftHeight = findHeight(t->left);
		int rightHeight = findHeight(t->right);
		int middleHeight = findHeight(t->middle);
		if(leftHeight > rightHeight && leftHeight > middleHeight)
			return(leftHeight+1);
		else if(rightHeight > leftHeight && rightHeight > middleHeight)
			return(rightHeight+1);
		else
			return(middleHeight+1);
	}
}