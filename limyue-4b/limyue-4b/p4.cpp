// EECE 3326
// Project 4, b
//
// Tim Liming
// Wing Tung Yuen


// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <cstdlib>
#include <utility>

using namespace std;

typedef int ValueType;		// The type of the value in a cell
const int Blank = -1;		// Indicates that a cell is blank

const int SquareSize = 3;	//  The number of cells in a small square
							//  (usually 3).  The board has
							//  SquareSize^2 rows and SquareSize^2
							//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

int totalCalls = 0;
int numBoards = 0;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	ValueType getCell(int, int);

	// Added functions
	void printConflicts();
	bool conflicts(int i, int j, int val);
	void setCell(int i, int j, int val);
	void clearCell(int i, int j);
	bool solvedBoard();
	int getCount() { return numRecursions; }
	void clearCount() { numRecursions = 0; }

	bool boardSolve();

private:
	// Added functions
	void updateConflicts(int i, int j, int num, bool val);
	int findBestBlank(int &i, int &j);
	bool solve(int i, int j);

	// The following matrices go from 1 to BoardSize in each
	// dimension.  ie. they are each (BoardSize+1)x(BoardSize+1)
	matrix<ValueType> value;

	matrix<bool> rows;		// matrix of each row conflict
	matrix<bool> cols;		// matrix of each column conflict
	matrix<bool> sqrs;		// matrix of each square conflict

	int numRecursions;
};

board::board(int sqSize)
	: value(BoardSize+1, BoardSize+1),
	rows(BoardSize+1, BoardSize+1),
	cols(BoardSize+1, BoardSize+1),
	sqrs(BoardSize+1, BoardSize+1)
	// Board constructor
{
}

void board::clearCell(int i, int j)
	// clear a cell in the sudoku board
{
	updateConflicts(i, j, value[i][j], 0);
	value[i][j] = 0;
} // clearCell

void board::clear()
	// clear the sudoku board
{
	for (int i = 1; i < value.rows(); i++)
	{
		for (int j = 1; j < value.cols(); j++)
		{
			clearCell(i, j);
		} // for
	} // for
} // clear

void board::initialize(ifstream &fin)
	// Read a Sudoku board from the input file.
{
	char ch;

	clear();	// clear incase there is a board already loaded

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
			{
				if (conflicts(i, j, ch-'0'))
				{
					throw rangeError("conflict on initialization");
				}
				setCell(i, j, ch-'0');	// Convert char to int
			} 
			else if (ch == '.')
			{
				setCell(i, j, 0);		// set cell to 0
			}// if - else if
		} // for
	} // for
} // initialize

int squareNumber(int i, int j)
	// Return the square number of cell i,j (counting from left to right,
	// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

bool board::conflicts(int i, int j, int val)
	// check the row, column, and square for conflicts of a given value
{
	return rows[i][val] || cols[j][val] || sqrs[squareNumber(i, j)][val];
} // conflicts

void board::updateConflicts(int i, int j, int num, bool val)
	// update each of the three possible conflict areas
{
	rows[i][num] = val;
	cols[j][num] = val;
	sqrs[squareNumber(i, j)][num] = val;
} // updateConflicts

ostream &operator<<(ostream &ostr, vector<int> &v)
	// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
	{
		ostr << v[i] << " ";
	}
	ostr << endl;
	return ostr;
}

ValueType board::getCell(int i, int j)
	// Returns the value stored in a cell.  Throws an exception
	// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
	{
		return value[i][j];
	}
	else
	{
		throw rangeError("bad value in getCell");
	}
} // getCell

void board::setCell(int i, int j, int val)
	// set the value of the cell
{
	value[i][j] = val;
	updateConflicts(i, j, val, true);
} // setCell

bool board::isBlank(int i, int j)
	// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
	{
		throw rangeError("bad value in setCell");
	}
	else
	{
		return value[i][j] == 0;
	}
} // isBlank

bool board::solvedBoard()
	// check if the sudoku board is solved
{
	for (int i = 1; i < BoardSize; i++)
	{
		for (int j = 1; j < BoardSize; j++)
		{
			if (isBlank(i,j))
			{
				return false;
			} // if
		} // for
	} // for
	return true;
} // solvedBoard

int board::findBestBlank(int &x, int &y)
	// find a blank spot in the sudoku puzzle
	// returns a pair of ints that are the indices in the board
	// that have the least amount of possible choices
{
	int maxConflicts = MaxValue;
	int temp;

	for (int i = MinValue; i <= MaxValue; i++)
	{
		for (int j = MinValue; j <= MaxValue; j++)
		{
			if (! isBlank(i, j)) { continue; }
			temp = MaxValue;
			for (int x = MinValue; x <= MaxValue; x++)
			{
				temp -= (rows[i][x] == 1); 
				temp -= (cols[j][x] == 1); 
				temp -= (sqrs[squareNumber(i, j)][x] == 1);
			} // for

			if (temp <= maxConflicts)
			{
				maxConflicts = temp;
				x = i;
				y = j;
			} // if
		} // for
	} // for
	return maxConflicts;
} // findBestBlank

bool board::solve(int i, int j)
	// solve the sudoku board using recursion
{
	numRecursions++;	// increase the count every time solve() is called
	
	// initialize indices
	int i1;
	int j1;

	// loop through numbers 1-9
	for (int num = MaxValue; num >= MinValue; num--)
	{
		// if there are no conflicts
		if (! conflicts(i, j, num))
		{
			setCell(i, j, num);		// set cell as that number

			if (solvedBoard()) { return true; }

			findBestBlank(i1, j1);	// find next best position

			if (solve(i1, j1))		// recursion
			{
				return true;
			} // if
			else
			{
				clearCell(i,j);		// clear current cell of number
				continue;
			} // else
		} // if
	} // for
	return false;
} // solve

bool board::boardSolve()
	// handles solving the sudoku board
{
	int i;
	int j;
	findBestBlank(i, j);
	return solve(i, j);
} // boardSolve

void board::print()
	// Prints the current board.
{
	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	}
	cout << "-+";
	cout << endl;

	for (int i = 1; i <= BoardSize; i++)
	{
		if (i == 4 || i == 7)
		{
			cout << "|";
			for (int j = 1; j < SquareSize; j++)
			{
				cout << "---------+";
			}
			cout << "---------|";
			cout << endl;
		} // if

		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j-1) % SquareSize == 0)
			{
				cout << "|";
			}
			if (! isBlank(i, j))
			{
				cout << " " << getCell(i, j) << " ";
			}
			else if (isBlank(i, j))
			{
				cout << "   ";
			}
		} // for
		cout << "|";
		cout << endl;
	} // for

	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	} // for
	cout << "-+";
	cout << endl;
} // print

void board::printConflicts()
	// print each of the conflict matrices side by side
{
	// prints titles spaced correctly
	cout << "Row Conflicts        ";
	cout << "Column Conflicts      ";
	cout << "Square Conflicts" << endl;

	for (int i = 1; i < value.rows(); i++)
	{
		for (int j = 1; j < value.cols(); j++)
		{
			// print a row matrix row
			cout << rows[i][j] << ' ';
		}
		cout << "   ";		// add space between each matrix
		for (int j = 1; j < value.cols(); j++)
		{
			// print a column matrix row
			cout << cols[i][j] << ' ';
		}
		cout << "    ";		// add space between each matrix
		for (int j = 1; j < value.cols(); j++)
		{
			// print a square matrix row
			cout << sqrs[i][j] << ' ';
		}
		cout << endl;		// move to the next line
	} // for
} // printConflicts

// MAIN FUNCTION
int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			numBoards++;

			b1.clearCount();	// clear count for new round

			b1.initialize(fin);
			cout << "\nSolving Board " << numBoards << "..." << endl;
			b1.print();			// print loaded board

			// solve the sudoku board
			if (b1.boardSolve())
			{
				b1.print();		// print the solved board
			} // if

			cout << "Number of calls: " << b1.getCount() << endl;
			totalCalls += b1.getCount();
			
		} // while

		cout << "Average number of calls: " << totalCalls / numBoards << endl;

	} // try
	catch  (rangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
} // main