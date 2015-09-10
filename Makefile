CPPC = g++ -std=c++11
FLAGS = -lpthread -Wall -Wextra

ParallelChecker : ParallelChecker.cpp Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp \
                  OutOfMatrixRange.hpp Complex.cpp Complex.h BadMemoryAlloc.hpp
	CPPC FLAGS ParallelChecker.cpp Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp \
                       OutOfMatrixRange.hpp Complex.cpp BadMemoryAlloc.hpp -o ParallelChecker