#include "LinkedList.h"
#include <iostream>
#include<string>  //isn't needed but for safty 

using namespace std;

//LinkedList::LinkedList() : m_size(0) {//defualt constructor, note: initalization list already sets the headpointer which points to a node to null in header
//}  


LinkedList::LinkedList(const LinkedList& rhs) : head(nullptr) { 
	m_size = rhs.m_size; // copy the size over
	Node* m = rhs.head;  
	if (m != nullptr) { //empty list set up, specifcally done to not loose head pointer
		head = new Node;
		head->value = m->value; 
		m = m->next; 
	}
	Node* n = head; // node will be used for accessing next and linking the prevous node to the new one

	while (m != nullptr) {
		Node* p = new Node;
		p->value = m->value;
		if (n -> next == nullptr) { //
			n->next = p;
			n = n->next;
		}
		
		m = m->next;
	}

}
LinkedList::~LinkedList(){ //destructor
	Node* m = head;
	while (m != nullptr) {
		Node* toDelete = m;  //use toDelete pointer to point to what will be deleted, move m along the list then terminate
		m = m->next;
		delete toDelete;
	}

}

const LinkedList& LinkedList::operator=(const LinkedList& rhs){ //assignment operator, 
	
	//make sure we do NOT assignoperator to assugn a var to itself 
	if (this == &rhs) { 
		return *this;

	}
	int size = rhs.size();
	LinkedList LL;
	ItemType val;
	for (int i = 0; i < size; i++) {
		rhs.get(i, val);
		LL.insertToFront(val);
	}
	LL.reverseList();
	this->swap(LL);
	this->m_size = size;
	return *this;

}



	/*Sequence& Sequence::operator= (const Sequence& value) //Assignment Constructor
{
	if (this == &value)
		return *this;
	int size = value.size();
	Sequence temp;
	ItemType testValue;
	for (int k = 0; k < size; k++)
	{
		value.get(k, testValue);
		temp.insert(k, testValue);
	}
	swap(temp);
	this->m_size = size;
	return *this;
}*/

	


void LinkedList::insertToFront(const ItemType& val) {
	 
		 
		
		Node* p = new Node; //make new node assign to pointer p
		p->value = val; //set value of new node to that specified in parameters
		p->next = head; //set new nodes next ptr to head 
		head = p;
		m_size++;

	
}

void LinkedList::printList() const {
	Node* m = head;
	while (m != nullptr) {
		cout << m->value << " ";
			
		m = m->next; 
	}
	cout << endl;
}

bool LinkedList::get(int i, ItemType& item) const {
	if (i < 0 || i > m_size) {
		return false;
	}
	else {
		Node* m;
		m = head;
		int count = 0;
		while (count != i) {
			m = m->next;
			count++;
		}
		item = m->value;
		return true;
	}
}

void LinkedList::reverseList() {
	Node* c = head; //where we at currently
	Node* prev = nullptr; //what came before current
	Node* n = head;  //what follows
	while (c != nullptr) { //run this loop until we end up with a next
		    n = n->next;
			c->next = prev; //flip the current node's next ptr to point to the node before it

			
			//otherwise
			prev = c; //move prev to current
			c = n; // move current to next node
		//	n = n->next; // move n along, eventually this will reach the nullptr of the orginal list

	}
	//n should equal null here, we set n equal to head 
	head = prev; //take our head and set it to the prev pointer which now should be the previous last
	

}

void LinkedList::printReverse() const { //this takes the code from reverse list but because it is const and we just want to print
	LinkedList cp;
	cp.m_size = m_size; // copy the size over
	Node* m = head;
	if (cp.head == nullptr) { //empty list set up, specifcally done to not loose head pointer
		cp.head = new Node;
		cp.head->value = m->value;
		m = m->next;
	}
	Node* n = cp.head; // node will be used for accessing next and linking the prevous node to the new one

	while (m != nullptr) {
		Node* p = new Node;
		p->value = m->value;
		if (n->next == nullptr) { //
			n->next = p;
			n = n->next;
		}

		m = m->next;
			   		 	  
	}
	cp.reverseList();
	cp.printList();
}
void LinkedList::append(const LinkedList& other) {// change!! // 
  
	Node* o = head; //points to the head of the list we are appending to
	Node* a = other.head; //points to the head of the list we are going to add, belongs to OTHER
	m_size = m_size + other.size(); 

	while (o->next != nullptr) { //we want to stop at the last element, not its next ptr
		o = o->next;
	} 
	//now o should be at the bottom of the append to list
	while (a != nullptr) {
		Node* p = new Node;
		p->value = a->value; // copy over the value
		o->next = p; 
		o = p;
		a = a->next;
		
	}
	
	
	
}

void LinkedList::swap(LinkedList& other) { //   head ptrs and size values
	Node* headswap = other.head; //pointer to store other's head address
	other.head = head; //set other.head to the this's head
	head = headswap; //take the this head and make this to the other head's address

	int sizeswap = other.m_size; //same algorithm as above for swaping the sizes of lists,
	other.m_size = m_size;
	m_size = sizeswap;

}

int LinkedList::size() const { //returns size of list
	
	return m_size; 
}

