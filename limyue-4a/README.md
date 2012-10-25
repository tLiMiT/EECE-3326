EECE-3326
=========

Northeastern University

EECE3326 - Optimization Methods

Prof. Waleed Meleis

Project #4
Write a program that solves Sudoku puzzles. The input to Sudoku is a 9x9 board that is subdivided
into 3x3 squares. Each cell is either blank or contains an integer from 1 to 9.
A solution to a puzzle is the same board with every blank cell filled in with a digit from 1 to 9 such
that every digit appears exactly once in every row, column, and square.
The input to the program is a text file containing a collection of Sudoku boards, with one board
per line. For each board that is read, the output is a printout of the board correctly filled in.
Part a
Some of the declarations and denitions for the board class are given to you. Add functions
to the class that:
1. initialize the board, and update conicts,
2. print the board and the conicts to the screen,
3. check whether a value causes conicts if it is placed in a cell,
4. add a value to a cell, and update conicts,
5. clear a cell, and update conicts, and
6. check to see if the board has been solved (return true or false, and print the result to
the screen)
For each row i and digit j, keep track of whether each digit j has been placed in row i. Do
the same for each column and each square. We will use this information in part b of the
project to write the Sudoku solver.
The code you submit should read each Sudoku board from the file one-by-one, print the
board and conicts to the screen, and check to see if the board has been solved (all boards
will not be solved at this point).