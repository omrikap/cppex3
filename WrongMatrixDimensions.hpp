// WrongMatrixDimensions.hpp

#ifndef EX3_WRONGMATRIXDIMENSIONS_HPP
#define EX3_WRONGMATRIXDIMENSIONS_HPP

#include <exception>

/**
 * An exception for matrix in wrong dimensions.
 */
class WrongMatrixDimensions : public std::exception
{

public:

	/**
	 * A short explanation of the exception.
	 * @return A c_string with the explanation.
	 */
	const char *what() const throw()
	{
		return "Can't perform this operation with a matrix of these dimensions.";
	}
} WrongMatrixDimensions;

#endif //EX3_WRONGMATRIXDIMENSIONS_HPP
