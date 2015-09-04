// IntMatrix.h

#ifndef EX1_INTMATRIX_H
#define EX1_INTMATRIX_H

#include <iosfwd>

using namespace std;

/**
 * A class that represent a matrix of integers.
 */
class IntMatrix
{
public:
	/**
	 * @brief The default constructor.
	 */
	IntMatrix();

	/**
	 * @brief A copy constructor.
	 * @param other The matrix to copy.
	 */
	IntMatrix(const IntMatrix& other);

	/**
	 * @brief A destructor.
	 */
	~IntMatrix();

	/**
	 * @brief A constructor for the binary arithmetic operators. Creates a zero matrix from the
	 * 		  given row and column size.
	 * @param rows The number of rows for the matrix.
	 * @param cols The number of columns for the matrix.
	 */
	IntMatrix(const int rows, const int cols);

	/**
	 * @brief IntMatrix constructor.
	 * @param rows The number of rows in the matrix.
	 * @param cols The number of columns in the matrix.
	 */
	IntMatrix(const int rows, const int cols, int *matrixArray);

	/**
	 * @brief The '=' operator.
	 * @param other The matrix to use on the right side of the '='.
	 */
	IntMatrix& operator=(const IntMatrix &other);

	/**
	 * @brief IntMatrix compound addition operator.
	 * @param other The matrix on the right hand side of the operator. Will be added to the matrix
	 * 				on the left hand side.
	 * @return A reference to the calling matrix (the matrix on the left hand side of the
	 * 		   operator).
	 */
	IntMatrix& operator+=(const IntMatrix &other);

	/**
	 * @brief IntMatrix compound reduction operator.
	 * @param other The matrix on the right hand side of the operator. Will be subtract from the
	 * 	 		 	matrix on the left hand side.
	 * @return A reference to the calling matrix (the matrix on the left hand side of the
	 * 		   operator).
	 */
	IntMatrix& operator-=(const IntMatrix &other);

	/**
 * @brief IntMatrix compound multiplication operator.
 * @param other The matrix on the right hand side of the operator. Will be multiplied (from
 * 				the right) with the matrix on the left hand side.
 * @return A reference to the calling matrix (the matrix on the left hand side of the
 * 		   operator).
 */
	IntMatrix& operator*=(const IntMatrix &other);

	/**
	 * @brief The addition operator. Calculates the sum of two matrices.
	 * @param right The matrix on the right of the '+'.
	 */
	const IntMatrix operator+(const IntMatrix &other);

	/**
	 * @brief The subtraction operator. Calculates the difference between two matrices.
	 * @param right The matrix on the right of the '-'.
	 */
	const IntMatrix operator-(const IntMatrix &other);

	/**
	 * @brief The multiplication operator. Calculates the product of two matrices.
	 * @param other The matrix on the right of the '*'.
	 */
	const IntMatrix operator*(const IntMatrix &other);

	/**
	 * @brief
	 */
	friend ostream& operator<<(ostream &os, const IntMatrix &matrix);

	/**
	 * @brief Transpose an IntMatrix.
	 * @param matrix The matrix to transpose.
	 * @return A new IntMatrix instance which is the transposition of the given matrix.
	 */
	IntMatrix trans();

	/**
	 * @brief Calculate the trace of a square matrix. Behavior for non-sqare matrices is
	 * 		  undefined.
	 * @return int The trace of the calling matrix.
	 */
	int trace();

	/**
	 * @brief rows getter.
	 * @return int Number of rows.
	 */
	int getRows();

	/**
	 * @brief cols getter.
	 * @return int Number of rows.
	 */
	int getCols();

private:
	int _rows; /* the number of rows of the matrix. */
	int _cols; /* the number of columns of the matrix. */
	int *_matrix; /* A pointer to the int array of the matrix. */
};

#endif //EX1_INTMATRIX_H
