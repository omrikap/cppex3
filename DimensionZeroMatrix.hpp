// WrongDimensionsMatrix.hpp

#include <exception>

#ifndef EX3_WRONGDIMENSIONSMATRIX_HPP
#define EX3_WRONGDIMENSIONSMATRIX_HPP

class DimensionZeroMatrix : public std::exception
{

public:
	const char *what() const throw()
	{
		return "Cannot perform the operation on a matrix with these dimensions.";
	}
} DimensionZeroMatrix;

#endif //EX3_WRONGDIMENSIONSMATRIX_HPP
