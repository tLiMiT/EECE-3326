// EECE 3326
// Project 3, b
//
// Tim Liming
// Wing Tung Yuen

/* sortedDictionary.h Header file for Project 3.
   
   Contains sortedDictionary class functions:
   constructor, sortedLookup
   Contains function:
   binarySearch
*/

#include <vector>
#include <string>
#include "dictionary.h"

using namespace std;

class sortedDictionary
	: public dictionary
{
public:
	sortedDictionary(string fln = "dictionary");
	virtual bool sortedLookup(string word) const;
protected:
	virtual void sort() = 0;
};

/* constructor */
sortedDictionary::sortedDictionary(string fln)
	: dictionary(fln)
{}

/* binarySearch function */
int binarySearch(const vector<string> &dict, 
				 int first, 
				 int last, 
				 string target)
{
	if (first > last) { return -1; }
    
    while (first < last)
	{
		int mid = (first + last) / 2;

		if (target == dict[mid])
		{
			return mid;
		}
		else if (target < dict[mid])
		{  
			return binarySearch(dict, first, mid - 1, target);
		}
		else
		{
			return binarySearch(dict, mid + 1, last, target);
		}
	} // while
} // binarySearch

/* look up for a sorted dictionary */
bool sortedDictionary::sortedLookup(string word) const
{
	return binarySearch(wordVect, 0, wordVect.size() - 1, word) != -1;
}