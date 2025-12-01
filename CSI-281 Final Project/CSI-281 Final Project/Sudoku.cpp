/*Author : Nicholas Robertson
* Title  : Sudoku Generator/Solver
* Date   : 11/30/2025
*
* Description:
*	This code is intended to be used to generate and/or solve Sudoku puzzles.
*/

#include <fstream>
#include <iostream>
#include "Sudoku.h"

using namespace std;

//constructors
Sudoku::Sudoku() 
{
	srand(time(NULL));
	generate();
}

//functions

bool Sudoku::check(int board[9][9], int row, int column, int number) 
{
	if (checkBlock(board, row - (row % 3), column - (column % 3), number) == true)
		if (checkPosition(board, row, column, number) == true)
				return true;//This means that the number doesnt exist within the block
	return false; //This means that the number already exists within the block
}

bool Sudoku::checkPosition(int board[9][9], int row, int column, int number)
{
	for (int i = 0; i < 9; i++)
	{
		if (board[row][i] == number)
			return false; //This means that the number already exists within the block
	}
	for (int i = 0; i < 9; i++) 
	{
		if (board[i][column] == number)
			return false; //This means that the number already exists within the block
	}
	return true; //This means that the number doesnt exist within the block
}

bool Sudoku::checkBlock(int board[9][9], int row, int column, int number)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (board[row + i][column + j] == number)
				return false; //This means that the number already exists within the block
		}
	return true; //This means that the number doesnt exist within the block
}

void Sudoku::exportSudoku(string fileName)
{
	ofstream fout;
	fout.open(fileName);
	if (!fout) 
	{
		cout << "the file failed to open." << endl;
		return;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fout << sudokuBoard[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();
}

bool Sudoku::fillAll(int row, int column) 
{
	if (row == 9)
		return true;
	if (column == 9)
		return fillAll(row + 1, 0);
	if (sudokuBoard[row][column] != 0)
		return fillAll(row, column + 1);
	for (int i = 1; i < 10; i++) 
	{
		if (check(sudokuBoard, row, column, i) == true) 
		{
			sudokuBoard[row][column] = i;
			if (fillAll(row, column + 1) == true) 
			{
				return true;
			}
			sudokuBoard[row][column] = 0;
		}
	}
	return false;
}

void Sudoku::fillBlock(int row, int column)
{
	int tempNum;
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) 
		{
			while (sudokuBoard[row + i][column + j] == 0)
			{
				tempNum = (rand() % 9) + 1;
				if (checkBlock(sudokuBoard, row, column, tempNum) == true)
					sudokuBoard[row + i][column + j] = tempNum;
			}

		}
}

void Sudoku::fillEmpty()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			sudokuBoard[i][j] = 0;
}

void Sudoku::generate()
{
	int diff = 0;
	string tempString;
	bool tempBool = false;

	while (tempString != "y" && tempString != "n")
	{
		cout << "would you like to import a puzzle? (y/n): ";
		cin >> tempString;
		cout << tempString << endl;
		if (tempString != "y" && tempString != "n") cout << "please enter 'y' or 'n'" << endl;
	}
	if (tempString == "y")
	{
		while (tempBool == false)
		{
			cout << "enter the name you would to export the file as: ";
			cin >> tempString;
			tempBool = import(tempString);
			if (tempString == "exit") 
			{
				tempBool = true;
				tempString = "n";
			}
			if (tempBool == false) cout << "The fileName you entered was not found. if no files exist, enter exit to generate a new Sudoku, otherwise please try again." << endl;
		}
		imported = true;
		
	}
	if (tempString == "n")
	{
		fillEmpty();
		print();
		for (int i = 0; i < 9; i = i + 3)
		{
			fillBlock(i, i);
			print();
		}
		fillAll(0, 0);
		print();
		while (diff > 3 || diff < 1)
		{
			cout << "Please enter the level of difficulty" << endl
				<< "1. Easy (30)" << endl
				<< "2. Normal (40)" << endl
				<< "3. Hard (50)" << endl;
			cin >> diff;
			if (diff > 3 || diff < 1)
				cout << "Please enter the number of one of the given options." << endl;
		}
		remove(sudokuBoard, diff);
		imported = false;
	}
	print();
}

bool Sudoku::hasUniqueSolution(int board[9][9]) {
	int solutionCount = 0;
	solveCount(board, solutionCount, 0, 0);
	return solutionCount == 1;
}

bool Sudoku::import(string fileName)
{
	ifstream fin;
	fin.open(fileName);
	if (!fin) return false;
	for(int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) 
		{
			fin >> sudokuBoard[i][j];
		}

	fin.close();
	return true;
}

void Sudoku::print()
{
	cout << "-------------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "| ";
		for (int j = 0; j < 9; j++) 
		{
			cout << sudokuBoard[i][j] << " ";
			if (j % 3 == 2) cout << "| ";
		}
		cout << endl;
		if (i % 3 == 2) cout << "-------------------------" << endl;
	}
	cout << endl;
}

void Sudoku::remove(int board[9][9], int diff)
{
	int tempNum1, tempNum2, tempInt;
	bool tempBool;
	switch (diff) 
	{
	case 1: diff = 30;
		break;
	case 2: diff = 40;
		break;
	case 3: diff = 50;
		break;
	default: cout << "THIS IS AN ERROR MESSAGE, THIS SHOULD NOT APPEAR, REPORT THIS." << endl;
		return;
		break;
	}
	while (diff != 0)
	{
		tempBool = false;
		while (tempBool == false)
		{
			tempNum1 = (rand() % 9);
			tempNum2 = (rand() % 9);
			if (board[tempNum1][tempNum2] != 0)
			{
				tempInt = board[tempNum1][tempNum2];
				board[tempNum1][tempNum2] = 0;
				tempBool = true;
			}
		}
		tempBool = hasUniqueSolution(board);
		if (tempBool)
		{
			sudokuBoard[tempNum1][tempNum2] = 0;
			diff--;
		}
		else if (!tempBool) 
		{
			board[tempNum1][tempNum2] = tempInt;
		}
	}
	return;

}

bool Sudoku::solve(int board[9][9], int row, int column)
{
	if (row == 9)
	{
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					sudokuBoard[i][j] = board[i][j];
		return true;
	}
	if (column == 9)
		return solve(board, row + 1, 0);
	if (board[row][column] != 0)
		return solve(board, row, column + 1);
	for (int i = 1; i < 10; i++)
	{
		if (check(board, row, column, i) == true)
		{
			board[row][column] = i;
			if (solve(board, row, column + 1) == true)
			{
				return true;
			}
			board[row][column] = 0;
		}
	}
	return false;
}

void Sudoku::solveCount(int board[9][9], int& count, int row, int column) 
{
	if (row == 9)
	{
		count++;
		return;
	}
	if (column == 9) 
	{
		solveCount(board, count, row + 1, 0);
		return;
	}
	if (board[row][column] != 0)
	{
		solveCount(board, count, row, column + 1);
		return;
	}
	for (int i = 1; i < 10; i++)
	{
		if (check(board, row, column, i) == true)
		{
			board[row][column] = i;
			solveCount(board, count, row, column + 1);
			board[row][column] = 0;
			if (count > 1) return;
		}
	}
	return;
}