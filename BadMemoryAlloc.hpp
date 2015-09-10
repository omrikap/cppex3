//
// Created by omri on 9/10/15.
//

#ifndef EX3_BADMEMORYALLOC_HPP
#define EX3_BADMEMORYALLOC_HPP

#include <exception>

class BadMemoryAlloc : public std::exception
{

public:
	const char *what() const throw()
	{
		return "Could not allocate memory.";
	}
} BadMemoryAlloc;

#endif //EX3_BADMEMORYALLOC_HPP
