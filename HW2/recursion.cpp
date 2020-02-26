#include<string>
#include<iostream>
using namespace std;


// Returns the product of two non-negative integers, m and n,
// using only repeated addition.
int prod(unsigned int m, unsigned int n)
{
	if (n == 0|| m == 0) {
		return 0;
	}
	if (n==1 ) {
		return m;
	}

	
	m+=prod(m, n - 1);
}
// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
// numberOfDigits(18838, 8) => 3
// numberOfDigits(55555, 3) => 0
// numberOfDigits(0, 0) => 0 or 1 (either if fine)
//
int numberOfDigits(int num, int digit)
{
	if (num == 0) { //eventually we will reach here if there are no found digits,
		return 0;
	}
	if (num % 10 == digit) { //checks last digit of num
		return 1 + numberOfDigits(num / 10, digit); //adds 1 to # digits and moves through num (starting from the back)

	}
	else {
		numberOfDigits(num / 10, digit); //will keep moving through the digits in num

	}

	//count = 0;

}
// Returns a string where the same characters next each other in
// string n are separated by "22"
//
// Pseudocode Example:
// doubleDouble("goodbye") => "go22odbye"
// doubleDouble("yyuu") => "y22yu22u"
// doubleDouble("aaaa") => "a22a22a22a"
//if strings can work as char arr, this could search for next one in the string
//otherwise, we can use the actual char code to determine if there is a duplicate
//consider using substring and other string type functions if allowed ofc
//
string doubleDouble(string n)
{
	if (n.length() == 1 || n.length()==0) {//one char or no char, 
		return n;
	}
	if (n[0] == n[1]) {
		return  n.substr(0,1)+"22" + doubleDouble(n.substr(1)); //adds 22 between the double letters
	}
	else {
		return n.substr(0, 1)+doubleDouble(n.substr(1)); //if no double, keep moving 
	}
}

// str contains a single pair of curly brackets, return a new
// string made of only the curly brackets and whatever those
// curly brackets contain
//
// Pseudocode Example:
// curlyFries("abc{ghj}789") => "{ghj}"
// curlyFries("{x}7") => "{x}"
// curlyFries("4agh{y}") => "{y}"
// curlyFries("4agh{}") => "{}"
//
string curlyFries(string str) //gets very mad if there are no instances of a  complete set of brackets
{
	//check each side of the string when we find the {{}}}}} we look on other side and in end return str
	
	if (str[0] == '{') { //if we found { marking the begining of our string to keep
		if (str[str.size() - 1] == '}') { //look and see if the end is a }
			return str; //end case, if there is a } found at last

		}
		else {
			return curlyFries(str.substr(0, str.size() -1)); //move from the back, search for that }
		}
	}
	else {
		return curlyFries(str.substr(1)); //move forward in string, we do ot care about characters before the {
	}
  
	
}
// Return true if the total of any combination of elements in
// the array a equals the value of the target.
//
// Pseudocode Example:
// addEmUp([2, 4, 8], 3, 10) => true
// addEmUp([2, 4, 8], 3, 6) => true
// addEmUp([2, 4, 8], 3, 11) => false
// addEmUp([2, 4, 8], 3, 0) => true
// addEmUp([], 0, 0) => true
//
bool addEmUp(const int a[], int size, int target)
{

	if (target == 0) { //in this case, the target value is obtainable
		return true;
	}
	if (size == 0) { //called when we have moved through the arra
		return false;
	}
	else { //int arr[4] = {3,2,1,7};
		//if(!addEmUp(a + 1, size - 1, target - a[0])) //Changed to the below code due to this logic not 
		//	addEmUp(a + 1, size - 1, target);  //working in the g++ compiler strangely enough, the OR statement did not cause a logic discrepehcny and worked fine in the g++  
		return addEmUp(a + 1, size - 1, target - a[0]) || addEmUp(a + 1, size - 1, target); //

	}
}
	
	
bool canWeFinish(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	maze[sr][sc] = '3';//mark each new spot
	if (sr == er && sc == ec) { //in general, the function checks if we can move in any of the directions and if so will call itself in that new spot, marking each time
		return true; //maze has been solved 
	}
	if (maze[sr - 1][sc] == '.' && canWeFinish(maze, nRows, nCols, sr - 1, sc, er, ec)) { //down
		return true;
	}
	if (maze[sr + 1][sc] == '.'&& canWeFinish(maze, nRows, nCols, sr + 1, sc, er, ec)) { //up
		return true;
	}
	if (maze[sr][sc - 1] == '.' && canWeFinish(maze, nRows, nCols, sr, sc - 1, er, ec)) {//left
		return true;
	}	
	if (maze[sr][sc + 1] == '.'&& canWeFinish(maze, nRows, nCols, sr, sc + 1, er, ec)) { //right
		return true;
	}
	return false; //if false is ever called, it is not solveable
	
}













int main() {
//  cerr << prod(4, 5) << endl;
//	cerr << prod(0, 5) << endl;
//	cerr << prod(0, 0) << endl;
//	cerr << prod(3, 0) << endl;
//
//	cerr << numberOfDigits(12211, 2);
//	cerr << numberOfDigits(12211, 0) << endl;
//
//	cerr << doubleDouble("waaa") << endl;
//	cerr << doubleDouble("yyuu") << endl;
//	cerr << doubleDouble("goodbye") << endl;
//	cerr << doubleDouble("uu") << endl;
//	cerr << doubleDouble("") << endl;
//	cerr << doubleDouble("ytho") << endl;
//	cerr << doubleDouble("y") << endl;
//
//	cerr << curlyFries("44{dd}dfdsfsdf") << endl;
//	cerr << curlyFries("44{}dfdsfsdf") << endl;
//	cerr << curlyFries("44{dddfdsfsdf}") << endl;
//	cerr << curlyFries("{44dd}dfdsfsdf") << endl;
//	cerr << curlyFries("{44dddfdsfsdf}") << endl;
//	cerr << curlyFries("44{dddfdsf}sdf") << endl;
//
//	cerr << curlyFries("44ddfd{sf}sdf") << endl;
//
//
//	string maze[10] = {
// "XXXXXXXXXX",
// "X.......@X",
// "XX@X@.XXXX",
// "X..X.....X",
// "X..X...@.X",
// "X....XXX.X",
// "X@X....XXX",
// "X..XX.XX.X",
// "X...X....X",
// "XXXXXXXXXX"
//};
//
//	if (canWeFinish(maze, 10, 10, 6, 4, 1, 1))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//
//
//
//
//
//
//	int arr[] = { 3,2,1,7 }; //MORE TEST CASES YO
//
//	if (addEmUp(arr, 4, 14)) {
//		cout <<endl<< "Add Em Up True" << endl;
//	}
//	else {
//		cout << endl<<"Add Em Up False" << endl;
//	}

}

