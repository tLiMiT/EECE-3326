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

using namespace std;

class dictionary
{
public:
	dictionary();						// default constructor
	dictionary(const string &dfln);		// constructor
	bool wordLookup(string word) const;	// finds a word in the dictionary
	void printDict();					// prints the dictionary
protected:
	vector<string> wordVect;
private:
	void readDict(string fln);
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
	int numLines = 0;
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

/* find words in the dictionary */
bool dictionary::wordLookup(string w) const
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		if (wordVect[i] == w)
		{
			return true;
		}
	} // for

	return false;
} // wordLookup

/* print all words in the dictionary (sanity check, not recommended) */
void dictionary::printDict()
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		cout << wordVect[i] << endl;
	}
} // printDict