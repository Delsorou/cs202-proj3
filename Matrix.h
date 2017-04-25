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
	// Default constructor
	Matrix_ops() : Matrix<T>()
	{ }
	// Derived class parameterized constructor
	Matrix_ops(const std::size_t r, const std::size_t c) : Matrix<T>(r, c)
	{ }
	
	// Addition compound assignment operator
	Matrix_ops<T>& operator+=(const Matrix_ops<T>& other);
	/* Binary addition operator defined via compound assignment
	 * and declared as a friend for operand symmetry */
	friend Matrix_ops<T> operator+
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left += other; };

	// Subtraction compound assignment operator
	Matrix_ops<T>& operator-=(const Matrix_ops<T>& other);
	/* Binary subtraction operator defined via compound assignment
	 * and declared as a friend for operand symmetry */
	friend Matrix_ops<T> operator-
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left -= other; };

	// Matrix multiplication compound assignment operator
	Matrix_ops<T>& operator*=(const Matrix_ops<T>& other);
	/* Binary matrix multiplication operator defined via compound assignment
	 * and declared as a friend for operand symmetry */
	friend Matrix_ops<T> operator*
		(Matrix_ops<T> left, const Matrix_ops<T>& other)
	{ return left *= other; };
	
	// Scalar multiplication compound assignment operator
	Matrix_ops<T>& operator*=(const T& scalar);
	/* Binary scalar multiplication operator defined via compound assignment
	 * and declared as a friend for operand symmetry */
	friend Matrix_ops<T> operator*(Matrix_ops<T> left, const T& scalar)
	{ return left *= scalar; };

	// Equality operator
	bool operator==(const Matrix_ops<T>& other) const;
	// Inequality operator defined in terms of equality
	bool operator!=(const Matrix_ops<T>& other) const
	{ return !(*this == other); };

	// Special matrix operations (will not modify self)
	Matrix_ops<T> trans() const;
	T det() const;
	Matrix_ops<T> inv(const T determinate = det()) const;
	Matrix_ops<T> solve() const;
};

// Include implementation file for template class design
#include "Matrix.cpp"
#endif // MATRIX_H
