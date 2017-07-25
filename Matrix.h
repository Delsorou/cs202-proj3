#ifndef MATRIX_H
#define MATRIX_H
/* -----------------------------------------------------------------------------

FILE:              Matrix.h

DESCRIPTION:       Specification file for the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             None

VERSION:           1.0

----------------------------------------------------------------------------- */

#include <iostream>

/* This is the multiplier on excess matrix dimensions before resizing.
 * Do not make it less than 1.0... that would be a bad business decision. */
#define MEM_PAD 1.5

// This is the field size for matrix elements in iostream output
#define FLD std::setw(5)

// Forward declare the class for I/O operator prototype list
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
	std::size_t row, col;
	// Matrix array storage pointer (template type)
	T **mtx;

	// Matrix dimension validation before expensive resize
	bool goodSize(const Matrix<T>& other) const;
	// Matrix array resize function (new zero matrix)
	void resize(const Matrix<T>& other);

public:
	// Constructor (Default)
	Matrix();
	// Constructor (Parameterized) (row, col)
	Matrix(const std::size_t r, const std::size_t c);
	// Constructor (Copy)
	Matrix(const Matrix<T>& other);
	// Constructor (Move) (rvalue reference)
	Matrix(Matrix<T>&& other) noexcept;
	// Destructor
	virtual ~Matrix();

	// Row dimension accessor (inline)
	std::size_t getRow() const
	{ return row; };

	// Column dimension accessor (inline)
	std::size_t getCol() const
	{ return col; };

	// Matrix element mutator function (row, col, val) (inline)
	void setElm(const std::size_t r, const std::size_t c, const T k)
	{ mtx[r][c] = k; };

	// Matrix element accessor function (row, col) (inline)
	T getElm(const std::size_t r, const std::size_t c) const
	{ return mtx[r][c]; };

	// Assignment operator (Copy)
	Matrix<T>& operator=
		(const Matrix<T>& other);
	// Assignment operator (Move) (rvalue reference)
	Matrix<T>& operator=
		(Matrix<T>&& other) noexcept;

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
	// Default constructor
	Matrix_ops() : Matrix<T>()
	{ }
	
	// Derived class parameterized constructor
	Matrix_ops(const std::size_t r, const std::size_t c) : Matrix<T>(r, c)
	{ }
	
	// Compound assignment operators
	// Addition assignment
	Matrix_ops<T>& operator+=
		(const Matrix_ops<T>& other);
	// Subtraction assignment
	Matrix_ops<T>& operator-=
		(const Matrix_ops<T>& other);
	// Matrix multiplication assignment
	Matrix_ops<T>& operator*=
		(const Matrix_ops<T>& other);
	// Scalar multiplication assignment
	Matrix_ops<T>& operator*=
		(const T scalar);
	// Scalar division assignment
	Matrix_ops<T>& operator/=
		(const T scalar);

	/* Binary operators are defined in terms of compound assignment and
	 * declared inline friend so (class * subclass == subclass * class) */
	// Binary addition
	friend Matrix_ops<T> operator+
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left += other; };
	// Binary subtraction
	friend Matrix_ops<T> operator-
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left -= other; };
	// Binary matrix multiplication
	friend Matrix_ops<T> operator*
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left *= other; };
	// Binary scalar multiplication
	friend Matrix_ops<T> operator*
		(Matrix_ops<T> left, const T scalar)
	{ return left *= scalar; };
	// Redefined for type symmetry
	friend Matrix_ops<T> operator*
		(const T scalar, Matrix_ops<T> right)
	{ return right *= scalar; }
	// Binary scalar division
	friend Matrix_ops<T> operator/
		(Matrix_ops<T> left, const T scalar)
	{ return left /= scalar; };

	// Equality operator
	bool operator==
		(const Matrix_ops<T>& other) const;
	// Inequality operator defined using equality
	bool operator!=
		(const Matrix_ops<T>& other) const
	{ return !(*this == other); };

	// Special matrix operations
	// Determinant
	T det();
	// Transpose
	Matrix_ops<T>& trans();
};

// Include implementation file, template class design cannot span TUs
#include "Matrix.cpp"
#endif // MATRIX_H
