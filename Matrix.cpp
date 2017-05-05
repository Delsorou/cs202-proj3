/* -----------------------------------------------------------------------------

FILE:              Matrix.cpp

DESCRIPTION:       Implementation file for the Matrix class

COMPILER:          gcc 5.4.0

NOTES:             None

VERSION:           1.0

----------------------------------------------------------------------------- */

#include <utility>
#include <iomanip>
#include <limits>

// This is a shorthand macro for use when repeated element access is needed
#define ELM(r,c) this->getElm(r, c)

/* -----------------------------------------------------------------------------
FUNCTION:          goodSize(const Matrix<T>& other) const
DESCRIPTION:       Returns true if size is not too small to fit or way too big
RETURNS:           bool
NOTES:             Used to prevent unnecessary resizing on reassignment
----------------------------------------------------------------------------- */
template <class T>
bool Matrix<T>::goodSize(const Matrix<T>& other) const
{
	// If it's not too small, or too big, it's good
	if ((row >= other.row && col >= other.col) 
		&& (row <= other.row * MEM_PAD && col <= other.col * MEM_PAD))
	   	return true;
	// Otherwise it's not
	else
		return false;
}

/* -----------------------------------------------------------------------------
FUNCTION:          resize(const Matrix<T>& other)
DESCRIPTION:       Deletes the existing matrix and initialzes a new zero matrix
                   of specified row, column dimensions
RETURNS:           Void function
NOTES:             Does not assign dimension values
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::resize(const Matrix<T>& other)
{
	// Delete existing matrix arrays from heap
	for (std::size_t i = 0; i < row; ++i)
		delete[] mtx[i];
	delete[] mtx;

	// Create and initialize new matrix arrays of specified dimensions on heap
	mtx = new T*[other.row];
	for (std::size_t i = 0; i < other.row; ++i)
		mtx[i] = new T[other.col] { 0 };
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix()
DESCRIPTION:       Default constructor (1x1 zero matrix)
RETURNS:           N/A
NOTES:             Closest equivalent to integer zero
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
FUNCTION:          Matrix(const size_t r, const size_t c)
DESCRIPTION:       Constructs zero matrix of specified row, column dimensions
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const std::size_t r, const std::size_t c)
{
	// Initialize matrix dimensions
	row = r, col = c;

	// Create and initialize new zero matrix on heap of specified dimensions
	mtx = new T*[r];
	for (std::size_t i = 0; i < r; ++i)
		mtx[i] = new T[c] { 0 };
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const Matrix<T>& other)
DESCRIPTION:       Copy constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	// Initialize dimension values to other matrix values
	row = other.row, col = other.col;

	// Create new matrix of other matrix dimensions and copy each element
	mtx = new T*[row];
	for (std::size_t i = 0; i < row; ++i)
	{
		mtx[i] = new T[col];
		for (std::size_t j = 0; j < col; ++j)
			mtx[i][j] = other.mtx[i][j];
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(Matrix<T>&& other) noexcept
DESCRIPTION:       Move constructor for Matrix class
RETURNS:           N/A
NOTES:             Constant time move construction for rvalue references
                   (usually temporaries)... modifies parameter object
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
{
	// Initialize dimension values to other matrix values
	row = other.row, col = other.col;

	// Exchange existing memory resources
	mtx = other.mtx;

	// Zero other matrix so it won't index empty memory
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
	for (std::size_t i = 0; i < row; ++i)
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
	for (std::size_t i = 0; i < row; ++i)
	{
		for (std::size_t j = 0; j < col; ++j)
			mtx[i][j] = other.mtx[i][j];
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator=(Matrix<T>&& other) noexcept
DESCRIPTION:       Move assignment operator for Matrix class
RETURNS:           Matrix<T>&
NOTES:             Constant time assignment for any size matrix when safe.
                   Used for rvalue references (usually temporaries)
				   Modifies parameter object.
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
	// Swap matrix dimension values
	std::swap(row, other.row);
   	std::swap(col, other.col);
	
	// Move memory resources directly
	std::swap(mtx, other.mtx);

	/* One little, two little, three little assignments...
	 * Whee, that was fast, thanks C++11 move semantics! */
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
	for (std::size_t i = 0; i < other.row; ++i)
	{
		for (std::size_t j = 0; j < other.col; ++j)
			os << FLD << other.mtx[i][j] << ' ';
		os << std::endl;
	}

	return os;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator>>(istream& is, Matrix<T>& other)
DESCRIPTION:       Stream extraction operator for Matrix class
RETURNS:           istream&
NOTES:             Only changes parameter if stream state is good after copy
----------------------------------------------------------------------------- */
template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& other)
{
	// Create template type buffers for matrix dimension values
	std::size_t buffR, buffC;
	// Extract row value from stream into buffer
	is >> buffR;
	// Skip the x
	is.ignore(std::numeric_limits<std::streamsize>::max(), 'x');
	// Extract column value from stream into buffer
	is >> buffC;

	// Create a buffer matrix
	Matrix<T> buff(buffR, buffC);

	// Extract the matrix entries, element by element
	for (std::size_t i = 0; i < buffR; ++i)
	{
		for (std::size_t j = 0; j < buffC; ++j)
			is >> buff.mtx[i][j];
	}
	
	// Assign only if input completely
	if (is.good())
	{
		// Resize other matrix only if necessary
		if (!other.goodSize(buff))
			other.resize(buff);
		other = buff;
	}

	return is;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator+=(const Matrix_ops<T>& other)
DESCRIPTION:       Compound addition assignment operator for Matrix class
RETURNS:           Matrix_ops<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T>& Matrix_ops<T>::operator+=(const Matrix_ops<T>& other)
{
	// Throw an exception if not suitable for addition
	if (this->getRow() != other.getRow() || this->getCol() != other.getCol())
		throw "Invalid operation (addition)...";

	for (std::size_t i = 0; i < this->getRow(); ++i)
	{
		for (std::size_t j = 0; j < this->getCol(); ++j)
		{
			// Add each entry 
			this->setElm(i, j, this->getElm(i, j) + other.getElm(i, j));
		}
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator-=(const Matrix_ops<T>& other)
DESCRIPTION:       Compound subtraction assignment operator for Matrix class
RETURNS:           Matrix_ops<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T>& Matrix_ops<T>::operator-=(const Matrix_ops<T>& other)
{
	// Throw an exception if not suitable for subtraction
	if (this->getRow() != other.getRow() || this->getCol() != other.getCol())
		throw "Invalid operation (subtraction)...";

	for (std::size_t i = 0; i < this->getRow(); ++i)
	{
		for (std::size_t j = 0; j < this->getCol(); ++j)
		{
			// Subtract each entry 
			this->setElm(i, j, this->getElm(i, j) - other.getElm(i, j));
		}
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*=(const Matrix_ops<T>& other)
DESCRIPTION:       Compound multiplication assignment operator for Matrix class
RETURNS:           Matrix_ops<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T>& Matrix_ops<T>::operator*=(const Matrix_ops<T>& other)
{
	// Create local dimension buffers to reduce function calls
	std::size_t rowB = this->getRow(), colB = other.getCol();

	// Throw an exception if not suitable for multiplication
	if (rowB != colB)
		throw "Invalid operation (matrix multiplication)...";
	
	// Make a buffer object to hold the product
	Matrix_ops<T> product(rowB, colB);

	for (std::size_t i = 0; i < rowB; ++i)
	{
		for (std::size_t j = 0; j < colB; ++j)
		{
			// Create a buffer object
			T buffer = 0;
			// Take the dot product and store it in buffer
			for (std::size_t p = 0; p < colB; ++p)
			{
				buffer += this->getElm(i, p) * other.getElm(p, j);
			}
			// Set this entry to equal buffer
			product.setElm(i, j, buffer);
		}
	}

	// Force move self-assignment from local buffer before it leaves scope
	*this = std::move(product);

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator*=(const T scalar)
DESCRIPTION:       Compound scalar multiplication assignment operator
                   for Matrix class
RETURNS:           Matrix_ops<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T>& Matrix_ops<T>::operator*=(const T scalar)
{
	// Eliminate obvious cases
	if (scalar == 1) return *this;
	// If the scalar is zero, just construct a replacement zero matrix
	else if (scalar == 0)
	{
		Matrix_ops<T> zero(this->getRow(), this->getCol());
		*this = std::move(zero);
		return *this;
	}	

	for (std::size_t i = 0; i < this->getRow(); ++i)
	{
		for (std::size_t j = 0; j < this->getCol(); ++j)
			this->setElm(i, j, this->getElm(i, j) * scalar);
	}

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator==(const Matrix_ops<T>& other) const
DESCRIPTION:       Compound addition assignment operator for Matrix class
RETURNS:           bool
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
bool Matrix_ops<T>::operator==(const Matrix_ops<T>& other) const
{
	// Initialze boolean buffer for equality
	bool isEqual = true;

	// If row or column is not equal, it can't be equal
	if (this->getRow() != other.getRow() || this->getCol() != other.getCol())
		isEqual = false;

	// If any member is not equal, it's not equal (skip if already failed)
	if (isEqual)
	{
		for (std::size_t i = 0; i < this->getRow(); ++i)
		{
			for (std::size_t j = 0; j < this->getCol(); ++j)
			{
				if (this->getElm(i, j) != other.getElm(i, j))
					isEqual = false;
			}
		}
	}

	return isEqual;
}

/* -----------------------------------------------------------------------------
FUNCTION:          trans()
DESCRIPTION:       Transposes the matrix
RETURNS:           Matrix_ops<T>&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T>& Matrix_ops<T>::trans()
{
	// Create a local buffer to store the transpose
	Matrix_ops<T> transpose(this->getCol(), this->getRow());

	for (std::size_t i = 0; i < transpose.getRow(); ++i)
	{
		for (std::size_t j = 0; j < transpose.getCol(); ++j)
			transpose.setElm(i, j, this->getElm(j, i));
	}

	// Copy local buffer using move semantics
	*this = std::move(transpose);

	return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION:          det()
DESCRIPTION:       Returns the determinant of this matrix
RETURNS:           T
NOTES:             Very easy to overrun template datatype with large matrices
----------------------------------------------------------------------------- */
template <class T>
T Matrix_ops<T>::det()
{
	std::size_t rowB = this->getRow(), colB = this->getCol();
	
	// Eliminate invalid and base cases
	if (rowB != colB)
		throw "Invalid operation (determinant)";
	// Determinant of 1x1 is the value of its only entry
	else if (rowB == 1)	return ELM(0,0);
	// 2 x 2 base case
	else if (rowB == 2)	return ELM(0,0) * ELM(1,1) - ELM(1,0) * ELM(0,1); 
	// 3 x 3 diagonal product base case
	else if (rowB == 3)
	{
		return
		{
			(ELM(0,2) * ELM(1,0) * ELM(2,1)
			 + ELM(0,0) * ELM(1,1) * ELM(2,2)
			 + ELM(0,1) * ELM(1,2) * ELM(2,0))
			- (ELM(2,2) * ELM(1,0) * ELM(0,1)
			 + ELM(2,0) * ELM(1,1) * ELM(0,2)
			 + ELM(2,1) * ELM(1,2) * ELM(0,0))
		};
	}

	/* We have not yet reached the base cases, so we need to compute.
	 * Create dynamic storage for a new round of minors and factors. */
	Matrix_ops<T>* minor[colB];
	T* factor[colB];
	for (std::size_t i = 0; i < colB; ++i)
	{
	   	minor[i] = new Matrix_ops<T>(rowB - 1, colB - 1);
		factor[i] = new T {};
	}

	// Populate the storage with all minors and factors
	for (std::size_t n = 0; n < colB; ++n)
	{
		for (std::size_t i = 0; i < rowB - 1; ++i)
		{
			for (std::size_t j = 0; j < colB - 1; ++j)
			{
				if (n <= j) minor[n]->setElm(i, j, ELM(i,j + 1));
				else minor[n]->setElm(i, j, ELM(i,j));
			}
		}
		*factor[n] = ELM(rowB - 1,n);
		if (rowB + n + 1 % 2 != 0) *factor[n] *= -1;
	}

	// Create a buffer and sum all the cofactors into it
	T determinant = 0;
	for (std::size_t i = 0; i <= colB; ++i)
			determinant += minor[i]->det() * *factor[i];

	// Delete cofactor data storage
	for (std::size_t i = 0; i < rowB; ++i)
	{
		delete minor[i];
		delete factor[i];
	}

	// And return the result
	return determinant;
}
