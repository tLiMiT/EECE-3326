// EECE 3326
// Project 3, b
//
// Tim Liming
// Wing Tung Yuen

/* dictionary.h Header file for Project 3.
   
   Contains dictionary class functions:
   default constructor, constructor, wordLookup,
   printDict
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "d_except.h"

using namespace std;

class dictionary
{
public:
	dictionary();						// default constructor
	dictionary(const string &dfln);		// constructor
	void printDict();					// prints the dictionary
	void sort();						// sorts the dictionary based on the algorithm
	bool binarySearch(int first, int last, string target) const;
	int getSize() const { return numLines; } 
private:
	void readDict(string fln);	
	vector<string> wordVect;
	int numLines;
};


/* dictionary default constructor */
dictionary::dictionary()
{
	readDict("dictionary");
} // constructor

/* dictionary constructor */
dictionary::dictionary(const string &fln)
{
	readDict(fln);
} // constructor

/* reads all words in the dictionary and puts them into a vector */
void dictionary::readDict(string dfln)
{
	ifstream fin;

	fin.open(dfln.c_str());
	if (! fin)
	{
		throw fileOpenError(dfln);
	}
	cout << "Loading dictionary...";

	// initialize
	string word;
	string tmp;
	numLines = 0;
	int wordIndex = 0;

	// count the number of lines in the dictionary
	while (getline(fin, tmp)) { numLines++; } 

	fin.clear();							// clear
	fin.seekg(0, ios::beg);					// return to beginning of file
	wordVect = vector<string>(numLines);	// preallocate vector for speed

	while (getline(fin, word))				// place words from the dictionary
	{										// file into a vector
		wordVect[wordIndex++] = word;		// much faster than push_back
	}

	fin.close();
	cout << '\r' << "Dictionary loaded.   " << endl;
} // readDict

/* binarySearch function */
bool dictionary::binarySearch(int first, int last, string target) const
{
	if (first > last) 
	{ 
		return false; 
	} // if
	else if (first == last) 
	{ 
		return target.compare(wordVect[first]) == 0; 
	} // else if

    while (first < last)
	{
		int mid = (first + last) / 2;
		int compare = target.compare(wordVect[mid]);

		if (compare == 0)
		{
			return true;
		} // if
		else if (compare < 0)
		{
			// recurse
			return binarySearch(first, mid, target);
		} // else if
		else
		{
			// recurse
			return binarySearch(mid + 1, last, target);
		} // else
	} // while
} // binarySearch

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

/* selection sort function */
void selectsort(vector<string> &words)
{
	string temp;
	int min;

	for (int i = 0; i < words.size() - 1; i++)
	{
		min = i;

		for ( int j = i + 1; j < words.size() - 1; j++)
		{
			if (words[j] < words[min])
			{
				min = j;
			} // if
		} // for

		temp = words[i];
		words[i] = words[min];
		words[min] = temp;
	} // for
} // selectsort

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

/* sort function */
void dictionary::sort()
{
	//selectsort(wordVect);
	quicksort(wordVect, 0, wordVect.size()-1);
} // sort

/* print all words in the dictionary (sanity check, not recommended) */
void dictionary::printDict()
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		cout << wordVect[i] << endl;
	}
} // printDict