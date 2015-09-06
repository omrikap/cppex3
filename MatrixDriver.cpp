#include <iostream>

#include "Matrix.hpp"

using namespace std;

int main()
{
	cout << "MatrixDriver" << endl;
	// test default constructor
	Matrix<int> matrix;

	// test dimension constructor
	Matrix<int> dimMatrix(3, 4);

	// test copy constructor
	Matrix<int> copiedMatrix(dimMatrix);

	// test move constructor // todo how to test move constructor
//	Matrix<int> movedMatrix(copiedMatrix);

	// test operator=
	matrix = dimMatrix;

	// test destructor
	copiedMatrix.~Matrix();

	// test trace function
	cout << "matrix trace: " << matrix.trace() << endl;

	return 0;
}