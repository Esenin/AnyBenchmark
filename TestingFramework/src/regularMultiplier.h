#pragma once

#include "matrixMultiplier.h"

class RegularMultiplier : public MatrixMultiplier
{
public:
	RegularMultiplier();
	virtual void run();
protected:
	void multiply();
};


