#ifndef MATRIX_H
#define MATRIX_H
/* -----------------------------------------------------------------------------

FILE:              Matrix.h

DESCRIPTION:       Specification file for the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             None

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Aaryna Irwin            2017-04-11         0.1

----------------------------------------------------------------------------- */

#include <iostream>

// Forward declare the class to create template friend functions
template <class T>
class Matrix;

// Template I/O operator overload prototypes
template <class T>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
template <class T>
std::istream& operator>>(std::istream&, Matrix<T>&);

template <class T>
class Matrix
{
	int row, col;
	T **mtx;
public:
	Matrix();
	Matrix(const int, const int);
	Matrix(const Matrix&);
	virtual ~Matrix();

	void set(const int, const int, const T);
	void resize(const int, const int);

	friend std::ostream& operator<<<T>(std::ostream&, const Matrix<T>&);
	friend std::istream& operator>><T>(std::istream&, Matrix<T>&);
};
#include "Matrix.cpp"
#endif // MATRIX_H
