#include "sudokuPuzzle.h"

int sudokuPuzzle::getLength() const
{
	return length;
}

int sudokuPuzzle::getValue(int row, int column) const
{
	return twoDimensionalArray[row][column];
}

sudokuPuzzle::sudokuPuzzle(const sudokuPuzzle & toBeCopied)     // Copy Constructor
{
	length = toBeCopied.getLength();
	twoDimensionalArray = new int*[length];
	for (int i = 0; i < toBeCopied.getLength(); i++)
	{
		twoDimensionalArray[i] = new int[length];
		for (int j = 0; j < toBeCopied.getLength(); j++)
		{
			twoDimensionalArray[i][j] = toBeCopied.getValue(i, j);
		}
	}
}

sudokuPuzzle& sudokuPuzzle::operator=(const sudokuPuzzle &rightPuzzle)
{
	length = rightPuzzle.getLength();
	twoDimensionalArray = new int*[length];
	for (int i = 0; i < length; i++)
	{
		twoDimensionalArray[i] = new int[length];
		for (int j = 0; j < length; j++)
		{
			twoDimensionalArray[i][j] = rightPuzzle.getValue(i, j);
		}
	}
	return *this;
}

sudokuPuzzle::sudokuPuzzle(int l)
{
	length = l;
	twoDimensionalArray = new int*[length];
	for (int i = 0; i < length; i++)
	{
		twoDimensionalArray[i] = new int[length];
		for (int j = 0; j < length; j++)
		{
			twoDimensionalArray[i][j] = 0;
		}
	}
}

sudokuPuzzle::~sudokuPuzzle()
{//deleteing memory to prevent memory leak
	for (int i = 0; i < length; ++i)
		delete[] twoDimensionalArray[i];

	delete[] twoDimensionalArray;
}

void sudokuPuzzle::assign(int row, int col, int value)
{
	twoDimensionalArray[row][col] = value;
}