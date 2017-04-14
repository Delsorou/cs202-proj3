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

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix()
DESCRIPTION:       Default constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix()
{
	row = 0, col = 0;
	mtx = nullptr;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const int, const int)
DESCRIPTION:       Parameterized constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(int r, int c)
{
	row = r, col = c;
	mtx = new T*[r];
	
	for (int i = 0; i < r; ++i)
	{
		mtx[i] = new T[c];
		for (int j = 0; j < c; ++j)
			mtx[i][j] = 0;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix(const Matrix<T>&)
DESCRIPTION:       Copy constructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
	row = m.row, col = m.col;
	mtx = new T*[row];

	for (int i = 0; i < row; ++i)
	{
		mtx[i] = new T[col];
		for (int j = 0; j < col; ++j)
			mtx[i][j] = m.mtx[i][j];
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          ~Matrix()
DESCRIPTION:       Default destructor for Matrix class
RETURNS:           N/A
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < row; ++i)
		delete[] mtx[i];
	delete[] mtx;
}

/* -----------------------------------------------------------------------------
FUNCTION:          set(const int, const int, const T)
DESCRIPTION:       Sets the value or a matrix member
RETURNS:           Void function
NOTES:             Throws an exception if the index is out of bounds
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::set(const int r, const int c, const T k)
{
	if (r > row)
		throw "Invalid row index";
	else if (c > col)
		throw "Invalid column index";

	mtx[r][c] = k;
}

/* -----------------------------------------------------------------------------
FUNCTION:          resize(const int, const int)
DESCRIPTION:       Deletes the existing matrix and initialzes a new zero matrix
RETURNS:           Void function
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
void Matrix<T>::resize(const int r, const int c)
{
	for (int i = 0; i < row; ++i)
		delete[] mtx[i];
	delete[] mtx;

	row = r, col = c;
	mtx = new T*[r];
	
	for (int i = 0; i < r; ++i)
	{
		mtx[i] = new T[c];
		for (int j = 0; j < c; ++j)
			mtx[i][j] = 0;
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator<<(ostream&, Matrix<T>&)
DESCRIPTION:       Stream insertion operator for Matrix class
RETURNS:           ostream&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
	os << m.row << 'x' << m.col << std::endl;

	for (int i = 0; i < m.row; ++i)
	{
		for (int j = 0; j < m.col; ++j)
			os << m.mtx[i][j] << ' ';
		os << std::endl;
	}

	return os;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator>>(istream&, Matrix<T>&)
DESCRIPTION:       Stream extraction operator for Matrix class
RETURNS:           istream&
NOTES:             None
----------------------------------------------------------------------------- */
template <class T>
std::istream& operator>>(std::istream& is, Matrix<T>& m)
{
	is >> m.row;
	is.ignore(1);
	is >> m.col;

	m.resize(m.row, m.col);

	for (int i = 0; i < m.row; ++i)
	{
		for (int j = 0; j < m.col; ++j)
			is >> m.mtx[i][j];
	}

	return is;
}
