#include "IntMatrix.h"
#include <iostream>

//------------------------------------------------------------------------------------------------
// Implementations for the IntMatrix class follows
//------------------------------------------------------------------------------------------------

#define NONE 0

using namespace std;

//------------------------------------- constructors ---------------------------------------------

/**
 * @brief Documented in header file
 */
IntMatrix::IntMatrix()
{
	_rows = NONE;
	_cols = NONE;
	_matrix = nullptr;
}

/**
 * @brief Documented in header file
 */
IntMatrix::IntMatrix(const int rows, const int cols)
{
	_rows = rows;
	_cols = cols;
	_matrix = new int[_rows * _cols];
	int arraySize = _rows * _cols;
	for (int i = 0; i < arraySize; ++i)
	{
		_matrix[i] = 0;
	}
}

/**
 * @brief Documented in header file
 */
IntMatrix::IntMatrix(const IntMatrix &other)
{
	_rows = other._rows;
	_cols = other._cols;
	_matrix = new int[_rows * _cols];
	for (int i = 0; i < (_rows * _cols); ++i)
	{
		_matrix[i] = other._matrix[i];
	}
}

/**
 * @brief Documented in header file
 */
IntMatrix::IntMatrix(const int rows, const int cols, int* matrixArray)
{
	_rows = rows;
	_cols = cols;
	_matrix = matrixArray;
}

/**
 * @brief Documented in header file
 */
IntMatrix::~IntMatrix()
{
	if (_matrix != nullptr)
	{
		delete[] _matrix;
	}
}

//-------------------------------------- operators -----------------------------------------------

/**
 * @brief Documented in header file
 */
IntMatrix& IntMatrix::operator=(const IntMatrix &other)
{
	if (this != &other) // in case of self assignment, just return the same object.
	{
		if (_matrix != nullptr)
		{
			if ((other._rows * other._cols) != (this->_rows * this->_cols))
			{
				delete[] _matrix;
				_matrix = new int[other._rows * other._rows];
			}
		}
		else
		{
			_matrix = new int[other._rows * other._rows];
		}
		this->_rows = other._rows;
		this->_cols = other._cols;
		int matrixArrayLength = other._rows * other._rows;
		for (int i = 0; i < matrixArrayLength; ++i)
		{
			_matrix[i] = other._matrix[i];
		}
	}
	return *this;
}

/**
 * @brief Documented in header file
 */
IntMatrix &IntMatrix::operator+=(const IntMatrix &other)
{
	int matrixArrayLength = _rows * _cols;
	for (int i = 0; i < matrixArrayLength; ++i)
	{
		_matrix[i] += other._matrix[i];
	}

	return *this;
}

/**
 * @brief Documented in header file
 */
IntMatrix &IntMatrix::operator-=(const IntMatrix &other)
{
	int matrixArrayLength = _rows * _cols;
	for (int i = 0; i < matrixArrayLength; ++i)
	{
		_matrix[i] -= other._matrix[i];
	}

	return *this;
}

/**
 * @brief Documented in header file
 */
IntMatrix &IntMatrix::operator*=(const IntMatrix &other)
{
	int *newMatrix = new int[_rows * other._cols];
	for (int row = 0; row < _rows; ++row)
	{
		for (int otherCol = 0; otherCol < other._cols; ++otherCol)
		{
			int dotProduct = NONE;
			for (int col = 0; col < _cols; ++col)
			{
				dotProduct += _matrix[(row * _cols) + col] * other._matrix[(col * other._cols) +
						otherCol];
			}
			newMatrix[row * _rows + otherCol] = dotProduct;
		}
	}
	delete[] _matrix;
	_matrix = newMatrix;
	_cols = other._cols;
	return *this;
}

/**
 * @brief Documented in header file
 */
const IntMatrix IntMatrix::operator+(const IntMatrix &other)
{
	IntMatrix result = *this;
	result += other;
	return result;
}

/**
 * @brief Documented in header file
 */
const IntMatrix IntMatrix::operator-(const IntMatrix &other)
{
	IntMatrix result = *this;
	result -= other;
	return result;
}

/**
 * @brief Documented in header file
 */
const IntMatrix IntMatrix::operator*(const IntMatrix &other)
{
	IntMatrix result = *this;
	result *= other;
	return result;
}

/**
 * @brief Documented in header file
 */
ostream& operator<<(ostream &os, const IntMatrix &matrix)
{
	os << endl;
	for (int i = 0; i < matrix._rows; ++i)
	{
		for (int j = 0; j < matrix._cols; ++j)
		{
			const int LAST_ELEMENT = matrix._cols - 1;

			os << matrix._matrix[i * matrix._cols + j];
			if (j < LAST_ELEMENT)
			{
				os << " ";
			}
		}
		os << endl;
	}
	return os;
}

//----------------------------------- methods ----------------------------------------------------

/**
 * @brief Documented in header file
 */
IntMatrix IntMatrix::trans()
{
	int *transposed = new int[_rows * _cols];
	for (int row = 0; row < _rows; ++row)
	{
		for (int col = 0; col < _cols; ++col)
		{
			transposed[(col * _rows) + row] = _matrix[(row * _cols) + col];
		}
	}
	return IntMatrix(_cols, _rows, transposed);
}

/**
 * @brief Documented in header file
 */
int IntMatrix::trace()
{
	int theTrace = 0;
	if (_matrix != nullptr)
	{
		for (int i = 0; i < _rows; ++i)
		{
			theTrace += _matrix[i*_rows + i];
		}
	}
	return theTrace;
}

/**
 * @brief Documented in header file
 */
int IntMatrix::getRows()
{
	return _rows;
}

/**
 * @brief Documented in header file
 */
int IntMatrix::getCols()
{
	return _cols;
}
