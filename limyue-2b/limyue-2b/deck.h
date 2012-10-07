// EECE 3326
// Project 2, b
//
// Tim Liming
// Wing Tung Yuen

/* deck.h Header file for Project 2.
   
   Contains deck class functions:
   default constructor

   overloaded '<<' operator that prints all the cards in a deck
*/

#include "card.h"
#include <algorithm>
#include "d_node.h"

using namespace std;

/* deck class */
class deck
{
public:
	deck();							// default constructor
	~deck();						// destructor
	card deal();					// deal a card from the top
	void replace(card toAdd);		// replace card at the bottom of a deck
	void shuffle();					// shuffle all cards in a deck
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

/* destructor for the deck
*/
deck::~deck()
{
	node<card> *next = NULL;

	while (aCard != NULL)
	{
		next = aCard->next;
		delete aCard;
		aCard = next;
	}
}

/* deal from the top of the deck
*/
card deck::deal()
{
	if (aCard != NULL)
	{
		node<card> *curr = aCard;
		card val = curr->nodeValue;
		aCard = aCard->next;
		delete curr;
		return val;
	}
	else
	{
		throw underflowError("ERROR: No cards to deal");
	}
} // deal

/* replace a card on the bottom of the deck
*/
void deck::replace(card toAdd)
{
	node<card> *curr = aCard;
	node<card> *bottomCard;
	int count = 0;

	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			bottomCard = curr;
		} // if

		curr = curr->next;
		count++;

	} // while

	// check deck size
	if (count >= 52)
	{
		throw overflowError("ERROR: Deck is already full");
	}
	
	// add the card to the bottom of the deck
	curr = new node<card>(toAdd, NULL);
	bottomCard->next = curr;
} // replace

/* shuffles the deck
*/
void deck::shuffle()
{
	vector<card> cardVect;
	node<card> *cards = aCard;

	// transfer cards to a vector
	while (cards != NULL)
	{
		cardVect.push_back(cards->nodeValue);
		cards = cards->next;
	} // for

	// shuffle all elements in the vector
	random_shuffle(cardVect.begin(), cardVect.end());

	// transfer cards back to a list
	int i = 0;
	node<card> *top = aCard;

	while (aCard != NULL)
	{
		aCard->nodeValue = cardVect[i];
		aCard = aCard->next;
		i++;
	}

	aCard = top;
} // shuffle


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