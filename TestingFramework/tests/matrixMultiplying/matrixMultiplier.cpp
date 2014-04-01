#include "matrixMultiplier.h"

MatrixMultiplier::MatrixMultiplier()
	: mMatrixSize(10)
	, mA(nullptr)
	, mB(nullptr)
	, mC(nullptr)
{
	ArrayMaster::randomize();
}

MatrixMultiplier::~MatrixMultiplier()
{
	clear();
}

void MatrixMultiplier::setParam(int const &param)
{
	mMatrixSize = param;
}

void MatrixMultiplier::prepare()
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
	if (mA != nullptr)
	{
		delete[] mA;
		mA = nullptr;
	}
	if (mB != nullptr)
	{
		delete[] mB;
		mB = nullptr;
	}
	if (mC != nullptr)
	{
		delete[] mC;
		mC = nullptr;
	}
}
