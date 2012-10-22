// EECE 3326
// Project 3, b
//
// Tim Liming
// Wing Tung Yuen

/* The program file for Project 3.
   contains the findMatches function 
   contains the testSearch function
   contains the main function
*/

#include <iostream>
#include <time.h>
#include "grid.h"
#include "dictionary.h"

using namespace std;

int wordCount = 0;

/* adjacentCheck function
   adjacentCheck checks for words around a letter in all directions
*/
void adjacentCheck(const dictionary &d,		// dictionary object
				   const grid &g,			// grid object
				   int row,					// row index
				   int col,					// column index
				   const int dX,			// change in x-direction
				   const int dY,			// change in y-direction
				   const int minWL = 5)		// minimum word length
{
	// make sure we will actually move from starting point
	if (dX == 0 && dY == 0) { return; }

	// set grid index
	int x = row;
	int y = col;
	string currWord = g[x][y];

	// find words that are longer than the minimum size
	while (currWord.length() <= g.getSize())
	{
		if (currWord.length() >= minWL)
		{
			// use binarySearch to check if word is in the dictionary
			if (d.binarySearch(0, d.getSize()-1, currWord))
			{
				cout << currWord << endl;
				wordCount++;
			} // if
		} // if

		// handle wrap-around cases
		x = (x + dX + g.getSize()) % g.getSize();
		y = (y + dY + g.getSize()) % g.getSize();
		currWord = currWord + g[x][y];
	} // while
} // adjacentCheck

/* findMatches function
   finds any words in the grid that match the dictionary
*/
void findMatches(const dictionary &dict, const grid &grd)
{
	time_t start, end;
	double diff;

	cout << "Searching...\n" << endl;
	time (&start);

	for (int j = 0; j < grd.getSize(); j++)
	{
		for (int i = 0; i < grd.getSize(); i++)
		{
			// check N
			adjacentCheck(dict, grd, j, i, -1, 0);
			// check NE
			adjacentCheck(dict, grd, j, i, -1, 1);
			// check E
			adjacentCheck(dict, grd, j, i, 0, 1);
			// check SE
			adjacentCheck(dict, grd, j, i, 1, 1);
			// check S
			adjacentCheck(dict, grd, j, i, 1, 0);
			// check SW
			adjacentCheck(dict, grd, j, i, 1, -1);
			// check W
			adjacentCheck(dict, grd, j, i, 0, -1);
			// check NW
			adjacentCheck(dict, grd, j, i, -1, -1);
		} // for
	} // for

	cout << '\n' << wordCount << " words found." << endl;

	time (&end);
	diff = difftime(end, start);
	printf("Runtime: %.2f minutes.\n", diff/60);
} // findMatches

/* testSearch function
   gets a dictionary and grid and finds matches
*/
void testSearch()
{
	
	// get dictionary filename
	/*
	string dictFN;
	cout << "Input the dictionary filename: ";
	cin >> dictFN;
	dictionary dict(dictFN);
	*/
	dictionary dict("dictionary");
	dict.sort();

	// get grid filename
	string gridFN;
	cout << "Input the grid filename: ";
	cin >> gridFN;
	grid grd(gridFN);

	// find all matching words in the grid
	findMatches(dict, grd);
} // testSearch

int main()
{
	try
	{
		// search the given grid for given words
		testSearch();
	}
	catch (fileOpenError &foe)
	{
		cout << foe.what() << endl;
	}
	catch (indexRangeError &ire)
	{
		cout << ire.what() << endl;
	}
} // main