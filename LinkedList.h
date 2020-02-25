#ifndef LINK_H
#define LINK_H

#include <iostream>
#include <string>

typedef std::string ItemType;


//using namespace std;
struct Node {
	ItemType value;
	Node* next = nullptr;// initalize the Node struct pointers

};
class LinkedList {
private:
	
	Node* head; //LinkList's pointer to the top of the list
	int m_size; // Amount of nodes in the LinkedList

public:
	// default constructor
	LinkedList() : head(nullptr), m_size(0) {} //new linkedlist will have a null head

	// copy constructor
	LinkedList(const LinkedList& rhs);	// Destroys all the dynamically allocated memory
	// in the list.
	~LinkedList();

	// assignment operator
	const LinkedList& operator=(const LinkedList& rhs);

	// Inserts val at the front of the list
	void insertToFront(const ItemType& val); 

	// Prints the LinkedList
	void printList() const;

	// Sets item to the value at position i in this
	// LinkedList and return true, returns false if 
	// there is no element i
	bool get(int i, ItemType& item) const;
		
	// Reverses the LinkedList
	void reverseList();

	// Prints the LinkedList in reverse order
	void printReverse() const;

	// Appends the values of other onto the end of this
	// LinkedList.
	void append(const LinkedList& other);

	// Exchange the contents of this LinkedList with the other
	// one.
	void swap(LinkedList& other);

	// Returns the number of items in the Linked List.


	int size() const;

};
#endif //end LINK_H

