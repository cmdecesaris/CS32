#include "WordTree.h"
#include <iostream>
#include <string>
#include<cassert>
using namespace std;
int main() {

	WordTree tree;
	tree.add("ra");
	tree.add("ra");
	tree.add("shaw");
	tree.add("zane");
	tree.add("chris");
	tree.add("zya");
	WordTree tree2 = tree;
	WordTree tree3;
	tree3.add("rats");
	tree3.add("cats");
	cout << tree3 << endl;
	tree3 = tree2;
	WordTree k;

	k.add("Kim");
	k.add("Kanye");
	k.add("Kanye");
	k.add("Kanye");
	assert(k.distinctWords() == 2);
	assert(k.totalWords() == 4);

	WordTree w;

	w.add("Harry");
	w.add("Niall");
	w.add("Niall");
	w.add("Liam");
	w.add("Louis");
	w.add("Harry");
	w.add("Niall");
	w.add("Zayn");
	w.add("");
	w.add("");

	cout << w;
	WordTree  j = w;
	cout << endl << j;
	WordTree a(w);
	cout << endl << a;
	cout << a.totalWords() << endl;
	cout << w.totalWords() << endl;
	cout << j.totalWords() << endl;
	cout << a.distinctWords() << endl;
	cout << w.distinctWords() << endl;
	cout << j.distinctWords() << endl;
}