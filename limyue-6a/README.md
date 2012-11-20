EECE-3326
=========

Northeastern University

EECE3326 - Optimization Methods

Prof. Waleed Meleis

Project #6

For this project, you are the Minister of Transportation for an island nation. The only way to get
from one island to another is by boat, which is very slow. You believe that the nation's economy
will be improved if there is a quick way to travel from island to island. Your plan is to build a
collection of bridges that let people easily get from island to island.

However, the cost to build a bridge between two islands varies, and not all islands can be directly
connected by a bridge. An engineering survey has been done to determine all pairs of islands that
can be connected by a bridge, and the cost to build each bridge.

Because the nation is democratic, it is important that the network of bridges allows travel between
as many pairs of islands as possible. However, it is not necessary that every pair of islands be
directly connected.

Given a set of islands, a set of potential bridges, and a cost for each potential bridge, your goal is
to select the bridges to build such that it is possible to travel between as many islands as possible,
and the cost of the bridges is minimized.


Part a

A legal solution to the transportation problem is a network of bridges that allows travel
between as many pairs of islands as possible, and which does not create any cycles. Note
that the cost of a legal solution is not necessarily minimized.

Write the following functions:

   void findSpanningForest(graph &g1, graph &sf)
   // Create a graph sf that contains a spanning forest on the graph g.

   bool isConnected(graph &g)
   // Returns true if the graph g is connected. Otherwise returns false.

   bool isCyclic(graph &g)
   // Returns true if the graph g contains a cycle. Otherwise, returns false.

Functions to read a set of edges and weights from a file are included as part of the assignment.
Several input files are also included. Each input file begins with a number of nodes, a number
of edges, and a list of undirected edges and edge weights.