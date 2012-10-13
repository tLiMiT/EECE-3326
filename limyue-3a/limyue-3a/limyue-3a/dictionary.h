// EECE 3326
// Project 3, a
//
// Tim Liming
// Wing Tung Yuen

/* dictionary.h Header file for Project 3.
   
   Contains dictionary class functions:
   
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class dictionary
{
public:
	dictionary();
	dictionary(const string &dfln);
	bool wordLookup(string word) const;
	void printDict();
private:
	void readDict(string fln);
	vector<string> wordVect;
};


/* dictionary constructor */
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
	string word;
	ifstream fin;
	fin.open(dfln.c_str());
	if (! fin)
	{
		throw fileOpenError(dfln);
	}
	cout << "Loading dictionary..." << endl;

	////
	while (getline(fin, word))
	{
		wordVect.push_back(word);
	}
	////

	fin.close();
	cout << "Dictionary loaded." << endl;
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

/* print all words in the dictionary (not recommended) */
void dictionary::printDict()
{
	for (int i = 0; i < wordVect.size(); i++)
	{
		cout << wordVect[i] << endl;
	}
} // printDict