// MatrixNotSquare.hpp

#include <exception>

#ifndef EX3_MATRIXNOTSQUARE_HPP
#define EX3_MATRIXNOTSQUARE_HPP

/**
 * An exception of a not square matrix.
 * Thrown when tying to perform operations relevant only for square matrices.
 */
class MatrixNotSquare : public std::exception
{

public:

	/**
	 * A short explanation of the exception.
	 * @return A c_string with the explanation.
	 */
	const char *what() const throw()
	{
		return "Cannot perform the operation on a matrix that is not square.";
	}
} MatrixNotSquare;

#endif //EX3_MATRIXNOTSQUARE_HPP
