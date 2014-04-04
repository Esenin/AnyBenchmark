#pragma once

#include "matrixMultiplier.h"

class TransposedMultiplier : public MatrixMultiplier
{
public:
	TransposedMultiplier();
	virtual void run() throw (Error);
protected:
	void multiply();
};

