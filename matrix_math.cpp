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

	Matrix<int> mat1;
	Matrix<int> mat2;

	file >> mat1;
	std::cout << mat1 << std::endl << " 1 OK\n";
	// This demonstrates move assignment - assign any matrix with six
	// assignment operations
	mat2 = static_cast<Matrix<int>&&>(mat1);
	std::cout << mat2 << std::endl << " 2 OK\n";

	file.close();

	return 0;
}
