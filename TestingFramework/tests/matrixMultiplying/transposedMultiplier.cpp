#include "transposedMultiplier.h"

TransposedMultiplier::TransposedMultiplier()
{
}

void TransposedMultiplier::run() throw(Error)
{
	ArrayMaster::transpose(mB, mMatrixSize);
	multiply();
}

void TransposedMultiplier::multiply()
{
	for (int  i= 0; i < mMatrixSize; i++)
		for (int j = 0; j < mMatrixSize; j++)
			for (int k = 0; k < mMatrixSize; k++)
			{
				mC[i * mMatrixSize + j] += mA[i * mMatrixSize + k] * mB[j * mMatrixSize + k];
			}
}
