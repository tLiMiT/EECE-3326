EECE-3326
=========

EECE3326 - Optimization Methods

Project #2

Write a program that allows the user to play the card game flip. Flip is played by one player with
a standard deck of 52 cards. The game has the following steps:

  1. The cards are shuffed three times.

  2. The player keeps taking cards until the player decides to stop and end the game.

  3. To take a card, the player turns over the top card on the deck and

      (a) receives 10 points for an ace,

      (b) receives 5 points for a king, queen or jack,

      (c) receives 0 points for an 8, 9 or 10,

      (d) loses half their points for a 7,

      (e) loses all their points for a 2, 3, 4, 5 or 6, and

      (f) receives 1 point extra, in addition to the above, for a heart.

  4. The goal is to end the game with the most points.

Part a

Fully implement a card class that stores a single card. A card includes a value and a suit (club,
diamond, heart or spade). The class should at least include constructors, set, and get functions,
and an overloaded print operator.

Fully implement a deck class that stores the cards in a deck in order. A deck of cards should be
implemented using a linked list of nodes, each of which contains a single card. The deck object
should contain a pointer to the first card in the deck. The class should at least include a constructor
that creates a deck with all the cards in order (2-A, clubs to spades) and an overloaded operator
that prints the cards in the deck.

Exceptions should be thrown for all error conditions and all exceptions should be caught.

Include a main function that initializes a deck and prints all the cards in the deck.