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
	Matrix(Matrix<T>&& other) noexcept;
	// Destructor
	virtual ~Matrix();

	// Row dimension accessor and mutuator functions (inline)
	void setRow(const int r)
	{ row = r; };
	int getRow() const
	{ return row; };

	// Column dimension accessor and mutator functions (inline)
	void setCol(const int c)
	{ col = c; };
	int getCol() const
	{ return col; };

	// Matrix element mutator function (row, col, val) (inline)
	void setElm(const int r, const int c, const T k)
	{ mtx[r][c] = k; };
	// Matrix element accessor function (row, col) (inline)
	T getElm(const int r, const int c) const
	{ return mtx[r][c]; };

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

template <class T>
class Matrix_ops : public Matrix<T>
{
public:
	// Addition operator
	Matrix<T>& operator+=(const Matrix<T>& other);
	friend Matrix<T> operator+(Matrix<T> left, const Matrix<T>& other)
	{ return left += other; };

	// Subtraction operator
	Matrix<T>& operator-=(const Matrix<T>& other);
	friend Matrix<T> operator-(Matrix<T> left, const Matrix<T>& other)
	{ return left -= other; };

	// Multiplication operator
	Matrix<T>& operator*=(const Matrix<T>& other);
	friend Matrix<T> operator*(Matrix<T> left, const Matrix<T>& other)
	{ return left *= other; };
	
	// Scalar multiplication operators
	Matrix<T>& operator*=(const T& scalar);
	friend Matrix<T> operator*(Matrix<T> left, const T& scalar)
	{ return left *= scalar; };
	friend Matrix<T> operator*(const T& scalar, Matrix<T> right)
	{ return right *= scalar; };

	// Equality operators
	bool operator==(const Matrix<T>& other) const;
	bool operator!=(const Matrix<T>& other) const
	{ return !(*this == other); };
};

// Include implementation file for template class design
#include "Matrix.cpp"
#endif // MATRIX_H
