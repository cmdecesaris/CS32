#ifndef BEFORE_H
#define BEFORE_H
#include "globals.h"

class Before
{
public:
	Before(int nRows, int nCols);
	bool keepTrack(int r, int c);
	void printWhatWasBefore() const;

private:
	int m_col, m_row; //private col and row vars to be reference by this class
	int beforeGrid[MAXROWS][MAXCOLS]; //2D matrix stores the values of keeptrack, displayed by printWhatWasBefore()
};
#endif //for BEFORE_H