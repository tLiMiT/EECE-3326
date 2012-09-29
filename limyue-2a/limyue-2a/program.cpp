// EECE 3326
// Project 2, a
//
// Tim Liming
// Wing Tung Yuen

/* The program file for Project 2.
   contains the main function
*/

#include "deck.h"

using namespace std;

int main()
{
	try
	{
		deck dk;

		// prints a deck of cards
		cout << dk;
	}
	catch (rangeError &re)
	{
		cout << re.what() << endl;
	}
}