#pragma once
#include "../../src/testObject.h"
#include "arrayMaster.h"

class MatrixMultiplier : public TestObject
{
public:
	MatrixMultiplier();
	virtual ~MatrixMultiplier();

	void setParam(int const &param);
	virtual void prepare();
	virtual void run() throw(Error) = 0;
	virtual void clear();

protected:
	int mMatrixSize;
	int *mA;
	int *mB;
	int *mC;
};


