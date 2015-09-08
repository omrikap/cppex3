// OutOfMatrixRange.hpp

#include <exception>

#ifndef EX3_OUTOFMATRIXRANGE_HPP
#define EX3_OUTOFMATRIXRANGE_HPP

class OutOfMatrixRange : public std::exception
{

public:
	const char *what() const throw()
	{
		return "Trying to reach a cell out of the matrix's range.";
	}
} OutOfMatrixRange;

#endif //EX3_OUTOFMATRIXRANGE_HPP
