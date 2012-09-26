// EECE 3326
// Project 1, a
//
// Tim Liming
// Wing Tung Yuen

/* Header file for Project 1. 
   Contains code class functions:
   Constructor, guess, checkCorrect, and checkIncorrect.
   
   Overloaded output operators to output vectors. 
*/

#include "d_random.h"
#include "d_except.h"
#include <iostream>
#include <vector>

using namespace std;

class code
{
public:
	// Constructor:
	code(int length, int range);
	// code operations:
	vector<int> guess();
	int checkCorrect(const vector<int> &guess);
	int checkIncorrect(const vector<int> &guess);
	int getN() { return n; }
	int getM() { return m; }
	friend ostream &operator<<(ostream &ostr, const code &c);
private:
	int n, m;				// size of length and range
	vector<int> randCode;	// Random Code vector
	vector<int> inputVect;	// Input Code vector
	vector<int> key;		// zeros vector
}; // end class

/* Constructor
*/
code::code(int length, int range)
	: n(length), m(range), key(n, 0)
{
	// check inputs
	if (n < 0)
    {
        throw rangeError("Cannot generate code with a negative length.");
    }
    if (m < 0)
    {
        throw rangeError("Cannot generate code with a negative range.");
    }


	// generate a random number vector 'n' digits long with a range of 'm'
	randomNumber rand;
	
	for (int i = 0; i < n; i++)
	{
		randCode.push_back(rand.random(m));
	} // end for
}

/* Prompt user for a guess, push each guess into a vector
*/
vector<int> code::guess()
{
	int i, num;
	inputVect.clear();

	cout << "\nEnter a " << n << " digit guess." << endl;

	for (i = 0; i < n; i++)
	{
		cout << "Digit " << i+1 << ": ";
		cin >> num;

		inputVect.push_back(num);
	} // end for

	return inputVect;

} // end guess

/* Compare each value of the vectors with each other
   Output the number of correct digit in correct location 
*/
int code::checkCorrect(const vector<int> &guess)
{
	// check inputs
	if (guess.size() < n)
    {
        throw rangeError("ERROR: Was expecting a vector of length n");
    }


	// check for correct digits
	int correct = 0;

	for(int i = 0; i < guess.size(); i++)
	{
		if (guess[i] == randCode[i])
		{
			correct += 1;
		} // end if
	} // end for

	return correct;

} // end checkCorrect

/* Compare each value of the vectors with each other
   Output the number of correct digits in the incorrect location
*/
int code::checkIncorrect(const vector<int> &guess)
{
	// check inputs
	if (guess.size() < n)
    {
        throw rangeError("ERROR: Was expecting a vector of length n");
    }


	// initialize variables
	int incorrect = 0, duplicate = 0, keySum = 0;
	
	// create a copy of key vect that we can modify
	vector<int> localKey = key; 


	// for loops check for duplicates in the random code
	for (int i = 0; i < guess.size(); i++)
	{
		for (int u = i+1; u < guess.size(); u++)
		{
			if (randCode[i] == randCode[u])
			{
				duplicate++; // count if there are duplicates
			} // end if
		} // end for
	} // end for


	/* if there is more than one duplicate we must subtract to account
	   for counting the first number twice */
	if (duplicate > 1)
	{
		duplicate--;
	} // end if


	// for loops check the guess against the random code
	for (int i = 0; i < guess.size(); i++)
	{
		for (int u = 0; u < guess.size(); u++)
		{
			if (randCode[i] == guess[i])
			{
				// do nothing because that is the correct number
				// (do not count)
			}
			else if (randCode[i] == guess[u])
			{
				// if the correct number is within the guess, increment 
				localKey[i]++;
			}
		} // end for
	} // end for


	/* to make sure we count each digit only once, we normalize the localKey
	     vector and then add each element to get the total incorrect digits */
	for (int i = 0; i < localKey.size(); i++)
	{
		if (localKey[i] > 1)
		{
			localKey[i] = 1;
		} // end if

		keySum += localKey[i];
	} // end for


	/* if there are no correct digits in the wrong location, keySum will 
	   return zero and if there are still duplicates we will get a negative
	   number. If this happens, we set duplicates to zero */
	if (keySum == 0 && duplicate > 0)
	{
		duplicate = 0;
	} // end if


	/* to get the number of correct digits in the incorrect location, we
	   subtract the duplicates from the keySum */
	incorrect = keySum - duplicate;

	return incorrect;

} // end checkIncorrect


/* Overload the '<<' operator for a vector of type 'T'
*/
template <typename T>
ostream &operator<<(ostream &ostr, const vector<T> &v1)
{
	ostr << "< ";

	for (int i = 0; i < v1.size(); i++)
	{
		ostr << v1[i] << " ";
	} // end for

	ostr << ">";

	return ostr;
}

/* Overload the '<<' operator for code objects
*/
ostream &operator<<(ostream &ostr, const code &c)
{
	ostr << c.randCode;
	return ostr;
}

