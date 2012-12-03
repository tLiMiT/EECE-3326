// Project 6, sample solution

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

int const NONE = -1;  // Used to represent a node that does not exist
EdgeWeight const MaxEdgeWeight = 99999;

void bfs(int start, graph &g, graph &sf)
// Perform a breadth-first search of unvisited nodes in graph g
// starting at the start node.  Add edges to graph st as they are
// discovered.
{

   int v;
   bool neighborFound;
   queue<int> q;

   // Push the start node on the queue and visit it
   q.push(start);
   g.visit(start);

   // Continue until the queue is empty 
   while (!q.empty())
   {
      // Find all unvisited neighbors of the current node and
      // push them on the queue.
      
      int v = 0;
      while (v < g.numNodes())
      {
         if (g.isEdge(q.front(),v) && !g.isVisited(v))
	 {
 	    sf.addEdge(v,q.front(),g.getEdge(q.front(),v).getWeight());
 	    sf.addEdge(q.front(),v,g.getEdge(q.front(),v).getWeight());

	    q.push(v);
            g.visit(v);
	 }
	 v++;
      }

      // Pop the front node off the queue and continue with the while
      // loop.
      
      q.pop();
   }
}

int findSpanningForest(graph &g, graph &sf)
// Create a graph sf that contains a spanning forest on the graph g.
// Return the number of connected components in g.
{
   g.clearVisit();

   // Add edges starting at every unvisited node, until all nodes
   // have been visited.
   
   int v = 0;
   while (v <= g.numNodes() && !g.allNodesVisited())
   {
      bfs(v,g,sf);
      v++;
   }
   return v;
}
   
int main()
{
   char x;
   ifstream fin;
   stack <int> moves;
   string fileName;
   
   // Read the name of the graph from the keyboard or
   // hard code it here for testing.
   
   fileName = "graph3.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try

   {
      cout << "Reading graph" << endl;
      graph g(fin);

      cout << g;
	    
      bool connected;
      bool cyclic;

      cout << "Finding spanning forest" << endl;

      // Initialize an empty graph to contain the spanning forest
      int numConnectedComponents;
      
      graph sf(g.numNodes());
      numConnectedComponents = findSpanningForest(g,sf);
      cout << endl;

      cout << sf;
      cout << "Num connected components: " << numConnectedComponents << endl;
      cout << endl;
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

