/*Author : Nicholas Robertson
* Title  : Sudoku Generator/Solver
* Date   : 11/30/2025
*
* Description:
*	This code is intended to be used to generate and/or solve Sudoku puzzles.
*/

#include <iostream>

#ifndef SUDOKU_H
#define SUDOKU_H

using namespace std;

class Sudoku
{
protected:


public:
	//variables
	
	int sudokuBoard[9][9];
	bool imported;

	//constructors
	Sudoku();

	//functions
	bool check(int board[9][9], int row, int column, int number);
	bool checkPosition(int board[9][9], int row, int column, int number);
	bool checkBlock(int board[9][9], int row, int column, int number);
	void exportSudoku(string fileName);
	bool fillAll(int row, int column);
	void fillBlock(int row, int column);
	void fillEmpty();
	void generate();
	bool hasUniqueSolution(int board[9][9]);
	bool import(string fileName);
	void print();
	void remove(int board[9][9], int amount);
	bool solve(int board[9][9], int row, int column);
	void solveCount(int board[9][9], int& count, int row, int column);
};

#endif