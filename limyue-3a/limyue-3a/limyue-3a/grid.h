// EECE 3326
// Project 3, a
//
// Tim Liming
// Wing Tung Yuen

/* grid.h Header file for Project 3.
   
   Contains grid class functions:
   
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

class grid
{
public:
	grid(string gfln);
	int getSize() const { return length; }
	void printGrid();
	vector<string> &operator[](int i);
	const vector<string> &operator[](int i) const;
private:
	matrix<string> mtx;
	int length;
	int height;
};

/* grid constructor */
grid::grid(string gfln)
{
	ifstream fin;
	string filename = gfln;
	fin.open(filename.c_str());
	if (! fin)
	{
		throw fileOpenError(gfln);
	}
	cout << "Loading grid..." << endl;

	////
	string x_size;
	string y_size;
	fin >> x_size >> y_size;
	length = atoi(x_size.c_str());
	height = atoi(y_size.c_str());

	mtx = matrix<string>(length, height);
	for (int j = 0; j < length; j++)
	{
		for (int i = 0; i < height; i++)
		{
			fin >> mtx[j][i];
		} // for
	} // for
	////

	fin.close();
	cout << "Grid loaded." << endl;
} // grid constructor

vector<string> &grid::operator[](int i)
{
	if (i < 0 || i >= length)
	{
		throw indexRangeError("ERROR: Invalid row index", i, length);
	}

	return mtx[i];
} // operator

const vector<string> &grid::operator[](int i) const
{
	if (i < 0 || i >= length)
	{
		throw indexRangeError("ERROR: Invalid row index", i, length);
	}

	return mtx[i];
} // const operator

/* sanity check to make sure our grid is properly loaded */
void grid::printGrid()
{
	for (int j = 0; j < mtx.rows(); j++)
	{
		for (int i = 0; i < mtx.cols(); i++)
		{
			cout << mtx[j][i] << ' ';
		} // for

		cout << endl;
	} // for
} // printGrid
