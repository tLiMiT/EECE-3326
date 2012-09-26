// EECE 3326
// Project 1, a
//
// Tim Liming
// Wing Yuen
//
// Header file for Project 1. Contains class code functions.
// Constructor, setCode, getCode, guess and checkCorrect.
// checkIncorrect.

#include "d_random.h"
//#include "d_except.h"
#include <iostream>
#include <vector>

using namespace std;

class code
{
public:
	// Constructor:
	code(int length, int range);
	// code operations:
	void getCode();
	void guess();
	int checkCorrect();
	int checkIncorrect();
	friend ostream &operator<<(ostream &ostr, code &cde);
private:
	int m, n;				// size of length and range
	vector<int> randCode;	// Random Code vector
	vector<int> inputVect;	// Input Code vector
}; // end class

code::code(int length, int range)
// Constructor
	:n(length), m(range)
{}

void code::getCode()
// Generate random code vector of length n
// Output random code vector
{
	randomNumber rand;
	int i;

	for (i = 0; i < n; i++)
	{
		randCode.push_back(rand.random(m));
	} // end for
} // end getCode
	

void code::guess()
// Prompt user for a guess, push each guess into a vector
{
	int i, num;
	inputVect.clear();

	cout << "\nEnter a " << n << " digit guess." << endl;

	for (i = 0; i < n; i++)
	{
		cout << "Digit " << i << ": ";
		cin >> num;

		inputVect.push_back(num);
	} // end for
} // end guess

int code::checkCorrect()
// Compare each value of the vectors with each other
// Output the number of correct digit in correct location
{
	int i, count = 0;

	for(i = 0; i < n; i++)
	{
		if (inputVect[i] == randCode[i])
		{
			count += 1;
		} // end if
	} // end for

	return count;

} // end checkCorrect

int code::checkIncorrect()
{
	int i, u, count = 0;
	vector<bool> used(n);

	for(i = 0; i < n; i++)
	{
		if (randCode[i] == inputVect[i])
		{
			used[i] = true;
		} //end if
		else
		{
			for (u = 0; u < n; u++)
			{
				do {
					if (randCode[i] == inputVect[u])
					{
						used[u] = true;
						count += 1;
					}
				} while (used[u] != true); // end do while
			} // end for
		} // end else
	} // end for

	return count;

} // end checkIncorrect


// overloaded output operator
ostream &operator<<(ostream &ostr, code &cde)
{
	int i;
	ostr << "< ";
	for (i = 0; i < cde.n; i++)
	{
		ostr << cde.randCode[i] << " ";
	} // end for
	ostr << ">";
	return ostr;
}

ostream &operator<<(ostream &ostr, vector<int> &v1)
{
	int i;
	ostr << "< ";
	for (i = 0; i < v1.size(); i++)
	{
		ostr << v1[i] << " ";
	} // end for
	ostr << ">";
	return ostr;
}