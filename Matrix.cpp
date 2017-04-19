/* -----------------------------------------------------------------------------

FILE:              Matrix.cpp

DESCRIPTION:       Implementation file for the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             None

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Aaryna Irwin            2017-04-11         0.1

----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <limits>

/* -----------------------------------------------------------------------------
FUNCTION:          goodSize(Matrix<T>& other)
DESCRIPTION:       Returns true if size is not too small to fit or way too big
RETURNS:           bool
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
bool Matrix<T>::goodSize(const Matrix<T>& other) const
{
	// If it's not too small, or more than twice as big, it's good
	if ((row > other.row && col > other.col) 
		&& (row <= other.row * 2 && col <= other.col * 2))
	   	return true;
	// Otherwise it's not
	else
		return false;
}

/* -----------------------------------------------------------------------------
FUNCTION:          resize(Matrix<T>& other)
DESCRIPTION:       Deletes the existing matrix and initialzes a new zero matrix
                   of specified row, column dimensions
RETURNS:           Void function
NOTES:             Does not assign dimension values
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::resize(const Matrix<T>& other)
{
	// Delete existing matrix arrays from heap
	for (int i = 0; i < row; ++i)
		delete[] mtx[i];
	delete[] mtx;

	// Create and initialize new matrix array of specified dimensions on heap
	mtx = new T*[other.row];
	for (int i = 0; i < other.row; ++i)
		mtx[i] = new T[other.col] { 0 };
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix()
DESCRIPTION:       Default constructor (1x1 zero matrix)
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix()
{
	// Initialize default matrix dimensions
	row = 1, col = 1;
	// Create and initialize single element zero matrix array on heap
	mtx = new T*;
	mtx[0] = new T { 0 };
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const int r, const int c)
DESCRIPTION:       Constructs zero matrix of specified row, column dimensions
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const int r, const int c)
{
	// Initialize matrix dimensions
	row = r, col = c;

	// Create and intialize new zero matrix on heap of specified dimensions
	mtx = new T*[r];
	for (int i = 0; i < r; ++i)
		mtx[i] = new T[c] { 0 };
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const Matrix<T>&)
DESCRIPTION:       Copy constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	// Initialize dimension values to other matrix values
	row = other.row, col = other.col;

	// Create new matrix of other dimensions and copy each element
	mtx = new T*[row];
	for (int i = 0; i < row; ++i)
	{
		mtx[i] = new T[col];
		for (int j = 0; j < col; ++j)
			mtx[i][j] = other.mtx[i][j];
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const Matrix<T>&&)
DESCRIPTION:       Move constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
{
	// Initialize dimension values to other matrix values
	row = other.row, col = other.col;

	// Reuse existing memory resource of temporary object
	mtx = &other.mtx;

	// Zero other address in case of destruction
	other.mtx = nullptr, other.row = 0, other.col = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          ~Matrix()
DESCRIPTION:       Default destructor for Matrix class
RETURNS:           N/A
NOTES:             Fresh and sassy
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::~Matrix()
{
	// Delete deez nuts
	for (int i = 0; i < row; ++i)
		delete[] mtx[i];
	delete[] mtx;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator=(const Matrix<T>& other)
DESCRIPTION:       Copy assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	// Skip resize if we can get away with it
	if (!goodSize(other))
		resize(other);

	// Copy other matrix dimension values
	row = other.row, col = other.col;

	// Copy other matrix values element by element
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
			mtx[i][j] = other.mtx[i][j];
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator=(Matrix<T>&& other)
DESCRIPTION:       Move assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             Memory leak on self-assignment (so don't do that)
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
	// Copy other matrix dimension values
	row = other.row, col = other.col;

	// Move allocated memory directly
	mtx = other.mtx;

	// Zero other matrix storage pointer to prevent deallocation
	other.mtx = nullptr, other.row = 0, other.col = 0;

	// Whee, that was fast, thanks C++11 move semantics!
	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator<<(ostream& os, Matrix<T>& other)
DESCRIPTION:       Stream insertion operator for Matrix class
RETURNS:           ostream&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& other)
{
	// Insert the matrix dimensions on the first line
	os << std::setprecision(3) << std::fixed << FLD 
		<< other.row << " x " << std::left << other.col
		<< std::right << std::endl;

	// Insert the matrix, row per line
	for (int i = 0; i < other.row; ++i)
	{
		for (int j = 0; j < other.col; ++j)
			os << FLD << other.mtx[i][j] << ' ';
		os << std::endl;
	}

	return os;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator>>(istream& is, Matrix<T>& other)
DESCRIPTION:       Stream extraction operator for Matrix class
RETURNS:           istream&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& other)
{
	// Create template type buffers for matrix dimension values
	T buffR, buffC;
	// Extract row value from stream into buffer
	is >> buffR;
	// Skip the x
	is.ignore(std::numeric_limits<std::streamsize>::max(), 'x');
	// Extrract column value from stream into buffer
	is >> buffC;

	// Resize other matrix only if necessary
	Matrix<T> buffMat(buffR, buffC);
	if (!other.goodSize(buffMat))
		other.resize(buffMat);

	// Copy matrix dimension values
	other.row = buffR, other.col = buffC;

	// Extract the matrix entries, element by element
	for (int i = 0; i < other.row; ++i)
	{
		for (int j = 0; j < other.col; ++j)
			is >> other.mtx[i][j];
	}

	return is;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator+=(const Matrix<T>& other)
DESCRIPTION:       Compound addition assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix_ops<T>::operator+=(const Matrix<T>& other)
{
	// Throw an exception if not suitable for addition
	if (this->getRow() != other.getRow() || this->getCol() != other.getCol())
		throw "Invalid operation (addition)...";

	// Sum assign other matrix values element by element
	for (int i = 0; i < this->getRow(); ++i)
	{
		for (int j = 0; j < this->getCol(); ++j)
		{
			T buffer = this->getElm(i, j) + other.getElm(i, j);
			this->setElm(i, j, buffer);
		}
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operatorc-=(const Matrix<T>& other)
DESCRIPTION:       Compound subtraction assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix_ops<T>::operator-=(const Matrix<T>& other)
{
	// Throw an exception if not suitable for subtraction
	if (this->row != other.row || this->col != other.col)
		throw "Invalid operation (subtraction)...";

	// Difference assign other matrix values element by element
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			T buffer = this->getElm(i, j) - other.getElm(i, j);
			this->setElm(i, j, buffer);
		}
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*=(const Matrix<T>& other)
DESCRIPTION:       Compound multiplication assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix_ops<T>::operator*=(const Matrix<T>& other)
{
	// Throw an exception if not suitable for multiplication
//	if (this->col != other.row)
//		throw "Invalid operation (matrix multiplication)...";

	// Make a buffer object to hold the product
//	Matrix_ops<T> product(this->row, other.col);

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*=(const Matrix<T>& scalar)
DESCRIPTION:       Compound scalar multiplication assignment operator
                   for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix_ops<T>::operator*=(const T& scalar)
{
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
			this->mtx[i][j] *= scalar;
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator==(const Matrix<T>& other)
DESCRIPTION:       Compound addition assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
bool Matrix_ops<T>::operator==(const Matrix<T>& other) const
{
	// Initialze boolean buffer for equality
	bool isEqual = true;

	// If row or column is not equal, it can't be equal
	if (this->row != other.row || this->col != other.col)
		isEqual = false;

	// If any member is not equal, it's not equal (skip if already failed)
	if (isEqual)
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				if (this->mtx[i][j] != other.mtx[i][j])
					isEqual = false;
			}
		}
	}

	return *this;
}
