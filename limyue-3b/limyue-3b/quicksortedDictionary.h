// EECE 3326
// Project 3, b
//
// Tim Liming
// Wing Tung Yuen

/* quicksortedDictionary.h Header file for Project 3.
   
   Contains quicksortedDictionary class functions:
   constructor, sort
   Contains functions: 
   partition, quicksort
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "sortedDictionary.h"

using namespace std;

class quicksortedDictionary
	: public sortedDictionary
{
public:
	quicksortedDictionary(string fln = "dictionary");
private:
	virtual void sort();
};

/* quicksortedDictionary constructor */
quicksortedDictionary::quicksortedDictionary(string fln)
	: sortedDictionary(fln)
{
	sort();
}

/* partition function */
int partition(vector<string> &words, int first, int last, int pivot)
{
	swap(words[pivot], words[last]);
	int start = first;

	for (int i = first; i < last; i++)
	{
		if (words[i] <= words[last])
		{
			swap(words[i], words[start]);
			start++;
		} // if
	} // for 

	swap(words[start], words[last]);
	return start;
} // partition

/* quicksort function */
void quicksort(vector<string> &words, int first, int last)
{
	if (first < last)
	{
		int p = (first + last) / 2;
		p = partition(words, first, last, p);
		quicksort(words, first, p - 1);
		quicksort(words, p + 1, last);
	} // if
} // quicksort

/* sort function
   sorts the dictionary using quicksort
*/
void quicksortedDictionary::sort()
{
	quicksort(wordVect, 0, wordVect.size() - 1);
} // sort