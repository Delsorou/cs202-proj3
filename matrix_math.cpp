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
//	int m, n;
	std::ifstream file("A.mtx");

//	std::cout << "Input rows and cols: ";
//	std::cin >> m >> n;
//	std::cout << std::endl;

//	Matrix<int> mat1(m, n);
	Matrix<int> mat1;

//	for (int i = 0; i < m; ++i)
//	{
//		mat1.set(i, i % n, i + 1);
//	}

	file >> mat1;
	std::cout << mat1;

	return 0;
}
