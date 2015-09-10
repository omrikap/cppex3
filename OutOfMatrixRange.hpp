// OutOfMatrixRange.hpp

#ifndef EX3_OUTOFMATRIXRANGE_HPP
#define EX3_OUTOFMATRIXRANGE_HPP

#include <exception>

/**
 * An exception of calling to a cell out of the bounds of a matrix.
 */
class OutOfMatrixRange : public std::exception
{

public:

	/**
	 * A short explanation of the exception.
	 * @return A c_string with the explanation.
	 */
	const char *what() const throw()
	{
		return "Trying to reach a cell out of the matrix's range.";
	}
} OutOfMatrixRange;

#endif //EX3_OUTOFMATRIXRANGE_HPP
