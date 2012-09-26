// EECE 3326
// Project 2, a
//
// Tim Liming
// Wing Tung Yuen

/* card.h Header file for Project 2.

   Contains card class functions:

*/

#include "d_except.h"
#include <iostream>

using namespace std;

/* class card */
class card
{
public:
	card();
	int getValue();
	void setValue();
	int getSuit();
	void setSuit();
	friend ostream &operator<<(ostream &out, const card &c);
private:

};



/* Overload the '<<' operator for card objects
*/
ostream &operator<<(ostream &out, const card &c)
{
	out << c;

	return out;
}