/* -----------------------------------------------------------------------------

FILE:              matrix_math.cpp

DESCRIPTION:       Driver for testing the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             Based on example code provided by Ed Corbett

VERSION:           1.0.1

----------------------------------------------------------------------------- */

#include <cstring>
#include <fstream>
#include "Matrix.h"
#define ITEM std::left << std::setw(6)
#define DESC std::right << std::setw(31)

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

	try
	{
		while (--argc)
		{
			++argv;

			if (strcmp(*argv, "-inp") == 0)
			{
				err = read_matrix(mat1, --argc, *++argv);
				if (err) return err;
				mat3 = mat1;
				std::cout << "Input:  " << std::endl;
				std::cout << mat3 << std::endl;
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
				std::cout << mat1 << std::endl << '+' << mat2 << std::endl
					<< '=';
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
				std::cout << mat1 << std::endl << '-' << mat2 << std::endl
					<< '=';
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
				std::cout << mat1 << std::endl << 'x' << mat2 << std::endl
					<< '=';
				std::cout << mat3 << std::endl;
			}
		
			if (strcmp(*argv, "-eq") == 0)
			{
				err = read_matrix(mat1, --argc, *++argv);
				if (err) return err;
				err = read_matrix(mat2, --argc, *++argv);
				if (err) return err;

				bool equality = mat1 == mat2;
				std::cout << mat1 << std::endl << mat2 << std::endl;
				std::cout << "Equality:  " << std::endl;
				std::cout << std::boolalpha << equality << std::endl;
			}

			if (strcmp(*argv, "-T") == 0)
			{
				err = read_matrix(mat1, --argc, *++argv);
				if (err) return err;
		
				std::cout << mat1 << std::endl;
				mat3 = mat1.trans();
				std::cout << "Transpose:  " << std::endl;
				std::cout << mat3 << std::endl;
			}

//			if (strcmp(*argv, "-1") == 0)
//			{
//				err = read_matrix(mat1, --argc, *++argv);
//				if (err) return err;
//
//				std::cout << "Inverse:  " << std::endl;
//				std::cout << mat1.inv() << std::endl;
//			}

			if (strcmp(*argv, "-det") == 0)
			{
				err = read_matrix(mat1, --argc, *++argv);
				if (err) return err;
	
				std::cout << mat1 << std::endl;
				std::cout << "Determinant:  " << std::endl;
				std::cout << mat1.det() << std::endl;
			}

//			if (strcmp(*argv, "-solve") == 0)
//			{
//				err = read_matrix(mat1, --argc, *++argv);
//				if (err) return err;
//
//				std::cout << "Solution:  " << std::endl;
//				std::cout << mat1.solve() << std::endl;
//			}
		
			if (strcmp(*argv, "-h") == 0)
			{
				display_help();
			}
		}
	}
	catch (const char* exc) { std::cout << exc << std::endl; };

	if (*file2) write_matrix(file2, mat3);

	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          read_matrix(Matrix<T>& mat1, int argc, char arg[])
DESCRIPTION:       Reads matrix from specified filename
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
FUNCTION:          read_file2(char file2[], int argc, char arg[])
DESCRIPTION:       Parse argument for output file, if needed
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
FUNCTION:          write_matrix(char file2[], Matrix<T>& mat)
DESCRIPTION:       Writes matrices to the given output file
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

/* -----------------------------------------------------------------------------
FUNCTION:          display_help()
DESCRIPTION:       Displays the help section
RETURNS:           Void function
NOTES:             None
----------------------------------------------------------------------------- */
void display_help()
{
	using std::cout;
	using std::endl;
	cout << std::left << endl << "Matrix Math Demonstration Program...\n\n";
	cout << "Usage: matrix_math [-arg] [filename(s)] ... [-out] [filename]\n\n";
	cout << "Arguments:\n\n";
	cout << ITEM << "-h" << DESC << "   Display this help file\n";
	cout << ITEM << "-inp" << DESC << "   Display matrix\n";
	cout << ITEM << "-out" << DESC << "   Save results to file\n";
	cout << ITEM << "-add" << DESC << "   Add matrices\n";
	cout << ITEM << "-sub" << DESC << "   Subtract matrices\n";
	cout << ITEM << "-mul" << DESC << "   Multiply matrices\n";
	cout << ITEM << "-eq" << DESC << "   Test matrices for equality\n";
	cout << ITEM << "-T" << DESC << "   Display transpose\n";
	cout << ITEM << "-1" << DESC << "   Display inverse (NONFUNCTIONAL)\n";
	cout << ITEM << "-det" << DESC	<< "   Display determinant\n";
	cout << ITEM << "-solve" << DESC 
		<< "   Attempt to solve as a set of equations (NONFUNCTIONAL)\n";
}
