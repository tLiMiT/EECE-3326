// Solution to quiz #8

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>
#include <vector>

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      int getReverseMapI(int n) const;
      int getReverseMapJ(int n) const;
      void mapMazeToGraph(graph &g);

      void visitNodesRecursive(graph &g);
      void visitNodes(int start, graph &g);
      bool allOpenReachable();
      
      void maze::printPath(stack<int> &s);
      int numRows(){return rows;};
      int numCols(){return cols;};

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;

      matrix<int> map;      // Mapping from maze (i,j) values to node index values
      vector<int> reverseMapI; // Mapping from node index values to maze i value
      vector<int> reverseMapJ; // Mapping from node index values to maze j value
      
};

bool maze::allOpenReachable()
// Returns true if all open cells in the maze are reachable from the
// start cell, and returns false otherwise.
{
   graph g;
   mapMazeToGraph(g);   

   g.clearVisit();
   visitNodes(map[0][0],g);

   for (int i = 0; i < g.numNodes(); i++)
      if (!g.isVisited(i))
      {
         cout << i << " " << getReverseMapI(i) << " " << getReverseMapJ(i) << endl;
	 return false;
      }
   return true;
}

void maze::visitNodes(int start, graph &g)
// Visit all nodes reachable from the start node
{
   bool found;

   // Mark the start node as visited.
   g.visit(start);

   found = false;
   int v = 0;

   // Keep looking for legal moves as long as there are more neighbors
   // to check.
      
   while (!found && v < g.numNodes())
   {
      // if v is an unvisited neighbor of the start node, recurse.
	 
      if (g.isEdge(start,v) && !g.isVisited(v))
	 visitNodes(v,g);
      v++;
   }
}

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
   map[i][j] = n;
   reverseMapI[n] = i;
   reverseMapJ[n] = j;
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
   return map[i][j];
}

int maze ::getReverseMapI(int n) const
// Return reverse mapping of node n to it's maze i value.
{
   return reverseMapI[n];
}

int maze ::getReverseMapJ(int n) const
// Return reverse mapping of node n to it's maze j value.
{
   return reverseMapJ[n];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
   reverseMapI.resize(rows*cols);
   reverseMapJ.resize(rows*cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
   int index;
   
   for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
      {
         // If (i,j) represents a legal cell in the matrix, create a
         // new node that represents the cell
         if (isLegal(i,j))
	 {
	    index = g.addNode();
	    setMap(i,j,index);     // save the node's index in map.
	 }
      }

   for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
      {
         // If (i,j) represents a legal cell in the matrix, add an
         // edge for every legal move from (i,j).
         if (isLegal(i,j))
	 {
            // Add up edge
	    if (i > 0 && isLegal(i-1,j))
	       g.addEdge(getMap(i,j), getMap(i-1,j));

            // Add up edge
	    if (i < rows-1 && isLegal(i+1,j))
	       g.addEdge(getMap(i,j), getMap(i+1,j));

	    // Add left edge
	    if (j > 0 && isLegal(i,j-1))
	       g.addEdge(getMap(i,j), getMap(i,j-1));

	    // Add rightedge
	    if (j < cols-1 && isLegal(i,j+1))
	       g.addEdge(getMap(i,j), getMap(i,j+1));
	 }
      }
}

void maze::printPath(stack<int> &s)
// Print the path in stack s.
{
   int v;	    

   while (!s.empty())
   {
      v = s.top();
      s.pop();
      print(rows-1,cols-1,reverseMapI[v],reverseMapJ[v]);
   }
}

int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   
   // Read the maze from the file.
   string fileName = "maze1.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      graph g;
      while (fin && fin.peek() != 'Z')
      {
	 maze m(fin);
         if (m.allOpenReachable())
	    cout << "All reachable" << endl;
	 else
	    cout << "Not all reachable" << endl;
      }
   }

   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}
