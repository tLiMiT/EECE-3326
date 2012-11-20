// EECE 3326
// Project 5, b
//
// Tim Liming
// Wing Tung Yuen


// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <utility>
#include <queue>
#include <map>

using namespace std;

class maze
{
public:
	maze(ifstream &fin);

	int numRows() { return rows; };
	int numCols() { return cols; };

	void print(int,int,int,int);
	bool isLegal(int i, int j);

	void setMap(int i, int j, int n);
	int getMap(int i, int j) const;
	int getReverseMapI(int n) const;
	int getReverseMapJ(int n) const;

	void mapMazeToGraph(graph &g);

	// Added functions
	bool findPathRecursive(graph &g, int curr, int end);
	void findPathNonRecursive(graph &g, int start, int end);
	void clearFoundPath() { foundPath = false; }
	void clearPath() { path.clear(); }
	void printPath();
	vector<int> getNeighbors(int id, graph &g);

	bool findShortestPath1(graph &g, int start, int end);	// DFS
	bool findShortestPath2(graph &g, int start, int end);	// BFS

private:
	int rows;		// number of rows in the maze
	int cols;		// number of columns in the maze

	matrix<bool> value;

	// Added members
	matrix<int> mapM;
	vector<pair<int,int>> nodeVect;
	vector<int> path;
	bool foundPath;
};

void maze::setMap(int i, int j, int n)
	// Set mapping from maze cell (i,j) to graph node n. 
{
	mapM[i][j] = n;
	nodeVect[n].first = i; 
	nodeVect[n].second = j;
} // setMap

int maze ::getMap(int i, int j) const
	// Return mapping of maze cell (i,j) in the graph.
{
	return mapM[i][j];
} // getMap

int maze ::getReverseMapI(int n) const
	// Return reverse mapping of node n to it's maze i value.
{
	return nodeVect[n].first;
} // getReverseMapI

int maze ::getReverseMapJ(int n) const
	// Return reverse mapping of node n to it's maze j value.
{
	return nodeVect[n].second;
} // getReverseMapJ

maze::maze(ifstream &fin)
	// Initializes a maze by reading values from fin.  Assumes that the
	// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;

	char x;

	value.resize(rows, cols);
	mapM.resize(rows, cols);
	nodeVect.resize(rows * cols);

	for (int i = 0; i <= rows-1; i++)
	{
		for (int j = 0; j <= cols-1; j++)
		{
			fin >> x;
			if (x == 'O')
				value[i][j] = true;
			else
				value[i][j] = false;
		} // for
	} // for
} // maze constructor

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
		} // for
		cout << endl;
	} // for
	cout << endl;
} // print

bool maze::isLegal(int i, int j)
	// Return the value stored at the (i,j) entry in the maze, indicating
	// whether it is legal to occupy cell (i,j).
{
	if (i < 0 || i > rows || j < 0 || j > cols)
		throw rangeError("Bad value in maze::isLegal");

	return value[i][j];
} // isLegal

void maze::mapMazeToGraph(graph &g)
	// Create a graph g that represents the legal moves in the maze m.
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (isLegal(i, j))
			{
				int n = g.addNode();
				setMap(i, j, n);

				// check for legal nodes above (i, j)
				if (i != 0 && isLegal(i-1, j))
				{
					// add edges in both directions
					int m = getMap(i-1, j);
					g.addEdge(m, n);
					g.addEdge(n, m);
				} // if

				// check for legal nodes left of (i, j)
				if (j != 0 && isLegal(i, j-1))
				{
					// add edges in both directions
					int m = getMap(i, j-1);
					g.addEdge(m, n);
					g.addEdge(n, m);
				} // if
			} // if
		} // for
	} // for
} // mapMazeToGraph

vector<int> maze::getNeighbors(int id, graph &g)
	// finds all neighbors of the node 'id' in graph 'g'
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

bool maze::findPathRecursive(graph &g, int curr, int end)
	// looks for a path from the start cell to the goal cell using 
	// depth-first search. (Uses Recursion)
{
	if (curr == end)
	{
		foundPath = true;
		path.push_back(curr);
	}
	else
	{
		g.mark(curr);
		g.visit(curr);

		vector<int> lst = getNeighbors(curr, g);

		while (!lst.empty())
		{
			int n =  lst.back();
			lst.pop_back();

			if (!g.isVisited(n))
			{
				// recursion
				if (findPathRecursive(g, n, end)) { return true; }
			} // if

			if (foundPath)
			{
				path.push_back(curr);
				break; // nasty, but it works
			} // if
		} // while
	} // else
	return false;
} // findPathRecursive

void maze::findPathNonRecursive(graph &g, int start, int end)
	// looks for a path from the start cell to the goal cell using 
	// depth-first search. (No Recursion)
{
	// clear node marks and visits from recursive findPath call
	g.clearVisit();
	g.clearMark();

	vector<stack<int>> paths;
	stack<int> st;
	stack<edge> edges;
	stack<int> pathS;

	st.push(start);

	// find the path
	while (!st.empty())
	{
		int top = st.top();
		// make sure we don't get stuck
		while (!edges.empty() && pathS.top() != edges.top().getSource())
		{
			pathS.pop();
		}

		pathS.push(top);
		if (!edges.empty())
		{
			edges.pop();
		}
		st.pop();
		g.visit(top);
		if (top == end)
		{   
			paths.push_back(pathS);
		}
		vector<int> lst = getNeighbors(top, g);
		for (int i = 0; i < lst.size(); i++)
		{
			if (!g.isVisited(lst[i]))
			{
				st.push(lst[i]);
				edges.push(g.getEdge(top, lst[i]));
			} // if
		} // for
	} // while

	// extract the path
	stack<int> reverse_path;
	for(int i = 0; i < paths.size(); i++)
	{
		if (paths[i].size() > reverse_path.size())
		{
			reverse_path = paths[i];
		}
	} // for

	// push values into vector for printing
	while (!reverse_path.empty())
	{
		int top = reverse_path.top();
		reverse_path.pop();
		if (g.isVisited(top))
		{
			path.push_back(top);
		}
	} // for
} // findPathNonRecursive

void maze::printPath()
	// print the path through the maze
{
	if (path.empty())
	{
		cout << "No path exists." << endl;
	}
	else
	{
		int curr;
		int prev = 0;
		int ip, jp, i, j;
		int count = 0;

		while (!path.empty())
		{
			count++;
			curr = path.back();

			ip = getReverseMapI(prev);	// previous i 
			jp = getReverseMapJ(prev);	// previous j
			i = getReverseMapI(curr);	// current i
			j = getReverseMapJ(curr);	// current j

			if (ip < i) { cout << "Go Down" << endl; }
			else if (ip > i) { cout << "Go Up" << endl; }
			else if (jp < j) { cout << "Go Right" << endl; }
			else if (jp > j) { cout << "Go Left" << endl; }

			print(rows-1, cols-1, i, j);

			path.pop_back();
			prev = curr;
		} // while
		cout << "Path length: " << count << endl;
	} // else
} // printPath

bool maze::findShortestPath1(graph &g, int start, int end)
	// Uses DFS to find the shortest path in the maze
{
	// clear node marks and visits
	g.clearVisit();
	g.clearMark();

	vector<stack<int>> paths;
	stack<int> st;
	stack<edge> edges;
	stack<int> pathS;

	st.push(start);

	// find the path
	while (!st.empty())
	{
		int top = st.top();

		// make sure we don't get stuck
		while (!edges.empty() && pathS.top() != edges.top().getSource())
		{
			pathS.pop();
		}

		pathS.push(top);

		if (!edges.empty())
		{
			edges.pop();
		}

		st.pop();
		g.visit(top);

		if (top == end)
		{   
			paths.push_back(pathS);
		}

		vector<int> lst = getNeighbors(top, g);

		for (int i = 0; i < lst.size(); i++)
		{
			if (!g.isVisited(lst[i]))
			{
				st.push(lst[i]);
				edges.push(g.getEdge(top, lst[i]));
			} // if
		} // for
	} // while

	// extract the path
	stack<int> reverse_path;

	for (int i = 0; i < paths.size(); i++)
	{
		if (paths[i].size() > reverse_path.size())
		{
			reverse_path = paths[i];
		}
	} // for

	// push values into vector for printing
	while (!reverse_path.empty())
	{
		int top = reverse_path.top();
		reverse_path.pop();

		if (g.isVisited(top))
		{
			path.push_back(top);
		}
	} // while

	if (path.empty()) { return false; }
	else { return true;}
} // findShortestPath1

bool maze::findShortestPath2(graph &g, int start, int end)
	// Uses BFS to find the shortest path in the maze
{
	// clear path
	clearPath();

	// clear node marks and visits
	g.clearVisit();
	g.clearMark();

	queue<int> q;
	stack<int> pathS;
	map<int,int> edges;
	q.push(start);
	bool found = false;

	while (!q.empty())
	{
		int top = q.front();
		q.pop();

		if (top == end)
		{
			found = true;
			pathS.push(end);
			break;
		}

		g.visit(top);

		vector<int> lst = getNeighbors(top, g);

		for (int i = 0; i < lst.size(); i++)
		{
			if (!g.isVisited(lst[i]))
			{
				q.push(lst[i]);
				edges.insert(pair<int,int>(lst[i], top));
			}
		} // for
	} // while

	// start backtracking
	int curr = end;

	while (found && curr != start)
	{
		curr = edges.find(curr)->second;
		pathS.push(curr);
	} // while
	
    // push values into vector for printing
	vector<int> revPath;

	while (!pathS.empty())
	{
		int top = pathS.top();
		pathS.pop();

		if (g.isVisited(top))
		{
			revPath.push_back(top);
		}
	} // while

	// reverse path
	path.push_back(getMap(rows-1, cols-1));
	for (int i = revPath.size(); i > 0; i--)
	{
		path.push_back(revPath.back());
		revPath.pop_back();
	} // for

	if (path.empty()) { return false; }
	else { return true;}
} // findShortestPath2


// MAIN FUNCTION
int main()
{
	ifstream fin;

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
			m.mapMazeToGraph(g);

			int start = m.getMap(0, 0);
			int goal = m.getMap(m.numRows()-1, m.numCols()-1);

			// findShortestPath1
			if (m.findShortestPath1(g, start, goal)) { m.printPath(); }
			else { cout << "No path found." << endl; }

			cout << "\n|||||||||||||||||||||||||||||\n" << endl;

			// findShortestPath2
			if (m.findShortestPath2(g, start, goal)) { m.printPath(); }
			else { cout << "No path found." << endl; }
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
