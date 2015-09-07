// MatrixNotSquare.hpp

#include <exception>

#ifndef EX3_MATRIXNOTSQUARE_HPP
#define EX3_MATRIXNOTSQUARE_HPP

class MatrixNotSquare : public std::exception
{

public:
	const char *what() const throw()
	{
		return "Cannot perform the operation on a matrix that is not square.";
	}
} MatrixNotSquare;

#endif //EX3_MATRIXNOTSQUARE_HPP
