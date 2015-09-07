// Matrix.hpp

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <vector>
#include "MatrixNotSquare.hpp"

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
	~Matrix()
	{
		_matrix.clear(); // todo needed? check with valgrind.
	}

	/**
	 * A move constructor.
	 * This constructor moves a Matrix<T> object from one pointer to another.
	 * @param other The Matrix<T> object that will be moved to the new pointer.
	 * @return The moved Matrix<T> object with it's new address. todo verify what's returned
	 */
	Matrix(Matrix<T>&& other) :_rows(other._rows), _cols(other._cols), _matrixVectorSize
	(other._matrixVectorSize) // todo test
	{
		_rows = move(other._rows);
		_cols = move(other._cols);
		_matrixVectorSize = move(other._matrixVectorSize);
		_matrix = move(other._matrix);

//		for (int i = 0; i < _matrixVectorSize; ++i) // todo remove
//		{
//			_matrix.push_back(other._matrix[i]);
//		}
//
//		// reset other
//		other._rows = 1;
//		other._cols = 1;
//		other._matrixVectorSize = 1;
//		other._matrix.clear();
//		other._matrix.push_back(1);
	}

	/**
	 * Assignment operator.
	 * This operator initializes the data members of this matrix with the data members of the
	 * other matrix.
	 * @param other A reference to the other matrix.
	 * @return A reference to this matrix.
	 */
	Matrix<T>& operator=(Matrix<T> other)
	{
		swap(*this, other);
		return *this;

//		// in case of self assignment, just return the same object. // todo remove
//		if (this != &other)
//		{
//			// initialize this matrix data members from the other matrix.
//			_rows = other._rows;
//			_cols = other._cols;
//			_matrixVectorSize = other._matrixVectorSize;
//
//			// clear the vector from current data.
//			_matrix.clear();
//
//			// copy the matrix elements from the other matrix to the new one.
//			for (int i = 0; i < _matrixVectorSize; ++i)
//			{
//				_matrix.push_back(other._matrix[i]);
//			}
//		}
//		return *this;
	}

	const Matrix<T> operator+(const Matrix<T> &other) // todo return type? implement +=?
	{

	}

	/**
	 * @brief Calculate the trace of a square matrix.
	 * @return int The trace of the calling matrix.
	 * @throws MatrixNotSquare exception, when the matrix is not square.
	 */
	T trace()
	{
		if (_rows != _cols)
		{
			cout << "not a squre matrix!" << endl; // todo remove
			throw MatrixNotSquare;
		}
		T theTrace = T(0);
		for (int i = 0; i < _rows; ++i)
		{
			theTrace += _matrix[i*_rows + i];
		}
		return theTrace;
	}

	friend void swap(Matrix<T>& first, Matrix<T>& second) // todo test
	{
		using std::swap;
		swap(first._rows, second._rows);
		swap(first._cols, second._cols);
		swap(first._matrixVectorSize, second._matrixVectorSize);
		swap(first._matrix, second._matrix);
	}

	/**
	 * A getter for the number of rows of the matrix
	 * @return unsinged int The number of rows.
	 */
	unsigned int rows() const
	{
		return _rows;
	}

	/**
	 * A getter for the number of columns of the matrix
	 * @return unsinged int The number of columns.
	 */
	unsigned int cols() const
	{
		return _cols;
	}

	vector<T> matrixVector() const
	{
		return _matrix;
	}

private:
	unsigned int _rows; /** The number of rows in the matrix */
	unsigned int _cols; /** The number of columns in the matrix */
	unsigned int _matrixVectorSize; /** The size of the vector representing the matrix */
	vector<T> _matrix; /** A pointer to the array of T type objects of the matrix. */
};

/**
     * The << operator.
     * Used to print the matrix with cout.
     * @return ostream reference With a formatted text version of the matrix.
     */
template <class T>
ostream& operator<<(ostream &os, const Matrix<T> &matrix) // todo fix formatting
{
	os << endl;
	for (int i = 0; i < matrix.rows(); ++i)
	{
		for (int j = 0; j < matrix.cols(); ++j)
		{
			const int LAST_ELEMENT = matrix.cols() - 1;

			os << matrix.matrixVector()[i * matrix.cols() + j];
			if (j < LAST_ELEMENT)
			{
				os << "    ";
			}
		}
		os << endl;
	}
	return os;
}

#endif //EX3_MATRIX_H
