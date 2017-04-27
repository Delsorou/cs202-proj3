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

#include <cstring>
#include <fstream>
#include "Matrix.h"

template <class T>
int read_matrix(Matrix<T>& mat1, int argc, char arg[]);

template <class T>
int write_matrix(char file2[], Matrix<T>& mat);

int read_file2(char file2[], int argc, char arg[]);

/* -----------------------------------------------------------------------------
FUNCTION:          main(int, char**)
DESCRIPTION:       The longer you wait, the harder it gets...
RETURNS:           int
NOTES:             None
----------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
	int err;
	char file2[20] = "";
	Matrix<int> mat1, mat2, mat3;

	while (--argc)
	{
		++argv;
		std::cout << "argc = " << argc << "  " << *argv << std::endl;

		if (strcmp(*argv, "-inp") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
		}

		if (strcmp(*argv, "-out") == 0)
		{
			err = read_file2(file2, --argc, *++argv);
			if (err) return err;
		}

		if (strcmp(*argv, "-add") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
			err = read_matrix(mat2, --argc, *++argv);
			if (err) return err;
		}
	}

	std::cout << "Input test:  " << std::endl;
	std::cout << mat1 << mat2;

	std::cout << "Assignment test:  " << std::endl;
	mat2 = mat1;
	std::cout << mat2;

	std::cout << "Copy constructor test:  " << std::endl;
	Matrix<int> mat4(mat2);
	std::cout << mat4;
	
	if (*file2) write_matrix(file2, mat4);

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          read_matrix(int, char**)
DESCRIPTION:       The longer you wait, the harder it gets...
RETURNS:           int
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
int read_matrix(Matrix<T>& mat1, int argc, char arg[])
{
	char file1[20];
	std::ifstream infile;

	if (argc < 1)
	{
		std::cout << "Not enough arguments ?\n\n";
		return 1;
	}
	strcpy(file1, arg);
	strcat(file1, ".mtx");

	infile.open(file1);

	if (!infile)
	{
		std::cout << "\nError opening file: " << file1 << "\n\n";
		return 1;
	}

	infile >> mat1;
	infile.close();

	std::cout << std::endl;

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          read_file2(int, char**)
DESCRIPTION:       The longer you wait, the harder it gets...
RETURNS:           int
NOTES:             None
----------------------------------------------------------------------------- */
int read_file2(char file2[], int argc, char arg[])
{
	if (argc < 1)
	{
		std::cout << "Not enough Arguments ?\n\n";
		return -1;
	}

	strcpy(file2, arg);
	strcat(file2, ".mtx");

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          read_file2(int, char**)
DESCRIPTION:       The longer you wait, the harder it gets...
RETURNS:           int
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
int write_matrix(char file2[], Matrix<T>& mat)
{
	std::ofstream outfile;
	outfile.open(file2);

	if (!outfile)
	{
		std::cout << "\nError opening file: " << file2 << "\n\n";
		return -1;
	}

	outfile << mat;
	outfile.close();

	return 0;
}
