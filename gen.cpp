/* -----------------------------------------------------------------------------

FILE:              gen.cpp

DESCRIPTION:       A simple generator for matrices to test with

COMPILER:          gcc 5.4.0

NOTES:             Requires three arguments: [rows] [columns] [filename]
                   does NOT validate input, dev utility, use with caution

VERSION:           0.2

----------------------------------------------------------------------------- */

// This sets the upper limit for matrix elements (from zero to this value)
#define U_LIM 10

#include "Matrix.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

/* -----------------------------------------------------------------------------
FUNCTION:          main(int argc, char* argv[])
DESCRIPTION:       Generates matrices of specced filename
RETURNS:           int
NOTES:             Requires exactly three cmdln args, no more, no less
----------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
	// Guide the user...
	if (argc != 4)
	{
		std::cout << "Requires args: [rows] [columns] [filename]\n";
		return 0;
	}
	
	// Seed rng
	std::srand(std::time(0));
	
	// Parse input arguments as integers and create that size matrix
	std::size_t row = std::size_t(atoi(argv[1]));
	std::size_t col = std::size_t(atoi(argv[2]));
	Matrix<int> Q(row, col);

	// Create a matrix of the provided width and height
	for (std::size_t i = 0; i < row; ++i)
	{
		for (std::size_t j = 0; j < col; ++j)
			Q.setElm(i, j, rand() % U_LIM);
	}

	// Create an output file and store the matrix in it
	std::ofstream file(strcat(argv[3],".mtx"));
	file << Q;
	file.close();

	return 0;
}
