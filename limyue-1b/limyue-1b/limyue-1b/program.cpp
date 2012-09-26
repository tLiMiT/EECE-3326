// EECE 3326
// Project 1, b
//
// Tim Liming
// Wing Tung Yuen

/* The program file for Project 1.
   contains the main function
*/

#include "1b.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	try
	{
		// initialize the length and range variables
		int n, m;

		// prompt the user to enter integers for the code length and digit range
		cout << "Enter code length (n) and digit range (m)" << endl;
		cout << "n: ";
		cin >> n;
		cout << "m: ";
		cin >> m;
	
		// initialize a code object using the input length and range
		mastermind mstr(n, m);

		// output the secret code and prompt user for the number of guesses to play
		mstr.startGame();

		// play the game for the specified number of guesses
		mstr.playGame();
	}
	catch (rangeError &re)
	{
		cout << re.what() << endl;
		exit(0);
	}
}