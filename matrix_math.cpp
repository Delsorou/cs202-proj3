/* -----------------------------------------------------------------------------

FILE:              matrix_math.cpp

DESCRIPTION:       Driver for testing the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             None

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Aaryna Irwin            2017-04-11         0.1

----------------------------------------------------------------------------- */

#include <fstream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	std::ifstream inputFile("A.mtx");

	Matrix<int> mat1(1, 1);

	if (inputFile)
	{
		inputFile >> mat1;
		std::cout << mat1;
		inputFile.close();
	}
	else
		std::cout << "File failed to open...";

	return 0;
}
