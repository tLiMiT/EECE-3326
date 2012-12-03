EECE-3326
=========

Northeastern University

EECE3326 - Optimization Methods

Prof. Waleed Meleis

Part b

Complete the project by writing the following function

    void prim(graph &g, graph &sf)
    // Given a weighted graph g, sets sf equal to a minimum spanning
    // forest on g. Uses Prim's algorithm.

Apply the function to the input file graph4.txt included with the assignment to find a set
of bridges to build that connect the islands as cheaply as possible. Print out the bridges
built, the total cost of your solution, and the number of connected components.

Also print out the improvement in the cost of your solution compared with the cost of the
spanning forest found by findSpanningForest.