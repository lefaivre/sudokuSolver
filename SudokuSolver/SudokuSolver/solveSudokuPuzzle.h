#include "sudokuPuzzle.h"

namespace solveSudokuPuzzle
{
	bool isRowOkay(int, int, sudokuPuzzle&);
	bool isColumnOkay(int, int, sudokuPuzzle&);
	bool isSquareOkay(int, int, int, sudokuPuzzle&);
	bool checkConstraints(int, int, int, sudokuPuzzle&);
	bool sudokuBacktrackingSearch(int, int, sudokuPuzzle&);
	bool findPositionForAssignmentCompletion(int&, int&, sudokuPuzzle&);
	void printSolutionToPuzzle(sudokuPuzzle&);
	std::vector<sudokuPuzzle> readPuzzlesFromTextFile(std::string);
};