// EECE 3326
// Project 1, b
//
// Tim Liming
// Wing Tung Yuen

/* Header file for Project 1.
   Contains mastermind class functions:
   constructor (passed values), constructor (default values), 
   startGame, playGame, and gameOutput.
*/

#include "1a.h"

using namespace std;

class mastermind
{
public:
	// Constructor:
	mastermind(int n, int m);
	mastermind();
	void startGame();
	void playGame();
	void gameOutput(int dig, int loc);
private:
	code cde;		// initialize a code object
	int numGuess;	// number of guesses to be played
}; // end class

/* constructor that takes in values for length and range and creates 
   the code object
*/
mastermind::mastermind(int n, int m)
	: cde(n, m)
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
}

/* constructor that creates the code object using default values
*/
mastermind::mastermind()
	: cde(5, 10)
{}

/* prints the secret code and prompts for the number of guess to be played
*/
void mastermind::startGame()
{
	cout << "The Secret Code is: " << cde << endl;

	cout << "How many guesses would you like to play?" << endl;
	cout << "n: ";
	cin >> numGuess;
}

/* controls the playing of the mastermind game
*/
void mastermind::playGame()
{
	// check inputs
	if (numGuess < 1)
    {
        throw rangeError("Cannot play with negative guesses.");
    }


	for (int i = 0; i < numGuess; i++)
	{
		// gets a guess from the user through the guess member function
		vector<int> guess = cde.guess();

		// passes the guess on to check correct and incorrect digits
		int digits = cde.checkCorrect(guess);
		int location = cde.checkIncorrect(guess);
		
		// output game feedback based on digits
		gameOutput(digits, location);
		
		// if user wins the game, return.
		if (digits == cde.getN())
		{
			return;
		} // end if
	} // end for

	cout << "You have run out of guesses.";

} // end playGame

/* prints the correct and incorrect digits or winning game dialogue
*/
void mastermind::gameOutput(int dig, int loc)
{
	// check inputs
	if (dig < 0)
    {
        throw rangeError("ERROR: Was expecting a positive number.");
    }
    if (loc < 0)
    {
        throw rangeError("ERROR: Was expecting a positive number.");
    }
	if (dig > cde.getN())
    {
        throw rangeError("ERROR: Cannot be larger than the length.");
    }
    if (loc > cde.getN())
    {
        throw rangeError("ERROR: Cannot be larger than the length.");
    }

	// determine output based on inputs
	if (dig == cde.getN())
	{
		cout << "You guessed the Secret Code!" << endl;
	}
	else
	{
		cout << dig << " digits were correct." << endl;
		cout << loc << " digits were correct but in the wrong location." << endl;
	}
} // end gameOutput