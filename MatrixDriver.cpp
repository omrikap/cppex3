#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;

int main()
{
	cout << "MatrixDriver" << endl;
//	// test default constructor
//	Matrix<int> matrix;
//
//	// test dimension constructor
//	Matrix<int> dimMatrix(3, 4);
//
//	// test copy constructor
//	Matrix<int> copiedMatrix(dimMatrix);
//
//	// test move constructor // todo how to test move constructor
////	Matrix<int> movedMatrix(copiedMatrix);
//
//	// test operator=
//	matrix = dimMatrix;
//
//	// test trace function
////	matrix.trace(); // test throw
//	Matrix<int> squareMatrix(3, 3);
//	cout << "Square Matrix Trace: " << squareMatrix.trace() << endl;
//
//	// test << operator
//	cout << matrix << endl;
//
//	// test cells constructor todo what happens if the vector not in the right size?
//	vector<int> tempVec;
//	tempVec.push_back(10);
//	tempVec.push_back(13);
//	tempVec.push_back(15);
//	tempVec.push_back(2);
//	tempVec.push_back(5);
//	tempVec.push_back(20);
//	Matrix<int> cellsMat(2, 3, tempVec);
//	cout << cellsMat << endl;
//
//	// test *= operator
//	int tArr[] = {1, 2, 3, 4};
//
//	vector<int> ourVec(tArr, (tArr + sizeof(int) * 4));
//	Matrix<int> ourMat(2, 2, ourVec);
//	Matrix<int> otherMat(2, 2, ourVec);
//	ourMat *= otherMat;
//	cout << "ourMat" << ourMat << endl;
//
//	// test setParallel
//	Matrix<int>::setParallel(true);
//
//	// test + parallel
//	matrix = ourMat + otherMat;
//	cout << matrix << endl;
//
//	// test * parallel
//	matrix = ourMat * otherMat;
//	cout << matrix << endl;
//
//	// test * linear
//	Matrix<int> newMat;
//	Matrix<int>::setParallel(false);
//	newMat = ourMat * otherMat;
//	cout << newMat << endl;

	// test * linear
	Matrix<int>::setParallel(false);
	int lArr[] = {1, 2, 3, 4};
	int rArr[] = {5, 6, 7, 8};

	vector<int> lVec(lArr, lArr + sizeof(int) * 4);
	vector<int> rVec(rArr, rArr + sizeof(int) * 4);

	Matrix<int> lMatrix(2, 2, lVec);
	Matrix<int> rMatrix(2, 2, rVec);
	Matrix<int> resMatrix(2, 2);

//	lMatrix *= rMatrix;
	Matrix<int>::setParallel(true);
	resMatrix = lMatrix * rMatrix;
	cout << "resMatrix:\n" << resMatrix << endl;


	for (Matrix<int>::const_iterator it = resMatrix.begin(); it != resMatrix.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}