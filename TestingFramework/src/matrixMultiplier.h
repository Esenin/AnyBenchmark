#pragma once
#include "arrayMaster.h"

class MatrixMultiplier
{
public:
	MatrixMultiplier();
	virtual ~MatrixMultiplier();

	void setMatrixSize(int const &newSize);
	virtual void prepareMatrixes();
	virtual void run() = 0;
	virtual void clear();

protected:
	int mMatrixSize;
	int *mA;
	int *mB;
	int *mC;
};


