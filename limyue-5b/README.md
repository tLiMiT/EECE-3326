EECE-3326
=========

Northeastern University

EECE3326 - Optimization Methods

Prof. Waleed Meleis

Project #5

Part b

A shortest path in a maze is a path from the start to the goal with the smallest number of
steps. Write two functions findShortestPath1 and findShortestPath2 that each find a
shortest path in a maze if a path from the start to the goal exists.

The first algorithm should use a depth-first search and the second algorithm should use a
breadth-first search.

In each case, if a solution exists the solver should simulate the solution to each maze by
calling the maze::print() function after each move.

Each function should return true if any paths are found, and false otherwise.