#include "solveSudokuPuzzle.h"

//Hold some constant row, and go through all of the columns checking if the value
//has been used in any of the columns for that row.
bool solveSudokuPuzzle::isRowOkay(int rowToCheck, int valueToCheck, sudokuPuzzle &puzzle)
{
	for (int i = 0; i < puzzle.getLength(); i++)
	{
		if (puzzle.getValue(rowToCheck, i) == valueToCheck)
		{
			return false;
		}
	}
	return true;
}

//Hold some constant column, and go through all of the rows checking if the value
//has been used in any of the rows for that column.
bool solveSudokuPuzzle::isColumnOkay(int columnToCheck, int valueToCheck, sudokuPuzzle &puzzle)
{
	for (int i = 0; i < puzzle.getLength(); i++)
	{
		if (puzzle.getValue(i, columnToCheck) == valueToCheck)
		{
			return false;
		}
	}
	return true;
}

bool solveSudokuPuzzle::isSquareOkay(int rowOfValueToCheck, int colOfValueToCheck,
	int valueToCheck, sudokuPuzzle &puzzle)
{
	int tempRow = rowOfValueToCheck;
	int tempCol = colOfValueToCheck;
	bool isFirstCheckRow = true;
	bool isFirstCheckCol = true;

	//First correct the starting position so that it adjusts to the start of the
	//input values respective box.
	while ((rowOfValueToCheck % static_cast<int>(sqrt(puzzle.getLength()))) != 0)
	{
		rowOfValueToCheck--;
	}

	while ((colOfValueToCheck % static_cast<int>(sqrt(puzzle.getLength()))) != 0)
	{
		colOfValueToCheck--;
	}

	//Now check from the starting position up to some modulus value of the total
	//length or width of the puzzle.  So if the puzzle is 9 by 9, and the starting
	//value is 4, then it will loop up to 6 and then go to the next row down.
	while (((rowOfValueToCheck % static_cast<int>(sqrt(puzzle.getLength()))) != 0) || isFirstCheckRow)
	{
		while (((colOfValueToCheck % static_cast<int>(sqrt(puzzle.getLength()))) != 0) || isFirstCheckCol)
		{
			if (puzzle.getValue(rowOfValueToCheck, colOfValueToCheck) == valueToCheck)
			{
				return false;
			}
			colOfValueToCheck++;
			isFirstCheckCol = false;
		}
		colOfValueToCheck = tempCol;
		rowOfValueToCheck++;
		isFirstCheckRow = false;
		isFirstCheckCol = true;
	}
	return true;
}

//Check that every constraint passes.  There are only three constraints 
bool solveSudokuPuzzle::checkConstraints(int row, int col, int valueToCheck,
	sudokuPuzzle &puzzle)
{
	if ((solveSudokuPuzzle::isRowOkay(row, valueToCheck, puzzle))
		&& (solveSudokuPuzzle::isSquareOkay(row, col, valueToCheck, puzzle))
		&& (solveSudokuPuzzle::isColumnOkay(col, valueToCheck, puzzle)))
	{
		return true;
	} else
	{
		return false;
	}
}

//The backtracking search is the algorithm used to solve the sudoku puzzles.
//The algorithm was given in class.
bool solveSudokuPuzzle::sudokuBacktrackingSearch(int row, int col,
	sudokuPuzzle& puzzle)
{
	//IF the whole Sudoku puzzle is full, then return true
	//and break the recursion.
	if (findPositionForAssignmentCompletion(row, col, puzzle))
	{
		return true;
	}
	//We choose some unassigned variable, but since our domain is just the values
	//from 1 to 9 we can just loop through and check to see if that number matches
	//the constraint

	//Choose the position given back (by reference from
	//findPositionForAssignmentCompletion), and then use 
	//this to complete the assignment.
	else
	{
		for (int variableToAssign = 1;
			variableToAssign <= puzzle.getLength(); variableToAssign++)
		{
			//If the value matches the constraints then 
			if (solveSudokuPuzzle::checkConstraints(row, col, variableToAssign, puzzle))
			{
				//Add value and variable into assignment, 
				//then call backtracking search again.
				puzzle.assign(row, col, variableToAssign);
				if (sudokuBacktrackingSearch(row, col, puzzle))
				{
					return true;
				}
				//Reset the value to nothing
				//so that backtracking can occur, so that a new value
				//can to be assigned to that position.
				puzzle.assign(row, col, 0);
			}
		}
	}
	//Return a failure. 
	return false;
}

//We need a helper function to determine the next variable that
//should be assigned a value from the domain.
bool solveSudokuPuzzle::findPositionForAssignmentCompletion(int & row, int & column,
	sudokuPuzzle & puzzle)
{
	for (int rowCheckValue = 0; rowCheckValue < puzzle.getLength(); rowCheckValue++)
	{
		for (int colCheckValue = 0; colCheckValue < puzzle.getLength(); colCheckValue++)
		{
			row = rowCheckValue;
			column = colCheckValue;
			if (puzzle.getValue(rowCheckValue, colCheckValue) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

//Just a function to loop through and print out the solution that was found.
void solveSudokuPuzzle::printSolutionToPuzzle(sudokuPuzzle &puzzle)
{
	std::cout << "Solution to puzzle:\n";
	std::cout << "-------------------\n\n";
	for (int i = 0; i < puzzle.getLength(); i++)
	{
		for (int j = 0; j < puzzle.getLength(); j++)
		{
			std::cout << puzzle.getValue(i, j) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

std::vector<sudokuPuzzle> solveSudokuPuzzle::readPuzzlesFromTextFile(std::string inputFile)
{
	int puzzleValue;

	std::ifstream fileStream;
	std::string lineToGet;

	std::vector<std::vector<int>> tempPuzzle;
	std::vector<std::vector<std::vector<int>>> vectorOfTempPuzzles;
	std::vector<sudokuPuzzle> puzzlesToReturn;

	fileStream.open(inputFile);
	if (fileStream.fail())
	{
		std::cerr << "File does not exist, try again!\n";
		std::exit(1);
	}

	while (fileStream.good())
	{
		while (getline(fileStream, lineToGet))
		{
			std::vector<int> row;
			std::istringstream inputStringStream(lineToGet);
			if (!(lineToGet == "" || lineToGet == "\n"))
			{
				while (inputStringStream >> puzzleValue)
				{
					row.push_back(puzzleValue);
				}
				tempPuzzle.push_back(row);
			}
			else
			{
				vectorOfTempPuzzles.push_back(tempPuzzle);
				tempPuzzle.clear();
			}
		}
		if (tempPuzzle.size() > 1)
		{
			vectorOfTempPuzzles.push_back(tempPuzzle);
			tempPuzzle.clear();
		}
	}

	for (unsigned int numberOfPuzzles = 0; numberOfPuzzles <
		vectorOfTempPuzzles.size(); numberOfPuzzles++)
	{
		sudokuPuzzle puzzle(vectorOfTempPuzzles.at(numberOfPuzzles).size());
		tempPuzzle = vectorOfTempPuzzles.at(numberOfPuzzles);

		for (unsigned int i = 0; i < tempPuzzle.size(); i++)
		{
			if (tempPuzzle.size() == tempPuzzle.at(i).size())
			{
				for (unsigned int j = 0; j < tempPuzzle.at(i).size(); j++)
				{
					puzzle.assign(i, j, tempPuzzle[i][j]);
				}
			} 
			else
			{
				std::cerr << "An incorrect Sudoku Puzzle was inputted, try again.";
				std::exit(1);
			}
		}
		tempPuzzle.clear();
		puzzlesToReturn.push_back(puzzle);
	}

	
	return puzzlesToReturn;
}