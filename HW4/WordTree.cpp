#include "WordTree.h"
#include <iostream>
#include <string>

using namespace std;
//impementation 
WordTree::WordTree() : root(nullptr) { }

// copy constructor
WordTree::WordTree(const WordTree& rhs) : root(nullptr){
	//root = nullptr;
	if (rhs.root == nullptr) {
		root = nullptr; // copy also null
		return; //done
	}
	else {
		copyTreeHelper(root, rhs.root); //recursively copies tree from rhs root
	}
}

// assignment operator
const WordTree& WordTree::operator=(const WordTree& rhs) { 
	if (&rhs == this) {
		return *this;
	}
	if (rhs.root == nullptr) {
		root = nullptr;
		//return *this;
	}
	else {
		copyTreeHelper(root, rhs.root);
	}
	
	return *this; 
}

// Inserts v into the WordTree
void WordTree::add(IType v) { //O(log2(n)
	
	insertion(v, root);
	
}
// Returns the number of distinct words / nodes
int WordTree::distinctWords() const { 
	int unique = 0;
	UniqueNodes(root, unique);
	


	return unique;

}

// Returns the total number of words inserted, including
// duplicate values
int WordTree::totalWords() const { 
	int total = 0;

	SumAllWords(root, total);
	return total;
}//transverse and add

// Destroys all the dynamically allocated memory in the
// tree
WordTree::~WordTree() { //O(n)

	FreeBTree(root);
}

// Prints the LinkedList
ostream& operator<<(ostream& out, const WordTree& rhs) { //needs recursive version
	WordNode* current = rhs.root;
	
	 rhs.printTreeHelper(current, out);
//	bool leftSide = false;
	//while (current) {
	//	if (!leftSide) {
	//		while (current->m_left) {
	//			//current = current->m_left;
	//		}
	//	}
	//	out << current->m_data << " " << current->m_wordcount << endl;
	//	leftSide = true;
	//	if (current->m_right) {
	//		leftSide = false;
	//		current = current->m_right;
	//	}
	//	else if(current ->)
	//}

	////pass in current 
	////stack<WordNode*>  mstack;
	////if (current == nullptr) { return; }
	//while (current != nullptr || !mstack.empty()) { //done
	//	if (current != nullptr) {
	//		mstack.push(current);
	//		current = current->m_left;
	//	}
	//	else {

	//		current = mstack.top();
	//		mstack.pop();
	//		out << current->m_data << " " << current->m_wordcount<< endl;
	//		current = current->m_right;
	//	}


	
  return out;

}

//Private function implementation
void WordTree::insertion(IType val, WordNode*& current) {
	if (current == nullptr) { //works if first or if we have found a valid empty location
		WordNode* newNode = new WordNode; //found the proper node insertion location
		newNode->m_data = val;
		newNode->m_wordcount++; 

		current = newNode; 
	}
	else { //not first or leaf
		if (val == current->m_data) {//duplicate name found
			current->m_wordcount++; //increase wordcount then return
			return;
		}
		if (val < current->m_data) { //if val is  less move on left
			insertion(val, current->m_left);
		}
		else {
			insertion(val, current->m_right); // otherwise move on right
		}

	}
	return;
}

void WordTree::FreeBTree(WordNode* current) {
	if (current == nullptr) { return; }//nothing to release or at a leaf node
	FreeBTree(current->m_left); //recursive call left
	FreeBTree(current->m_right); //recursive  call right
	delete current; //deletes post order (which makes sense)
}
int WordTree::UniqueNodes(WordNode* current, int& n) const {

	if (current == nullptr) { return n; }
	UniqueNodes(current->m_left, n);
	if (current->m_wordcount > 0) { //only counts if there is a word
		n++;
		//return n;
	}
	UniqueNodes(current->m_right, n);
	return n;
}
int WordTree::SumAllWords(WordNode* current, int& n) const {

	if (current == nullptr) { return n; } //basecase 
	SumAllWords(current->m_left, n);
	if (current->m_wordcount > 0) {
		n = n + current->m_wordcount;
		//return n;
	}
	SumAllWords(current->m_right, n);
	return n;
}

void WordTree::copyTreeHelper(WordNode*& copy, WordNode* OP) {
	if (OP == nullptr) { //ensure that we don't have a null root, and ensure we return when OP is at null (don't want to access m_left if it is null!!!)
		copy = nullptr; //if pointing at null make this null
		return;
	}

	copy = new WordNode; //set pointer new node

	copy->m_data = OP->m_data; 
	copy->m_wordcount = OP->m_wordcount;
	copyTreeHelper(copy->m_right, OP->m_right); //go right, will basically call this recursively
	copyTreeHelper(copy->m_left, OP->m_left); //go left

	//return;

}
ostream& WordTree::printTreeHelper(WordNode* current, ostream& o) const {
	if (current == nullptr) { //similar to copy tree, if we are at a null return the stream, do not access
		return o;
	}

		 printTreeHelper(current->m_left, o);
		 o << current->m_data << " " << current->m_wordcount << endl; //adds data and word cout continuously to the stream processing the nodes in order
		 printTreeHelper(current->m_right, o);

	

		 return o;
	
}
