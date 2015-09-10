// WrongMatrixDimensions.hpp

#ifndef EX3_WRONGMATRIXDIMENSIONS_HPP
#define EX3_WRONGMATRIXDIMENSIONS_HPP

#include <exception>

class WrongMatrixDimensions : public std::exception
{

public:
	const char *what() const throw()
	{
		return "Can't perform this operation with a matrix of these dimensions.";
	}
} WrongMatrixDimensions;

#endif //EX3_WRONGMATRIXDIMENSIONS_HPP
