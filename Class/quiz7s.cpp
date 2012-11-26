// Solutions to quiz #6

#include <iostream>
#include "d_matrix.h"
#include "d_except.h"
#include <vector>

using namespace std;

bool check(vector<int> v, int target, int n)
// Returns true if target appears in v, and false otherwise.  Checks
// starting at index n.
{
   if (n == v.size())
      return false;
   else
   {
      if (v[n] == target)
	 return true;
      else
         return check(v,target,n+1);
   }
}

int count(vector<int> v, int target, int n)
// Returns the number of times target appears in v, starting at index n.
{
   if (n == v.size())
      return 0;
   else
   {
      int num = 0;
      if (v[n] == target)
         num = 1;
      return num + count(v, target, n+1);
   }
}

int main()
{
   vector<int> v;
   v.push_back(4);
   v.push_back(3);
   v.push_back(5);
   v.push_back(1);
   v.push_back(2);
   v.push_back(2);
   v.push_back(3);

   cout << check(v,99,0) << endl;
   cout << count(v,3,0) << endl;
}

