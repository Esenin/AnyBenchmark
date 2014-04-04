#pragma once

#include "matrixMultiplier.h"

// For recursive multiplier only matrixes 2^N size available !
class RecursiveMultiplier : public MatrixMultiplier
{
public:
	RecursiveMultiplier();
	virtual void run() throw (Error);
protected:
	void recMultiply(int *c, int *a, int *b, int n, int rowsize);
};

