// EECE 3326
// Project 3, b
//
// Tim Liming
// Wing Tung Yuen

/* selectionsortedDictionary.h Header file for Project 3.
   
   Contains selectionsortedDictionary class functions:
   constructor, sort
   Contains functions: 
   selectsort
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "sortedDictionary.h"

using namespace std;

class selectionsortedDictionary
	: public sortedDictionary
{
public:
	selectionsortedDictionary(string fln = "dictionary");
private:
	virtual void sort();
};

/* constructor */
selectionsortedDictionary::selectionsortedDictionary(string fln)
	: sortedDictionary(fln)
{
	sort();
}

/* selection sort function */
void selectsort(vector<string> &words)
{
	for (int i = 0; i < words.size() - 1; i++)
	{
		int nextInd = i;

		for ( int j = i + 1; j < words.size(); j++)
		{
			if (words[j] < words[nextInd])
			{
				nextInd = j;
			} // if
		} // for

		swap(words[i], words[nextInd]);
	} // for
} // selectsort

/* sort function
   sorts the dictionary using selectsort
*/
void selectionsortedDictionary::sort()
{
	selectsort(wordVect);
} // sort