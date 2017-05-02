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

// Function prototypes 
template <class T>
int read_matrix(Matrix<T>& mat1, int argc, char arg[]);
template <class T>
int write_matrix(char file2[], Matrix<T>& mat);
int read_file2(char file2[], int argc, char arg[]);
void display_help();

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
	Matrix_ops<int> mat1, mat2, mat3;

	while (--argc)
	{
		++argv;

		if (strcmp(*argv, "-inp") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
			std::cout << "Input:  " << std::endl;
			std::cout << mat1 << std::endl;
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

			mat3 = mat1 + mat2;
			std::cout << "Sum:  " << std::endl;
			std::cout << mat3 << std::endl;
		}
		
		if (strcmp(*argv, "-sub") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
			err = read_matrix(mat2, --argc, *++argv);
			if (err) return err;

			mat3 = mat1 - mat2;
			std::cout << "Difference:  " << std::endl;
			std::cout << mat3 << std::endl;
		}

		if (strcmp(*argv, "-mul") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
			err = read_matrix(mat2, --argc, *++argv);
			if (err) return err;

			mat3 = mat1 * mat2;
			std::cout << "Product:  " << std::endl;
			std::cout << mat3 << std::endl;
		}
		
		if (strcmp(*argv, "-eq") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;
			err = read_matrix(mat2, --argc, *++argv);
			if (err) return err;

			bool equality = mat1 == mat2;
			std::cout << "Equality:  " << std::endl;
			std::cout << std::boolalpha << equality << std::endl;
		}

		if (strcmp(*argv, "-T") == 0)
		{
			err = read_matrix(mat1, --argc, *++argv);
			if (err) return err;

			std::cout << "Transpose:  " << std::endl;
			std::cout << mat1.trans() << std::endl;
		}

//		if (strcmp(*argv, "-1") == 0)
//		{
//			err = read_matrix(mat1, --argc, *++argv);
//			if (err) return err;
//
//			std::cout << "Inverse:  " << std::endl;
//			std::cout << mat1.inv() << std::endl;
//		}
///
//		if (strcmp(*argv, "-det") == 0)
//		{
//			err = read_matrix(mat1, --argc, *++argv);
//			if (err) return err;
//
//			std::cout << "Determinant:  " << std::endl;
//			std::cout << Matrix_ops::det(mat1) << std::endl;
//		}
//
//		if (strcmp(*argv, "-solve") == 0)
//		{
//			err = read_matrix(mat1, --argc, *++argv);
//			if (err) return err;
//
//			std::cout << "Solution:  " << std::endl;
//			std::cout << mat1.solve() << std::endl;
//		}
		
		if (strcmp(*argv, "-h") == 0)
		{
			display_help();
		}
	}

	if (*file2) write_matrix(file2, mat3);

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

void display_help()
{
	using std::cout;
	using std::endl;
	cout << endl << "Matrix Math Demonstration Program...\n\n";
	cout << "Usage: matrix_math [-arg] [filename(s)] ... [-out] [filename]\n\n";
	cout << "Arguments:\n\n";
	cout << std::setw(15) << "-h" << std::setw(15) << "Display this help file\n";
	cout << std::setw(15) << "-inp" << std::setw(15) << "Display matrix\n";
	cout << std::setw(15) << "-out" << std::setw(15) << "Save results\n";
	cout << std::setw(15) << "-add" << std::setw(15) << "Add matrices\n";
	cout << std::setw(15) << "-sub" << std::setw(15) << "Subtract matrices\n";
	cout << std::setw(15) << "-mul" << std::setw(15) << "Multiply mattices\n";
	cout << std::setw(15) << "-eq" << std::setw(15)
		<< "Test matrices for equality\n";
	cout << std::setw(15) << "-T" << std::setw(15) << "Display transpose\n";
	cout << std::setw(15) << "-1" << std::setw(15) << "Display inverse\n";
	cout << std::setw(15) << "-det" << std::setw(15) << "Display determinant\n";
	cout << std::setw(15) << "-solve" << std::setw(15) << "Attempt to solve provided matrix as a set of equations\n";
}
