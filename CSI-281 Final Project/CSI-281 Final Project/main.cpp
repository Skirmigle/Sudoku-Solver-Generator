/*Author : Nicholas Robertson
* Title  : Sudoku Generator/Solver
* Date   : 11/30/2025
*
* Description:
*	This code is intended to be used to generate and/or solve Sudoku puzzles.
*/

#include <iostream>
#include "Sudoku.h"

using namespace std;

int main()
{
	string tempString;
	Sudoku sudoku;

	if (sudoku.imported == false)
	{
		while (tempString != "y" && tempString != "n")
		{
			cout << "would you like to export the puzzle? (y/n): ";
			cin >> tempString;
			cout << tempString << endl;
			if (tempString != "y" && tempString != "n") cout << "please enter 'y' or 'n'" << endl;
		}
		if (tempString == "y")
		{
			cout << "enter the name you would to export the file as: ";
			cin >> tempString;
			sudoku.exportSudoku(tempString);
		}

		tempString = "";
	}

	while (tempString != "y" && tempString != "n")
	{
		cout << "would you like to automatically solve the puzzle? (y/n): ";
		cin >> tempString;
		cout << tempString << endl;
		if (tempString != "y" && tempString != "n") cout << "please enter 'y' or 'n'" << endl;
	}
	if (tempString == "y")
	{
		sudoku.solve(sudoku.sudokuBoard, 0, 0);
		sudoku.print(sudoku.sudokuBoard);
	}
	else if (tempString == "n")
	{
		sudoku.play();
	}
}