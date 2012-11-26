void matchDiagonal(dictionary &d, grid &g, int startI, int startJ)
// If the characters in the matrix starting at position (startI,
// startJ) and continuing diagonally down and left match a word in the
// dictionary, print that word out.
{
   string s;
   int updateI, updateJ;

   int i = startI;
   int j = startJ;

   // Consider strings of all lengths.
   for (int k = 0; k < g.getCols(); k++)
   {
      // Build up a string s containing consecutive characters from
      // the matrix in some direction.

      s.push_back(g.getChar(i,j));

      // Update the i and j indices in the appropriate way, depending
      // on the direction.

      i++;
      j++;

      // Wrap around at the edge of the matrix.

      if (i == -1)
	 i = g.getRows()-1;
            else
	       if (i == g.getRows())
		  i = 0;

      if (j == -1)
	 j = g.getCols()-1;
            else
	       if (j == g.getCols())
		  j = 0;

      // If the string s is in the dictionary, print it out.
      if (d.indictionary(s) && s.size() > 4)
	 cout << "found: " << s << endl;
   }
}

