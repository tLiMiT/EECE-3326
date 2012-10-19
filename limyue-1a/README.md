EECE-3326
=========

EECE3326 - Optimization Methods

Project #1

In this project, you will write a complete program that allows the user to play a game of Mastermind
against the computer. A Mastermind game has the following steps:

	1. The user is prompted to enter two integers, the code length n, and the range of digits m < 10.

	2. The computer selects a code, a random sequence of n digits, each of which is in the range [0,m-1].

 	3. The user is prompted to enter a guess, an n-digit sequence.

	4. The computer responds by printing two values that indicate how close the guess is to the
		code. The rst response value is the number of digits that are the right digit in the right
		location. The second response value is the number of digits that are the right digit in the
		wrong location.
		For example if the code is 1; 2; 3; 4; 5 and the guess is 5; 0; 3; 2; 6, the response would be 1; 2
		because one digit (3) is the right digit in the right location, and two digits (2 and 5) are the
		right digits in the wrong locations.
		Note that no digit in the code or guess is counted more than once. If the code is 1; 2; 3; 4; 5
		and the guess is 2; 1; 2; 2; 2, the response is 0; 2. If the code is 3; 2; 3; 3; 3 and the guess is
		1; 3; 3; 4; 5, the response is 1; 1.

	5. The user is prompted to continue entering guesses. The user wins if the correct code is
		guessed. The user loses if a predetermined maximum number of guesses has been made.

Your program should be modular and should make full use of object-oriented programming tech-
niques. Each class should clearly separate its interface from its implementation. Use member
functions to implement all commonly used operations.

Part a

In the first part of the project, implement the class code which stores the code as a vector. No
error-checking is necessary. Implement:

	1. the code class declaration,

	2. a constructor that is passed values n and m and which initializes the random code,

	3. a function checkCorrect which is passed a guess as a parameter and which returns the
		number of correct digits in the correct location,

	4. a function main which initializes a code, prints it out, and prints out the result of calling
		checkCorrect for three sample inputs.
