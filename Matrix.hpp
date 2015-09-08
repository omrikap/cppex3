// Matrix.hpp

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <vector>
#include <iterator>
#include <thread>
#include "Complex.h"
#include "MatrixNotSquare.hpp"
#include "DimensionZeroMatrix.hpp"
#include "OutOfMatrixRange.hpp"

using namespace std; // todo remove

template <class T>
class Matrix
{
public:

//-------------------------------------- constructors ---------------------------------------------

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
	 * A move constructor.
	 * This constructor moves a Matrix<T> object from one pointer to another.
	 * @param other The Matrix<T> object that will be moved to the new pointer.
	 */
	Matrix(Matrix<T>&& other) :_rows(other._rows), _cols(other._cols), _matrixVectorSize
	(other._matrixVectorSize)
	{
		_rows = move(other._rows);
		_cols = move(other._cols);
		_matrix = move(other._matrix);
		_matrixVectorSize = move(other._matrixVectorSize);
	}

	/**
	 * A constructor that get the dimensions of the new Matrix and its values as a vector.
	 * @param rows The number of rows for the new Matrix.
	 * @param rows The number of columns for the new Matrix.
	 * @param cells A const reference to a vector of T objects.
	 * @return A Matrix object with the specified number of rows and columns, that is initialized
	 *         with the zeros of the type T.
	 */
	Matrix(unsigned int rows, unsigned int cols, const vector<T>& cells) : _rows(rows), _cols
			(cols), _matrixVectorSize(rows * cols) // fixme coding style
	{
		// verify the vector not exceed the matrix size.
		if (cells.size() > _matrixVectorSize)
		{
			throw OutOfMatrixRange;
		}

		// allocate the exact amount of memory
		_matrix.resize(_matrixVectorSize);

		// initialize the matrix cells
		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.at(i) = cells.at(i);
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

//--------------------------------------- operators -----------------------------------------------

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
	}

	// todo move assignement operator? gets rValue

	/**
     * The += operator.
     * Add the matrix on the right side of the operator from this matrix (on the left side).
     * @param other A reference to a matrix<T> object.
     * @return A reference to this Matrix<T>.
     */
	Matrix<T>& operator+=(const Matrix<T> &other)
	{
		if (_rows != other._rows || _cols != other._cols)
		{
			throw
		}

		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.at(i) += other._matrix.at(i);
		}

		return *this;
	}

	/**
     * The -= operator.
     * Subtract the matrix on the right side of the operator from this matrix (on the left side).
     * @param other A reference to a matrix<T> object.
     * @return A reference to this Matrix<T>.
     */
	Matrix<T>& operator-=(const Matrix<T> &other)
	{
		for (int i = 0; i < _matrixVectorSize; ++i)
		{
			_matrix.at(i) -= other._matrix.at(i);
		}

		return *this;
	}

	/**
     * The *= operator.
     * Multiply the matrix on the right side of the operator with this matrix (on the left side).
     * @param other A reference to a matrix<T> object.
     * @return A reference to this Matrix<T>.
     */
	Matrix<T>& operator*=(const Matrix<T> &other)
	{
		_matrix.resize(_rows * other._cols, 0);
		for (int row = 0; row < _rows; ++row)
		{
			for (int otherCol = 0; otherCol < other._cols; ++otherCol)
			{
				int dotProduct = 0;
				for (int col = 0; col < _cols; ++col)
				{
					dotProduct += _matrix.at((row * _cols) + col) * other._matrix.at((col *
							other._cols) + otherCol);
				}
				_matrix.at(row * _rows + otherCol) = dotProduct;
			}
		}
		_cols = other._cols;
		return *this;
	}

	/**
	 * The + operator.
	 * Calculate the sum of two matrices.
	 * @param other A reference to another Matrix<T> object.
	 * @return Matrix<T> object which is the sum of the two matrices.
	 */
	const Matrix<T> operator+(const Matrix<T> &other)
	{
		if (_multiThread)
		{
			Matrix<T> result = *this;
			result += other;
			return result;
		}
		else
		{
			Matrix<T> res(_rows, _cols);
			vector<thread> threadVector;

			for (unsigned int i = 0; i < _rows; ++i)
			{
				threadVector.push_back(std::thread(oneLineAddition(i, *this, other, res)));
			}
			for (thread t : threadVector)
			{
				t.join();
			}
			return res;
		}
	}

	/**
	 * The - operator.
	 * Calculate the difference of two matrices.
	 * @param other A reference to another Matrix<T> object.
	 * @return Matrix<T> object which is the difference of the two matrices.
	 */
	const Matrix<T> operator-(const Matrix<T> &other)
	{
		Matrix<T> result = *this;
		result -= other;
		return result;
	}

	/**
	 * The * operator.
	 * Calculate the product of two matrices.
	 * @param other A reference to another Matrix<T> object.
	 * @return Matrix<T> object which is the product of the two matrices.
	 */
	const Matrix<T> operator*(const Matrix<T> &other)
	{
		Matrix<T> result = *this;
		result *= other;
		return result;
	}

	bool operator==(const Matrix<T> &other) const
	{
		return other._matrix == _matrix;

//		if(other._matrixVectorSize != _matrixVectorSize) // fixme
//		{
//			return false;
//		}
//
//		if(other._cols != _cols)
//		{
//			return false;
//		}
//
//		if(other._rows != _rows)
//		{
//			return false;
//		}

	}

	bool operator!=(const Matrix<T> &other) const
	{
		return !(*this == other);
	}

	/**
	 * The () operator.
	 * Access the [int, int] cell of the matrix.
	 * @return A reference to the specified location in the matrix.
	 */
	T& operator()(unsigned int row, unsigned int col)
	{
		if (row * _cols + col >= _matrixVectorSize)
		{
			throw OutOfMatrixRange;
		}

		return _matrix.at(row * _cols + col); // todo test
	}

	/**
	 * The () operator.
	 * Access the [int, int] cell of the matrix.
	 * @return A copy of to the specified location in the matrix.
	 */
	T operator()(unsigned int row, unsigned int col) const
	{
		if (row * _cols + col >= _matrixVectorSize)
		{
			throw OutOfMatrixRange;
		}

		return _matrix.at(row * _cols + col); // todo test
	}

//------------------------------------ methods ----------------------------------------------------

	/**
	 * Transpose this matrix.
	 * @return A new Matrix<T> instance which is the transposition of the given matrix.
	 */
	Matrix<T> trans()
	{
		if ((_rows == 0) || (_cols == 0))
		{
			throw OutOfMatrixRange;
		}

		// create a vector for the transposed matrix cells, and allocate exact memory size
		vector<T> transposed;
		transposed.resize(_matrixVectorSize);

		// transpose the matrix
		for (int row = 0; row < _rows; ++row)
		{
			for (int col = 0; col < _cols; ++col)
			{
				transposed.at((col * _rows) + row) = _matrix.at((row * _cols) + col);
			}
		}

		// return a new transposed matrix
		return Matrix<T>(_cols, _rows, transposed);
	}

	// todo Complex trans

	/**
	 * @brief Calculate the trace of a square matrix.
	 * @return int The trace of the calling matrix.
	 * @throws DimensionZeroMatrix, when the matrix's dimensions are zero.
	 * @throws MatrixNotSquare exception, when the matrix is not square.
	 */
	T trace() const
	{
		if ((_rows == 0) || (_cols == 0))
		{
			throw DimensionZeroMatrix;
		}

		if (_rows != _cols)
		{
			throw MatrixNotSquare;
		}

		T theTrace = T(0);
		for (int i = 0; i < _rows; ++i)
		{
			theTrace += _matrix[i*_rows + i];
		}
		return theTrace;
	}

	/**
	 * Swap two matrices.
	 * @param first The first matrix.
	 * @param second The second matrix.
	 */
	friend void swap(Matrix<T>& first, Matrix<T>& second) // todo why error?
	{
		using std::swap;
		swap(first._rows, second._rows);
		swap(first._cols, second._cols);
		swap(first._matrixVectorSize, second._matrixVectorSize);
		swap(first._matrix, second._matrix);
	}

	static void setParallel(bool setter) // todo if-cosmetics
	{
		if (setter)
		{
			_multiThread = true;

			if (!_multiThread)
			{
				cout << "_multithread is true" << endl;
			}
		}
		else
		{
			_multiThread = false;

			if (_multiThread)
			{
				cout << "_multithread is true" << endl;
			}
		}
	}

//-------------------------------- access - methods -----------------------------------------------

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

	/**
	 * A getter to the matrix vector size.
	 * @return unsinged int The number of cells.
	 */
	unsigned int vectorLength() const
	{
		return _matrixVectorSize;
	}

	/**
	 * A getter to the matrix vector.
	 * @return vector<T> The vector holding the matrix objects.
	 */
	vector<T> matrixVector() const
	{
		return _matrix;
	}

	/**
	 * An iterator at the beginning of the matrix.
	 * @return iterator
	 */
	const iterator begin() // todo test, add const function?
	{
		return _matrix.begin();
	}

	/**
	 * An iterator at the end of the matrix.
	 * @return iterator
	 */
	const iterator end() // todo test, add const function?
	{
		return _matrix.end();
	}

private:

//------------------------------------- data - members --------------------------------------------

	unsigned int _rows; /** The number of rows in the matrix */
	unsigned int _cols; /** The number of columns in the matrix */
	unsigned int _matrixVectorSize; /** The size of the vector representing the matrix */
	vector<T> _matrix; /** A pointer to the array of T type objects of the matrix. */
	static bool _multiThread = false;

	/**
	 * A helper function to perform the line addition in the multi-threaded addition operator.
	 * @param row The number of row to sum.
	 * @param lMatrix The matrix to the left of the operator.
	 * @param rMatrix The matrix to the right of the operator.
	 * @param res The matrix that will hold the sum of lMatrix and rMatrix.
	 */
	static void oneLineAddition(unsigned int row, const Matrix<T> &lMatrix,
	                            const Matrix<T> &rMatrix, Matrix<T> &res)
	{
		for (unsigned int i = 0; i < res.cols(); ++i)
		{
			res(row, i) = rMatrix(row, i) + lMatrix(row, i);
		}
	}
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

			os << matrix.matrixVector().at(i * matrix.cols() + j);
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
