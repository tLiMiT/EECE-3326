EECE-3326
=========

EECE3326 - Optimization Methods

Project #2
Part b
Complete the program that allows the user to play the card game ip:
1. Add a copy constructor and overloaded assignment operator to the card class, and a destruc-
tor to the deck class.
2. Add a function deal to the deck class that returns the top card in the deck by value. The
card is also removed from the deck.
3. Add a function replace to the deck class that is passed a card as a parameter by value. The
card is placed on the bottom of the deck.
4. Add a function shuffle to the deck class that shues the cards. Use any algorithm to shue
the cards that puts the cards in a random order. It is acceptable to move cards around, and
not reorder nodes.
5. Write a global function playFlip that plays the game by reading instructions from the
keyboard and printing the results to the screen.
Exceptions should be thrown for all error conditions and all exceptions should be caught.