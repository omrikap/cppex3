#include <iostream>

#include "Matrix.hpp"

using namespace std;

int main()
{
	cout << "MatrixDriver" << endl;
	Matrix<int> matrix;
	Matrix<int> dimMatrix(3, 4);
	Matrix<int> copiedMatrix(dimMatrix);
	return 0;
}