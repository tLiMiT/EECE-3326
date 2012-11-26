#1

void board::solve-all()
{
   if (solved())
      print();

   else
   {
      findBlankCell(i,j);

      int val = 1;
      for (int val = 1; val <= 9; val++)
      {
	 if (isLegal(i, j, val))
	 {
	    setCell(i,j,val);
	    solve-all();
	    unsetCell(i, j);
	 }
      }
   }
}

#2

void board::solve-once(bool &solutionFound)
{
   if (solved())
   {
      print();
      solutionFound = true;
   }

   else
   {
      findBlankCell(i,j);

      for (int i = 1; i <= 9; i++)
      {
	 if (isLegal(i, j, val))
	 {
	    setCell(i,j,val);
	    solve-once(solutionFound);
	    unsetCell(i, j);

	    if (solutionFound)
	       return;
	 }
      }
   }
}

bool board::solve-bool()
{
   if (solved())
      return true;

   else
   {
      findBlankCell(i,j);

      for (int val = 1; val <= 9; val++)
      {
	 if (isLegal(i, j, val))
	 {
	    setCell(i,j,val);
	    if (solve-bool());
   	       return true;
	    unsetCell(i, j);
	 }
	 val++;
      }
   }
   return false;
}
