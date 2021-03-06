//
// Created by omri on 9/10/15.
//

#ifndef EX3_BADMEMORYALLOC_HPP
#define EX3_BADMEMORYALLOC_HPP

#include <exception>

/**
 * An exception thrown when memory allocation fails.
 */
class BadMemoryAlloc : public std::exception
{

public:

	/**
	 * A short explanation of the exception.
	 * @return A c_string with the explanation.
	 */
	const char *what() const throw()
	{
		return "Could not allocate memory.";
	}
} BadMemoryAlloc;

#endif //EX3_BADMEMORYALLOC_HPP
