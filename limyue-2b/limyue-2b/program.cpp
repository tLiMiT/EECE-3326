// EECE 3326
// Project 2, b
//
// Tim Liming
// Wing Tung Yuen

/* The program file for Project 2.
   contains the playFlip function that handles playing the Flip game
   contains the main function
*/

#include "deck.h"

using namespace std;

void playFlip()
{
	int points = 0;
	int count = 0;

	deck d;

	// shuffle three times
	d.shuffle();
	d.shuffle();
	d.shuffle();

	cout << "Press Enter to deal a card. Press any other key to stop." << endl;

	while (cin.get() == '\n')
	{
		card c = d.deal();
		int val = c.getValue();
		Suit s = c.getSuit();

		// display the card dealt
		cout << c << endl;;

		// 10 points for an Ace
		if (val == 14)
		{
			points += 10;

			// 1 extra point for a Heart
			if (s == HEARTS)
			{
				points += 1;
			}
		}

		// 5 points for King, Queen, or Jack
		else if (val ==  13 || val == 12 || val == 11)
		{
			points += 5;

			// 1 extra point for a Heart
			if (s == HEARTS)
			{
				points += 1;
			}
		}

		// 0 points for 8, 9, or 10
		else if (val == 8 || val == 9 || val == 10)
		{
			points += 0;

			// 1 extra point for a Heart
			if (s == HEARTS)
			{
				points += 1;
			}
		}

		// lose half points for a 7
		else if (val == 7)
		{
			points /= 2;

			// 1 extra point for a Heart
			if (s == HEARTS)
			{
				points += 1;
			}
		}

		// lose all points for 2, 3, 4, 5, or 6
		else if (val == 2 || val == 3 || val == 4 || val == 5 || val == 6)
		{
			points = 0;

			// 1 extra point for a Heart
			if (s == HEARTS)
			{

				points += 1;
			}
		}

		// Output user score
		cout << "Your score is: " << points << endl;

		// check if deck is complete
		count ++;
		if (count == 52)
		{
			cout << "The entire deck has been played through." << endl;
			break; 
		}
	
	} // while
} // playFlip


int main()
{
	try
	{
		// play the Flip game
		playFlip();
	}
	// catch errors thrown
	catch (rangeError &re)
	{
		cout << re.what() << endl;
	}
	catch (underflowError &ue)
	{
		cout << ue.what() << endl;
	}
	catch (overflowError &oe)
	{
		cout << oe.what() << endl;
	}
} // main