#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

class sudokuPuzzle
{
private:
	int length;
	int **twoDimensionalArray;

public:
	sudokuPuzzle(int);
	~sudokuPuzzle();
	void assign(int, int, int);
	int getLength() const;
	int getValue(int, int) const;
	sudokuPuzzle & operator=(const sudokuPuzzle &);
	sudokuPuzzle(const sudokuPuzzle &);
};