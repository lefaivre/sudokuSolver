#include "solveSudokuPuzzle.h"

int main()
{
	int row = 0;
	int column = 0;
	sudokuPuzzle puzzle(0);
	std::vector<sudokuPuzzle> vectorOfPuzzles;
	

	vectorOfPuzzles = solveSudokuPuzzle::readPuzzlesFromTextFile("testPuzzle.txt");
	for (unsigned int i = 0; i < vectorOfPuzzles.size(); i++)
	{
		puzzle = vectorOfPuzzles.at(i);
		if (solveSudokuPuzzle::sudokuBacktrackingSearch(row, column, puzzle))
		{
			solveSudokuPuzzle::printSolutionToPuzzle(puzzle);
		}
		else
		{
			std::cout << "A solution was not found for puzzle number: " << i;
		}
	}
	

	return 0;
}