#include "Before.h"
#include "globals.h"
#include <iostream>
using namespace std;
//before implementation
Before::Before(int nRows, int nCols) {  //before constructor goes here
	m_col = nCols;
	m_row = nRows;


	for (int i = 0; i < nRows; i++) { //might be redundant here
		for (int j = 0; j < nCols; j++) {
			beforeGrid[i][j] = 0; //build the new grid, set values to null
		}
	}
	
}

bool Before::keepTrack(int r, int c) {

	beforeGrid[r][c]++; //increment so player arrival to keep track 
	return true;    //value is to be set in the beforeGrid[][], since every val is 0 we can add 1 to that spot value everytime th player is at those coordinates 
					//use of character to increment values from A-Z, ++ should increment via char string
}

void Before::printWhatWasBefore() const { 

	char charGrid[MAXROWS][MAXCOLS]; // char grid that will be recreated to coresspond to the numerical vals in beforeGrid
	for (int i = 1; i <= m_row; i++) 
		for (int j = 1; j <= m_col; j++)
		{
			if (beforeGrid[i][j] == 0) //everything at first should be set to zero in beforeGrid
				charGrid[i - 1][j - 1] = '.';
			else if (beforeGrid[i - 1][j - 1] >= 26) //beforeGrid vals over 25 are set to 
				charGrid[i - 1][j - 1] = 89; //89 is the char code for Z
			else
				charGrid[i - 1][j - 1] = 64 + beforeGrid[i][j]; // char codes are A=65, B=66, +64 ensures that any non zero value under 26 will be incremented to its proper char
		}

	clearScreen(); //without clear screen, the  charGrid will appear below the game in a messy fashion

	for (int i = 1; i <= m_row; i++) //prints out new char matrix that is "a translated" beforeGrid
	{
		for (int j = 1; j <= m_col; j++)
			cout << charGrid[i - 1][j - 1];
		cout << endl;
	}
	cout << '\n'; //space before press enter to contiune

}
