// EECE 3326
// Project 6, b
//
// Tim Liming
// Wing Tung Yuen

// Project 6
//
// Assumes that directed edges in both directions (x,y) and (y,x) are present in the input file.
//

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

// Helper Functions
void visitNodes(int start, graph &g)
	// Visit all nodes reachable from the start node
{
	bool found = false;

	// Mark the start node as visited.
	g.visit(start);

	int v = 0;

	// Keep looking for legal moves as long as there are more neighbors
	// to check.
	while (!found && v < g.numNodes())
	{
		// if v is an unvisited neighbor of the start node, recurse.

		if (g.isEdge(start, v) && !g.isVisited(v))
		{
			visitNodes(v, g);
		}
		v++;
	}
} // visitNodes

vector<int> getNeighbors(int id, graph &g)
	// get all neighbors of the node (id) in the graph (g)
{
	vector<int> lst;

	for (int i = 0; i < g.numNodes(); i++)
	{
		if (g.isEdge(id, i))
		{
			lst.push_back(i);
		}
	} // for
	return lst;
} // getNeighbors

void findCycle(int curr, int start, bool &found, graph &g)
	// checks for cycles in a graph
{
	g.mark(curr);

	vector<int> lst = getNeighbors(curr, g);

	for (int i = 0; i < lst.size(); i++)
	{
		if (start == lst[i])
		{
			continue;
		}
		if (g.isMarked(lst[i]))
		{
			found = true;
		}
		else if (!g.isVisited(lst[i]))
		{
			findCycle(lst[i], curr, found, g);
		}
	} // for

	g.unMark(curr);
	g.visit(curr);

} // findCycle

// Project Functions
bool isCyclic(graph &g)
	// Returns true if the graph g contains a cycle.  Otherwise, returns false.
{
	g.clearVisit();
	g.clearMark();

	bool cycle = false;

	for (int i = 0; i < g.numNodes(); i++)
	{
		if (!g.isVisited(i))
			findCycle(i, i, cycle, g);
	}

	g.clearMark();
	g.clearVisit();

	return cycle;
} // isCyclic

bool isConnected(graph &g)
	// Returns true if the graph g is connected.  Otherwise returns false.
{
	g.clearVisit();
	g.clearMark();

	visitNodes(0, g);	// start at '0' the 'first' node

	for (int i = 0; i < g.numNodes(); i++)
	{
		if (!g.isVisited(i))
		{
			return false;
		}
	} // for
	return true;
} // isConnected

void findSpanningForest(graph &g, graph &sf)
	// Create a graph sf that contains a spanning forest on the graph g.
{
	if (isConnected(g) && !isCyclic(g))
	{
		sf = g;
	}
	else
	{
		// add nodes to sf
		for (int i = 0; i < g.numNodes(); i++)
		{
			sf.addNode(g.getNode(i));
		}

		// build sf
		for (int i = 0; i < g.numNodes(); i++)
		{
			for (int j = 0; j < g.numNodes(); j++)
			{
				if (g.isEdge(i, j) && !sf.isEdge(i, j))
				{
					sf.addEdge(i, j, g.getEdgeWeight(i, j));
					sf.addEdge(j, i, g.getEdgeWeight(j, i));

					if(isCyclic(sf))
					{
						sf.removeEdge(j, i);
						sf.removeEdge(i, j);
					} // if
				} // if
			} // for
		} // for
	} // else
} // findSpanningForest

class CompareEdge
	// returns true if edge1 is greater than edge2
{
public:
	bool operator() (edge &e1, edge &e2)
	{
		return e2.getWeight() < e1.getWeight();
	}
};

void findMSF(graph &g, graph &sf, int start)
	// finds a minimum spanning tree in graph 'g'
{
	priority_queue<edge, vector<edge>, CompareEdge> pq;
	vector<int> lst = getNeighbors(start, g);

	// build our priority queue
	for (int i = 0; i < lst.size(); i++)
	{
		pq.push(g.getEdge(start, lst[i]));
		g.mark(start, lst[i]);
	}

	// visit the start node
	g.visit(start);

	int src, dst, w;
	edge top;

	while (!pq.empty())
	{
		top = pq.top();
		pq.pop();
		src = top.getSource();
		dst = top.getDest();
		w = top.getWeight();

		// add edges
		if (!sf.isEdge(src, dst))
		{
			sf.addEdge(src, dst, w);
			sf.addEdge(dst, src, w);

			// delete edges if we make a cycle
			if (isCyclic(sf))
			{
				sf.removeEdge(src, dst);
				sf.removeEdge(dst, src);
			}
			else
			{
				g.visit(src);
				lst = getNeighbors(dst, g);

				for (int i = 0; i < lst.size(); i++)
				{
					if (!g.isMarked(dst, lst[i]))
					{
						pq.push(g.getEdge(dst, lst[i]));
						g.mark(dst, lst[i]);
					}
				} // for
			} // else
		} // if
	} // while
} // findMSF

void prim(graph &g, graph &msf)
	// Given a weighted graph g, sets msf equal to a minimum spanning
	// forest on g. Uses Prim's algorithm.
{
	// build msf
	for (int i = 0; i < g.numNodes(); i++)
	{
		msf.addNode(g.getNode(i));
	}

	// populate msf using findMSF
	for (int i = 0; i < g.numNodes(); i++)
	{
		if (!g.isVisited(i))
		{
			findMSF(g, msf, i);
		}
	}
} // prim


// MAIN FUNCTION
int main()
{
	ifstream fin;
	stack <int> moves;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	fileName = "graph4.txt";

	// cout << "Enter filename: ";
	// cin >> fileName;
	// cout << endl;

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

		connected = isConnected(g);
		cyclic = isCyclic(g);

		if (connected)
			cout << "Graph is connected" << endl;
		else
			cout << "Graph is not connected" << endl;

		if (cyclic)
			cout << "Graph contains a cycle" << endl;
		else
			cout << "Graph does not contain a cycle" << endl;

		cout << endl;

		cout << "Finding spanning forest" << endl;

		// Initialize an empty graph to contain the spanning forest
		graph sf;
		findSpanningForest(g, sf);

		graph msf;
		prim(g, msf);

		cout << endl;

		cout << msf;

		cout << "Spanning forest weight: " << sf.getTotalEdgeWeight()/2 << endl;

		connected = isConnected(sf);
		cyclic = isCyclic(sf);

		if (connected)
			cout << "Graph is connected" << endl;
		else
			cout << "Graph is not connected" << endl;

		if (cyclic)
			cout << "Graph contains a cycle" << endl;
		else
			cout << "Graph does not contain a cycle" << endl;

		cout << endl;

		cout << "Minimum Cost: " << msf.getTotalEdgeWeight()/2 << endl;
		cout << "Difference: " << sf.getTotalEdgeWeight()/2 - msf.getTotalEdgeWeight()/2 << endl;
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

