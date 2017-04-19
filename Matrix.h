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

#define FLD std::setw(5)
#include <iostream>

// Forward declare the class for I/O operator prototype parameter list
template <class T>
class Matrix;

// Templated, class parameter I/O operator prototypes
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& other);
template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& other);

template <class T>
class Matrix
{
	// Matrix dimension values
	int row, col;
	// Matrix array storage pointer (template type)
	T **mtx;

	// Matrix dimension validation before expensive resize
	bool goodSize(const Matrix<T>& other) const;
	// Matrix array resize function (new zero matrix)
	void resize(const Matrix<T>& other);

public:
	// Constructor (Default)
	Matrix();
	// Constructor (Parameterized) (int row, int col)
	Matrix(const int r, const int c);
	// Constructor (Copy)
	Matrix(const Matrix<T>& other);
	// Constructor (Move) (rvalue reference)
	Matrix(Matrix<T>&& other);
	// Destructor
	virtual ~Matrix();

	// Matrix element mutator function (row, col, val) (inline)
	void set(const int r, const int c, const T k) { mtx[r][c] = k; };
	// Matrix element accessor function (row, col) (inline)
	T get(const int r, const int c) const { return mtx[r][c]; };

	// Assignment operator (Copy)
	Matrix<T>& operator=(const Matrix<T>& other);
	// Assignment operator (Move) (rvalue reference)
	Matrix<T>& operator=(Matrix<T>&& other) noexcept;

	// Stream insertion operator of prototyped template type
	friend std::ostream& operator<<<T>
		(std::ostream& os, const Matrix<T>& other);
	// Stream extraction operator of prototyped template type
	friend std::istream& operator>><T>
		(std::istream& os, Matrix<T>& other);
};
// Include implementation file for template class design
#include "Matrix.cpp"
#endif // MATRIX_H
