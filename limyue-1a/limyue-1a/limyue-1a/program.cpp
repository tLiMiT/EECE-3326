// EECE 3326
// Project 1, a
//
// Tim Liming
// Wing Yuen
//
// Main program file for Project 1. Contains main function.

#include "1a.h"

int main()
{
	code c;						// Initialize a code object

	c.setCode();				// input code parameters
	c.getCode();				// generate a random code

	c.guess();					// prompt a guess
	cout << c.checkCorrect();	// output result

	c.guess();					// prompt a guess
	cout << c.checkCorrect();	// output result

	c.guess();					// prompt a guess
	cout << c.checkCorrect();	// output result

}
