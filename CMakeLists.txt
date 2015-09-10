cmake_minimum_required(VERSION 3.3)
project(ex3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -Wall -Wextra -Wvla")

set(SOURCE_FILES GenericMatrixDriver.cpp Matrix.hpp MatrixNotSquare.hpp DimensionZeroMatrix.hpp
        OutOfMatrixRange.hpp Complex.cpp Complex.h BadMemoryAlloc.hpp WrongMatrixDimensions.hpp)
add_executable(ex3 ${SOURCE_FILES})