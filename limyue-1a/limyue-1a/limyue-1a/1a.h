// EECE 3326
// Project 1, a
//
// Tim Liming
// Wing Yuen
//
// Header file for Project 1. Contains class code functions.
// Constructor, setCode, getCode, guess and checkCorrect.

#include "d_random.h"
#include <iostream>
#include <vector>

using namespace std;

class code
{
public:
	// Constructor:
	code(int length = 5, int range = 10);
	// code operations:
	void setCode();
	void getCode();
	void guess();
	int checkCorrect();
private:
	int m, n;				// size of length and range
	vector<int> randCode;	// Random Code vector
	vector<int> inputVect;	// Input Code vector
}; // end class

code::code(int length, int range)
// Constructor
	:n(length), m(range)
{}

void code::setCode()
// Set code length and digit range
{
	cout << "Enter code length (n) and digit range (m)" << endl;
	cout << "n: ";
	cin >> n;
	cout << "m: ";
	cin >> m;
} // end setCode

void code::getCode()
// Generate random code vector of length n
// Output random code vector
{
	randomNumber rand;
	int i;

	for (i = 0; i < n; i++)
	{
		randCode.push_back(rand.random(m));

		cout << randCode[i];
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
