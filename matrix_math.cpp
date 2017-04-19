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
	std::fstream file("A.mtx", std::ios::in | std::ios::out);

	Matrix_ops<int> mat1;
	Matrix_ops<int> mat2;

	file >> mat1;
	mat2 = mat1;
	mat1 += mat2;

	std::cout << mat1 << std::endl << " 1 OK\n";
	std::cout << mat2 << std::endl << " 2 OK\n";

	file.close();

	return 0;
}
