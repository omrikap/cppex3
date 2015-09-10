// WrongDimensionsMatrix.hpp

#include <exception>

#ifndef EX3_WRONGDIMENSIONSMATRIX_HPP
#define EX3_WRONGDIMENSIONSMATRIX_HPP

/**
 * An exception thrown when matrix is from dimension zero.
 */
class DimensionZeroMatrix : public std::exception
{

public:

	/**
	 * A short explanation of the exception.
	 * @return A c_string with the explanation.
	 */
	const char *what() const throw()
	{
		return "Cannot perform the operation on a matrix with these dimensions.";
	}
} DimensionZeroMatrix;

#endif //EX3_WRONGDIMENSIONSMATRIX_HPP
