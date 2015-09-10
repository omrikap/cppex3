CPPC = g++ -std=c++11
FLAGS = -pthread -Wall -Wextra -Wvla

.PHONY clean main tar

main : Matrix

Matrix : Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp OutOfMatrixRange.hpp Complex.cpp \
         Complex.h BadMemoryAlloc.hpp WrongMatrixDimensions.hpp
	$(CPPC) $(FLAGS) Matrix.hpp

clean : Matrix
	rm -f *.gch ex3.tar ParallelChecker

tar : Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp OutOfMatrixRange.hpp \
      BadMemoryAlloc.hpp WrongMatrixDimensions.hpp
	tar vcf ex3.tar Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp OutOfMatrixRange.hpp \
                    BadMemoryAlloc.hpp WrongMatrixDimensions.hpp

ParallelChecker : ParallelChecker.cpp Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp \
                  OutOfMatrixRange.hpp Complex.cpp Complex.h BadMemoryAlloc.hpp
	$(CPPC) $(FLAGS) -O -DNDEBUG ParallelChecker.cpp Complex.cpp -o ParallelChecker