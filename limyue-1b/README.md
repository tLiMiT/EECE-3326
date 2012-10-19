EECE-3326
=========

EECE3326 - Optimization Methods

Project #1
Part b
In the second part of the project, complete the program that allows a user to play Mastermind
against the computer.
1. Add the function checkIncorrect to the code class. The function is passed a guess as a
parameter and returns the number of correct digits in the incorrect location. No digit in the
guess or the code should be counted more than once.
2. Implement the class mastermind which handles the playing of the game. The mastermind
class should have a code object as a data member.
3. Write an overloaded output operator << that prints the secret code in a code object, and
an output operator that prints vectors.
4. The mastermind class should include at least two constructors to initialize the game. One
constructor is passed values of n and m that were read from the keyboard, and the other
constructor is passed no parameters and uses default values for n and m.
5. Check the inputs to every function and throw exceptions wherever errors are detected. Every
exception should be caught, should print an appropriate error message, and should cause the
execution of the program to halt using the exit(0) command.
The version of the program you submit should print the secret code to the screen before the game
starts. We will use this information to see if your program is working correctly.