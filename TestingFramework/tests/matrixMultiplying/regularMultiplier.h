#pragma once

#include "matrixMultiplier.h"

class RegularMultiplier : public MatrixMultiplier
{
public:
	RegularMultiplier();
	virtual void run() throw(Error);
protected:
	void multiply();
};


