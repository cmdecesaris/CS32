#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include<string>
#include<cassert>
using namespace std;

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in
/* loadWOrds places string in dictfle into the arr dict,
returns he number of words read into dict, this number is not to be
larger than maxDictwords (due to this being the arr limit)
*/

void swapChar(char* first, char* second) { //uses pointers to swap two characters
	char temp = *first;
	*first = *second;
	*second = temp;
}

string alphaSort(string str, int length, int i, int j) { //returns a copy  and does not change actual string
	if (length == 1) {
		return str;
	}
	if (length == 2) { //if we have a two letter word we don't want to accidentally return without alpha because length-2 will equal the starting i=0
		if (str[0] < str[1]) {
			return str;
		}
		else {
			swap(str[0], str[1]);
			return str;
		}

	}


	if (i == length - 2) { //base case concludes i has "iterated" through each char and compared with j, we now can return the string
		return str;
	}

	if (j == length - 1) { //case to check j boundary, size-1 is end of the word
		if (str[i] > str[length - 1]) { //if we are at the end of the word, somtimes characters of the same value will get skippd over and end up last 
			swap(str[i], str[j]); //this ensures that there are no skips and swaps char i with char j if an inconsistency is found

		}
		i++; //if j is at the end, we move i along the string
		j = i + 1; //set j to the pos after i
		if (str[i] > str[j]) //if i is alpha less than j
			swap(str[i], str[j]); //swap
		j++;
		return	alphaSort(str, length, i, j);  //move j along to compare the next character
	}
	else {
		if (j < length - 1) //j is not yet at the end of th string
		{
			if (str[j] < str[i]) //check if j is alpha greater than i char
				swap(str[i], str[j]);//if so flop them
			j++; //j++ in the return did not go through, i think it had to do with j being incrimented aftr the call so it caused run time error
			return alphaSort(str, length, i, j); //continue in th
		}
	}
	return str;

}




int loadWords(istream& dictfile, string dict[]) { //check that if we have reached 3000
	string temp;  //storage
	int count = 0;
	if (dictfile.eof()) { //end of dict base case
		return 0;
	}
	if (!dictfile.eof()) { //if not end of dict
		dictfile >> temp; //grap currnt line
		//cout << temp;
		int n = loadWords(dictfile, dict); //check size
		if (n == MAXDICTWORDS) { //check size
			return MAXDICTWORDS;
		}
		dict[n] = temp;//if size is fine, store that index in dict
		return n + 1; //incr n to represent the increased rturnd size
		//end function


	//return loadWords(dictfile, dict + 1) + 1; //end function we've exceeded our limit, WRITE END FUNCTION
	}

	return 0;
}









/*
recBlends bsaically places all combinations of word found
in dict unto results arr, so for rat, it would place
rat, art, and tar in results, maxresults is the limit on this
*/


bool dupes(string word, int size, int i, const string results[]) {
	if (size == i) { //base case, i will be incrimnted
		return false;
	}
	else {
		if (results[i] == word) { //test if there is a match
			return true;
		}
		else {//no match
			i++;
			return dupes(word, size, i, results);//no need to results +1, because i is our index
		}
	}
}

int blender(string word, const string dict[], int size, string
	results[], int n) {


	if (size == 0) { //base case, this is th end of dict

		return 0;
	}


	if (word.length() != dict[0].length()) { //if not same length, they can't be anagrams
		size--;
		return blender(word, dict + 1, size, results, n); //move along dict
		//cout << n << endl;


	}
	//cout << recCheck(0, results) << endl;
	if (word.length() == dict[0].length()) { //same length check
		if (alphaSort(word, word.length(), 0, 1) == alphaSort(dict[0], dict[0].length(), 0, 1)) {//do we have identical strings aftr apha sort
			//if (n == MAXRESULTS) {
			if (n == MAXRESULTS) { //size check, returns MAXRESULTS and 
				return MAXRESULTS;
			}
			else {
				if (dupes(dict[0], n, 0, results - n) == false) {	//sends dict[0] word to be checked with every current result, if we find that word there, we dont add it																 //int k;
					//results-n indexs th results array back to its original state
					results[0] = dict[0]; //if idental after sort, store in results , in this case we add it
					size--;
					n++;
					return blender(word, dict + 1, size, results + 1, n) + 1; //if added to results, incremint results on further
				}
				//else {
				//	return blender(word, dict + 1, size, results, n); //other wise move along in dict
				//}
			}
			//cout << n << endl;
			//move along in dict and results
//inc(results, 0, n, word);



		}
		else {
			size--;
			return blender(word, dict + 1, size, results, n); //move along in dict
			//cout << n << endl;

		}
	}
	return 0; //important so all path's return a value


}


int recBlends(string word, const string dict[], int size, string
	results[]) {

	int x = blender(word, dict, size, results, 0); //Blender does all the heavy lifting, it was needed to keep a count on results
	return x;
	//	int x;
	//	int n;
	//	x = theCount(x, 0, results);
	//	cout << x << endl;
	//	if (size == 0) {
	//
	//		return 0;
	//	}
	//
	//	if (word.length() != dict[0].length()) {
	//		size--;
	//		n = (recCount(recBlends(word, dict + 1, size, results))); //move along
	//		//cout << n << endl;
	//		return n; //move along
	//
	//	}
	//	//cout << recCheck(0, results) << endl;
	//	if (word.length() == dict[0].length()) {
	//		if (alphaSort(word, word.length(), 0, 1) == alphaSort(dict[0], dict[0].length(), 0, 1)) {//do we have identical strings aftr apha sort
	//			//if (n == MAXRESULTS) {
	//																						 //int k;
	//			
	//			
	//			results[0] = dict[0]; //if idental after sort, store in results
	//			size--;
	//
	//			n = (recCount(recBlends(word, dict + 1, size, results + 1)) + 1);
	//			//cout << n << endl;
	//			//move along in dict and results
	////inc(results, 0, n, word);
	//			return n;
	//
	//
	//		}
	//		else {
	//			size--;
	//			n = (recCount(recBlends(word, dict + 1, size, results)));
	//			//cout << n << endl;
	//			return n;
	//		}
	//	}
	//	return 0;
}



//if empty return the 
//function should transverse through the word and compare to all other words
//function should transverse through the word and compare to all other words
//in this case we can look at words of same length, permutate through each
//the key is to find a matching letter for every letter in the input
//if we don't find any matches, store word in result stand alone
//lettercount! (as a permutation) will always be the max number of possible permutations, single letter is also a base case
//start by checking if length of word equals the length of current dict word, (if it move the arr to the  next word, with dict+1)
//if the sizes match, normally i'd use nested for loop, in this case maybe a helper function is in store
//helper function would be a bool and transverse through  all letters in both strings
//if we find an anagram it returns true and the dictword is stored in results else false


/*displays the size number and strings from results in any order*/


void showResults(const string results[], int size) {


	if (size == 0) {
		return;
	}
	cerr << results[0] << endl;
	size--;   
	return showResults(results + 1, size);

}






int main()
{


	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile;         // file containing the list of words
	int nwords;                // number of words read from dictionary
	string word;


	dictfile.open("words.txt");
	if (!dictfile) {
		cout << "File not found!" << endl;
		return (1);
	}
	//cout<<alphaSort("however", 7, 0, 1);

	nwords = loadWords(dictfile, dict);
	cout << nwords<<endl;
	cout << "Please enter a string for an anagram: ";
	cin >> word;
	//for (int i = 0; i < nwords; i++) {
	//	cout << dict[i]+ "--" <<endl;
	//}
	int numMatches = recBlends(word, dict, nwords, results);
	cout << numMatches << endl;
	if (!numMatches)
		cout << "No matches found" << endl;
	else
		showResults(results, numMatches);
}