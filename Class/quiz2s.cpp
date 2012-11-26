#include <vector>
#include <iostream>

#include "d_random.h"
#include "d_except.h"

using namespace std;



class code
// Represents the hidden code in Mastermind
{
   public:
      code(int m, int n);
      int checkCorrect(vector<int> &guess);
      int checkIncorrect(vector<int> &guess);
      friend int operator%(const code &lhs, const vector<int> &rhs);
      int size() const {return seq.size();} 
   private:
      randomNumber rnd;
      vector<int> seq;	
};

int operator%(const code &lhs, const vector<int> &rhs)
// Overloaded operator that returns the number of digits in the code
// in the lhs that match the vector rhs.
{
   int count = 0;
   
   if (lhs.size() != rhs.size())
      throw rangeError();

   for (int i = 0; i < rhs.size(); i++)
      if (lhs.seq[i] == rhs[i])
	 count++;

   return count;
}

class mastermind
{
   public:
      mastermind();
      mastermind(int m, int n);
      void playMastermind();
      void test();
   private:
      code secretCode;
};      

void mastermind::test()
{
   try
      {
         vector<int> guess;
         cout << secretCode % guess;
      }
   catch (rangeError &ex)
      {
         cout <<"Error" << endl;
      }
   
}

int main()
{}
