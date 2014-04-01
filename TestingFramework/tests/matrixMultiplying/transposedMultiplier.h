#pragma once

#include "matrixMultiplier.h"

class TransposedMultiplier : public MatrixMultiplier
{
public:
	TransposedMultiplier();
	virtual void run();
protected:
	void multiply();
};

