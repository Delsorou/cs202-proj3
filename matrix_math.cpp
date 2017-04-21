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
#include <vector>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	std::fstream file("A.mtx", std::ios::in | std::ios::out);
	Matrix_ops<int> read_buffer;
	file >> read_buffer;

	std::vector<Matrix_ops<int>> test_bed(10, read_buffer );

	std::cout << "Demonstrate addition and addition assignment\n";
	std::cout << test_bed[0] + test_bed[1];
	test_bed[0] += test_bed[1];
	std::cout << test_bed[0];
	std::cout << "Demonstrate subtraction and subtraction assignment\n";
	std::cout << test_bed[1] - test_bed[2];
	test_bed[1] -= test_bed[2];
	std::cout << test_bed[1];
	std::cout << "Demonstrate multiplication and multiplication assignment\n";
	std::cout << test_bed[2] * test_bed[3];
	test_bed[2] *= test_bed[3];
	std::cout << test_bed[2];
	std::cout << test_bed[2].trans();
	std::cout << "Demonstrate equality and inequality\n";
	std::cout << std::boolalpha << (test_bed[0] == test_bed[1]) << std::endl
		<< (test_bed[0] != test_bed[1]);
	file.close();

	return 0;
}
