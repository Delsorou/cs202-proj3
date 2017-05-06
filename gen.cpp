/* -----------------------------------------------------------------------------

FILE:              gen.cpp

DESCRIPTION:       A simple generator for matrices to test with

COMPILER:          gcc 5.4.0

NOTES:             Requires three arguments: [rows] [columns] [filename]
                   does NOT validate input, dev utility, use with caution

VERSION:           0.1

----------------------------------------------------------------------------- */

#include <fstream>
#include "Matrix.h"
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
	if (argc != 4)
	{
		std::cout << "Requires args: [rows] [columns] [filename]\n";
		return 0;
	}
	
	std::size_t row = std::size_t(atoi(argv[1]));
	std::size_t col = std::size_t(atoi(argv[2]));
	std::srand(std::time(0));
	Matrix<int> Q(row, col);

	for (std::size_t i = 0; i < row; ++i)
	{
		for (std::size_t j = 0; j < col; ++j)
		{
			Q.setElm(i, j, rand() % 10 + 1);
		}
	}

	std::ofstream file(strcat(argv[3],".mtx"));

	file << Q;

	return 0;
}
