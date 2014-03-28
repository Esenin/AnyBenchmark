#include "matrixMultiplier.h"

MatrixMultiplier::MatrixMultiplier()
	: mMatrixSize(10)
	, mA(NULL)
	, mB(NULL)
	, mC(NULL)
{
}

MatrixMultiplier::~MatrixMultiplier()
{
	clear();
}

void MatrixMultiplier::setMatrixSize(int const &newSize)
{
	mMatrixSize = newSize;
}

void MatrixMultiplier::prepareMatrixes()
{
	clear();
	mA = new int[mMatrixSize * mMatrixSize];
	mB = new int[mMatrixSize * mMatrixSize];
	mC = new int[mMatrixSize * mMatrixSize];
	ArrayMaster::loadArrays(mA, mB, mMatrixSize);
	ArrayMaster::clearArray(mC, mMatrixSize * mMatrixSize);
}

void MatrixMultiplier::clear()
{
	if (mA != NULL)
	{
		delete[] mA;
		mA = NULL;
	}
	if (mB != NULL)
	{
		delete[] mB;
		mB = NULL;
	}
	if (mC != NULL)
	{
		delete[] mC;
		mC = NULL;
	}
}
