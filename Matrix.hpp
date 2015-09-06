// Matrix.hpp

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <vector>

using namespace std;

template <class T>
class Matrix
{
public:
	/**
	 * The default constructor.
	 * @return A new Matrix object of size 1x1.
	 * @throw bad_alloc exception if memory allocation did not succeed.
	 */
	Matrix() : _rows(1), _cols(1), _matrixVectorSize(1)
	{
		// initialize the size of the matrix.
		_rows = 1;
		_cols = 1;
		_matrixVectorSize = 1;

		// put zero in the only cell of the matrix.
		_matrix.push_back(T(0));
	}

	/**
	 * A constructor that get the dimensions of the new Matrix.
	 * @param rows The number of rows for the new Matrix.
	 * @param rows The number of columns for the new Matrix.
	 * @return A Matrix object with the specified number of rows and columns, that is initialized
	 *         with the zeros of the type T.
	 */
	Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols), _matrixVectorSize
			(rows * cols)
	{
		// put T zeros in the vector.
		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.push_back(T(0));
		}
	}

	/**
	 * A copy constructor.
	 * This constructor creates a new copy of a Matrix<T> object.
	 * @param other The Matrix object to be copied.
	 * @return A new Matrix object that is a copy of the other Matrix object.
	 */
	Matrix(const Matrix<T>& other) : _rows(other._rows), _cols(other._cols), _matrixVectorSize
			(other._matrixVectorSize)
	{
		// copy the matrix elements from the other matrix to the new one.
		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.push_back(other._matrix[i]);
		}
	}

	/**
	 * The Matrix class destructor.
	 * Destructs the elements of the vector containing the matrix object cell.
	 */
	~Matrix() // todo test
	{
		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.erase(i);
		}
	}

	/**
	 * A move constructor.
	 * This constructor moves a Matrix<T> object from one pointer to another.
	 * @param other The Matrix<T> object that will be moved to the new pointer.
	 * @return The moved Matrix<T> object with it's new address. todo verify what's returned
	 */
	Matrix(Matrix<T>& other) //todo implement
	{

	}


private:
	unsigned int _rows; /** The number of rows in the matrix */
	unsigned int _cols; /** The number of columns in the matrix */
	vector<T> _matrix; /* A pointer to the array of T type objects of the matrix. */
	unsigned int _matrixVectorSize; /** The size of the vector representing the matrix */
};

#endif //EX3_MATRIX_H
