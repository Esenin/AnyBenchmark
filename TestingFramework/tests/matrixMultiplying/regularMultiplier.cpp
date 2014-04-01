#include "regularMultiplier.h"

RegularMultiplier::RegularMultiplier()
{
}

void RegularMultiplier::run()
{
	multiply();
}

void RegularMultiplier::multiply()
{
	for (int  i = 0; i < mMatrixSize; i++)
		for (int j = 0; j < mMatrixSize; j++)
			for (int k = 0; k < mMatrixSize; k++)
			{
				mC[i * mMatrixSize + j] += mA[i * mMatrixSize + k] * mB[k * mMatrixSize + j];
			}
}
