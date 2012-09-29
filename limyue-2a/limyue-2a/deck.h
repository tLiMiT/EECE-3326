// EECE 3326
// Project 2, a
//
// Tim Liming
// Wing Tung Yuen

/* deck.h Header file for Project 2.
   
   Contains deck class functions:
   default constructor

   overloaded '<<' operator that prints all the cards in a deck
*/

#include "card.h"
#include "d_node.h"

using namespace std;

/* deck class */
class deck
{
public:
	deck();		// default constructor
	friend ostream &operator<<(ostream &ostr, const deck &d);
private:
	node<card> *aCard;
};

/* default constructor for deck 
   creates a deck of cards [2 - Ace] and [Clubs - Spades]
*/
deck::deck()
{
	node<card> *curr = NULL;

	/* loops through each suit starting at Spades since we want spades to 
	   be the last suit when we go through and print out the deck
	*/
	for (int i = 3; i >= 0; i--)
	{
		/* loops through each card value [2 - Ace]
		*/
		for (int val = 14; val > 1; val--)
		{
			/* creates a new node that contains a single card consisting
			   of a card value and a card suit
			*/
			aCard = new node<card> (card(val, static_cast<Suit>(i)), curr);
			
			curr = aCard;
		} // end for
	} // end for
}


/* Overload the '<<' operator for deck objects */
ostream &operator<<(ostream &ostr, const deck &d)
{
	node<card> *card = d.aCard;

	// while the card doesn't point to NULL, we print the list 
	while (card != NULL)
	{
		ostr << card->nodeValue << endl;
		card = card->next;
	}

	return ostr;
}