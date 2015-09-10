// Matrix.hpp

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

//---------------------------------- const and includes -------------------------------------------

#include <vector>
#include <iterator>
#include <thread>
#include "Complex.h"
#include "MatrixNotSquare.hpp"
#include "DimensionZeroMatrix.hpp"
#include "OutOfMatrixRange.hpp"
#include "BadMemoryAlloc.hpp"
#include "WrongMatrixDimensions.hpp"

#define INIT_LENGTH 1
#define T_CLASS_ZETO 0

using namespace std;

enum functionType
{
	SUM,
	MULT
};

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
	Matrix() try : _rows(INIT_LENGTH), _cols(INIT_LENGTH), _matrixVectorSize(INIT_LENGTH),
	               _data(_matrixVectorSize, T(T_CLASS_ZETO))
	{

	}
	catch (bad_alloc)
	{
		throw BadMemoryAlloc;
	}

	/**
	 * A constructor that get the dimensions of the new Matrix.
	 * @param rows The number of rows for the new Matrix.
	 * @param rows The number of columns for the new Matrix.
	 * @return A Matrix object with the specified number of rows and columns, that is initialized
	 *         with the zeros of the type T.
	 */
	Matrix(unsigned int rows, unsigned int cols) try : _rows(rows), _cols(cols),
	                                                   _matrixVectorSize(rows * cols),
	                                                   _data(_matrixVectorSize, T(T_CLASS_ZETO))
	{

	}
	catch (bad_alloc)
	{
		throw BadMemoryAlloc;
	}

	/**
	 * A copy constructor.
	 * This constructor creates a new copy of a Matrix<T> object.
	 * @param other The Matrix object to be copied.
	 * @return A new Matrix object that is a copy of the other Matrix object.
	 */
	Matrix(const Matrix<T>& other) try : _rows(other._rows), _cols(other._cols),
	                                     _matrixVectorSize(other._matrixVectorSize),
	                                     _data(other._data)
	{

	}
	catch (bad_alloc)
	{
		throw BadMemoryAlloc;
	}

	/**
	 * A move constructor.
	 * This constructor moves a Matrix<T> object from one pointer to another.
	 * @param other The Matrix<T> object that will be moved to the new pointer.
	 */
	Matrix(Matrix<T>&& other) try :_rows(std::move(other._rows)), _cols(std::move(other._cols)),
	                           _matrixVectorSize(std::move(other._matrixVectorSize)),
	                           _data(std::move(other._data))
	{

	}
	catch (bad_alloc)
	{
		throw BadMemoryAlloc;
	}


	/**
	 * A constructor that get the dimensions of the new Matrix and its values as a vector.
	 * @param rows The number of rows for the new Matrix.
	 * @param rows The number of columns for the new Matrix.
	 * @param cells A const reference to a vector of T objects.
	 * @return A Matrix object with the specified number of rows and columns, that is initialized
	 *         with the zeros of the type T.
	 */
	Matrix(unsigned int rows, unsigned int cols, const vector<T>& cells) try : _rows(rows),
	                                                                       _cols(cols),
	                                                                       _matrixVectorSize(rows * cols),
	                                                                       _data(cells)
	{

	}
	catch (bad_alloc)
	{
		throw BadMemoryAlloc;
	}

	/**
	 * The Matrix class destructor.
	 * Destructs the elements of the vector containing the matrix object cell.
	 */
	~Matrix()
	{
		_data.clear(); // todo needed? check with valgrind.
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
			throw WrongMatrixDimensions;
		}

		for (unsigned int i = 0; i < _matrixVectorSize; ++i)
		{
			_data.at(i) += other._data.at(i);
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
			_data.at(i) -= other._data.at(i);
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
		// create a new vector of the result size to store the result
		vector<T> resVector((size_t)_rows * other._cols);

		// multiply matrices
		for (unsigned int row = 0; row < _rows; ++row)
		{
			for (unsigned int otherCol = 0; otherCol < other._cols; ++otherCol)
			{
				T dotProduct = 0;
				for (unsigned int col = 0; col < _cols; ++col)
				{
					dotProduct += (*this)(row, col) * other(col, otherCol);
				}
				resVector.at(row * _rows + otherCol) = dotProduct;
			}
		}

		// put result vector instead of previous vector, and update the columns and vector length
		swap(_data, resVector);
		_cols = other._cols;
		_matrixVectorSize = _rows * _cols;

		return *this;
	}

	/**
	 * This function prevents code duplication.
	 * Performing parallel summing or multiplication.
	 * @param function Enum functionType to determine the function that will be executed in
	 *        parallel mode
	 * @param other A const reference to the matrix to the right of the operator.
	 * @return const Matrix<T> the result of the operation performed.
	 */
	const Matrix<T> parallelHelper(const functionType function, const Matrix<T> &other) const
	{
		Matrix<T> res(_rows, _cols);
		vector<thread> threadVector;

		switch (function)
		{
			case SUM:
				for (unsigned int i = 0; i < _rows; ++i)
				{
					threadVector.push_back(thread(oneLineAddition, i, ref(*this),
					                              ref(other), ref(res)));
				}
			case MULT:
				for (unsigned int i = 0; i < _rows; ++i)
				{
					threadVector.push_back(thread(oneLineMultiplication, i, ref(*this),
					                              ref(other), ref(res)));
				}
		}

		for (unsigned int j = 0; j < threadVector.size(); ++j)
		{
			threadVector.at(j).join();
		}
		return res;
	}

	/**
	 * The + operator.
	 * Calculate the sum of two matrices.
	 * @param other A reference to another Matrix<T> object.
	 * @return Matrix<T> object which is the sum of the two matrices.
	 */
	const Matrix<T> operator+(const Matrix<T> &other) const
	{
		if (!s_parallel)
		{
			Matrix<T> result = *this;
			result += other;
			return result;
		}
		else
		{
			return parallelHelper(functionType::SUM, other);
		}
	}

	/**
	 * The - operator.
	 * Calculate the difference of two matrices.
	 * @param other A reference to another Matrix<T> object.
	 * @return Matrix<T> object which is the difference of the two matrices.
	 */
	const Matrix<T> operator-(const Matrix<T> &other) const
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
	const Matrix<T> operator*(const Matrix<T> &other) const
	{
		if (!s_parallel)
		{
			Matrix<T> result = *this;
			result *= other;
			return result;
		}
		else
		{
			return parallelHelper(functionType::MULT, other);
		}
	}

	/**
	 * The == operator.
	 * Check the equality of two matrices.
	 * @return bool true if the matrices are equal, false else.
	 */
	bool operator==(const Matrix<T> &other) const
	{
		if(other._matrixVectorSize != _matrixVectorSize)
		{
			return false;
		}

		if(other._cols != _cols)
		{
			return false;
		}

		if(other._rows != _rows)
		{
			return false;
		}

		return other._data == _data;
	}

	/**
	 * The != operator.
	 * Check the inequality of two matrices.
	 * @return bool true if the matrices are not equal, false else.
	 */
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

		return _data.at(row * _cols + col);
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

		return _data.at(row * _cols + col);
	}

//------------------------------------ methods ----------------------------------------------------

	/**
	 * Transpose this matrix.
	 * @return A new Matrix<T> instance which is the transposition of the given matrix.
	 */
	const Matrix<T> trans() const
	{
		if ((_rows == 0) || (_cols == 0))
		{
			throw OutOfMatrixRange;
		}

		// create a vector for the transposed matrix cells, and allocate exact memory size
		vector<T> transposed;
		transposed.resize(_matrixVectorSize);

		// transpose the matrix
		for (unsigned int row = 0; row < _rows; ++row)
		{
			for (unsigned int col = 0; col < _cols; ++col)
			{
				transposed.at((col * _rows) + row) = _data.at((row * _cols) + col);
			}
		}

		// return a new transposed matrix
		return Matrix<T>(_cols, _rows, transposed);
	}

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
		for (unsigned int i = 0; i < _rows; ++i)
		{
			theTrace += _data[i*_rows + i];
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
		swap(first._data, second._data);
	}

	/**
	 * A static function to select parallel computation mod.
	 * @param setter A boolean value to determine the parallel mod.
	 */
	static void setParallel(bool setter) // todo test
	{
		if (setter == s_parallel)
		{
			return;
		}
		else if (setter)
		{
			s_parallel = true;
			std::cout << "Generix Matrix mode changed to parallel mode\n";
		}
		else
		{
			s_parallel = false;
			std::cout << "Generix Matrix mode changed to non-parallel mode\n";
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
		return _data;
	}

	bool isSquareMatrix() const
	{
		return (_rows == _cols);
	}

	typedef typename std::vector<T>::iterator iterator; /** An iterator type */
	typedef typename std::vector<T>::const_iterator const_iterator; /** A constant iterator type */

	/**
	 * An iterator at the beginning of the matrix.
	 * @return iterator
	 */
	iterator begin()
	{
		return _data.begin();
	}

	/**
	 * An iterator at the end of the matrix.
	 * @return iterator
	 */
	iterator end()
	{
		return _data.end();
	}

	/**
	 * An iterator at the beginning of the matrix.
	 * @return iterator
	 */
	const_iterator begin() const
	{
		return _data.cbegin();
	}

	/**
	 * An iterator at the end of the matrix.
	 * @return iterator
	 */
	const_iterator end() const
	{
		return _data.cend();
	}

private:

//------------------------------------ private - methods ------------------------------------------

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

	/**
	 * A helper function to perform the line multiplication in the parallel mode mltiplication.
	 * @param row The number of row to sum.
	 * @param lMatrix The matrix to the left of the operator.
	 * @param rMatrix The matrix to the right of the operator.
	 * @param res The matrix that will hold the sum of lMatrix and rMatrix.
	 */
	static void oneLineMultiplication(unsigned int row, const Matrix<T> &lMatrix,
	                                  const Matrix<T> &rMatrix, Matrix<T> &res)
	{
		for (unsigned int rMatrixCol = 0; rMatrixCol < rMatrix.cols(); ++rMatrixCol)
		{
			T dotProduct = 0;
			for (unsigned int lMatrixCol = 0; lMatrixCol < lMatrix.cols(); ++lMatrixCol)
			{
				dotProduct += lMatrix(row, lMatrixCol) * rMatrix(lMatrixCol, rMatrixCol);
			}
			res(row, rMatrixCol) = dotProduct;
		}
	}

//------------------------------------- data - members --------------------------------------------

	unsigned int _rows; /** The number of rows in the matrix */
	unsigned int _cols; /** The number of columns in the matrix */
	unsigned int _matrixVectorSize; /** The size of the vector representing the matrix */
	vector<T> _data; /** A pointer to the array of T type objects of the matrix. */
	static bool s_parallel; /** Static flag for multi threaded calculation */
};

//------------------------------------- end-of-class ----------------------------------------------

template <>
const Matrix<Complex> Matrix<Complex>::trans() const
{
	if ((_rows == 0) || (_cols == 0))
	{
		throw OutOfMatrixRange;
	}

	// create a vector for the transposed matrix cells, and allocate exact memory size
	vector<Complex> transposed;
	transposed.resize(_matrixVectorSize);

	// transpose the matrix
	for (unsigned int row = 0; row < _rows; ++row)
	{
		for (unsigned int col = 0; col < _cols; ++col)
		{
			transposed.at((col * _rows) + row) = _data.at((row * _cols) + col).conj();
		}
	}

	// return a new transposed matrix
	return Matrix<Complex>(_cols, _rows, transposed);
}

template <class T>
bool Matrix<T>::s_parallel = false;

/**
 * The << operator.
 * Used to print the matrix with cout.
 * @return ostream reference With a formatted text version of the matrix.
 */
template <class T>
ostream& operator<<(ostream &os, const Matrix<T> &matrix)
{
	os << endl;
	for (unsigned int i = 0; i < matrix.rows(); ++i)
	{
		for (unsigned int j = 0; j < matrix.cols(); ++j)
		{
			os << matrix.matrixVector().at(i * matrix.cols() + j) << "      ";
		}
		os << endl;
	}
	return os;
}

#endif //EX3_MATRIX_H
