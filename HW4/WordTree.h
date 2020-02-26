#ifndef  WORDTREES_H
#define WORDTREES_H
#include <iostream>
#include <string>

typedef std::string IType;

struct WordNode {
	IType m_data;
	WordNode* m_left = nullptr;
	WordNode* m_right = nullptr;
	int m_wordcount = 0;
	// You may add additional data members and member functions
	// in WordNode
};

class WordTree {
private:
	WordNode* root;
	void insertion(IType val, WordNode*& current);
	void FreeBTree(WordNode* current);
	int UniqueNodes( WordNode* current, int& n) const;
	int SumAllWords( WordNode* current, int& n) const;
	void copyTreeHelper(WordNode*& copy, WordNode* OP);
	std::ostream& printTreeHelper(WordNode* current, std::ostream& o) const;


public:
	// default constructor
	WordTree();

	// copy constructor
	WordTree(const WordTree& rhs);

	// assignment operator
	const WordTree& operator=(const WordTree& rhs);
	// Inserts v into the WordTree
	void add(IType v);
	// Returns the number of distinct words / nodes
	int distinctWords() const;
	
		// Returns the total number of words inserted, including
		// duplicate values
		int totalWords() const;

	// Prints the LinkedList
	friend std::ostream& operator<<(std::ostream& out, const WordTree&
		rhs);
	// Destroys all the dynamically allocated memory in the
	// tree
	~WordTree();
};

#endif // ! WORDTREES_H
