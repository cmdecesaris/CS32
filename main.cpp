#include "LinkedList.h"
#include <iostream>
#include <cassert>
using namespace std;
int main() {
	LinkedList e1;
	e1.insertToFront("Sam");
	e1.insertToFront("Carla");
	e1.insertToFront("Cliff");
	e1.insertToFront("Norm");
	e1.reverseList(); // reverses the contents of e1
	string s;
	assert(e1.size() == 4 && e1.get(0, s) && s == "Sam");
	LinkedList v;
	v.insertToFront("ames");
	v.insertToFront("brant");
	v.printList();
	e1.printList();
	v = e1; //call assign operator
	v.printReverse();
	
}