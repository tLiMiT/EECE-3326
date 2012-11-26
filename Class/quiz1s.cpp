#include <iostream>
#include <vector>
#include "d_random.h"

using namespace std;

class code
{
   public:
      code(int n, int m);
      bool allRight(const vector<int> &guess);
   private:
      randomNumber rnd;
      vector<int> secretCode;
};

template <typename T>
bool vectorsEqual(const vector<T> &v1, const vector<T> &v2)
// Returns true if v1 and v2 are the same size and contain the same
// values.
{
   if (v1.size() != v2.size())
      return false;

   for (int i = 0; i < v1.size(); i++)
      if (v1[i] != v2[i])
	 return false;

   return true;
}

bool code::allRight(const vector<int> &guess)
// Returns true if the guess and the secret code vectors match.
{
   if (vectorsEqual(secretCode,guess))
       return true;
   else
      return false;
}

int main()
{
   code c(5,10);
   vector<int> guess;

   guess.push_back(1);
   guess.push_back(2);
   guess.push_back(3);
   guess.push_back(4);
   guess.push_back(5);

   if (c.allRight(guess))
      cout << "The guess is right" << endl;
   
   
}
