CPPC = g++ -std=c++11
FLAGS = -pthread -Wall -Wextra -Wvla -O -DNDEBUG

ParallelChecker : ParallelChecker.cpp Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp \
                  OutOfMatrixRange.hpp Complex.cpp Complex.h BadMemoryAlloc.hpp
	$(CPPC) $(FLAGS) ParallelChecker.cpp Complex.cpp -o ParallelChecker