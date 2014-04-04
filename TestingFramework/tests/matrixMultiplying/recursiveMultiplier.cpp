#include "recursiveMultiplier.h"

RecursiveMultiplier::RecursiveMultiplier()
{
}

void RecursiveMultiplier::run() throw(Error)
{
	recMultiply(mC, mA, mB, mMatrixSize, mMatrixSize);
}

void RecursiveMultiplier::recMultiply(int *c, int *a, int *b, int n, int rowsize)
{
	if (n == 1)
		c[0] += a[0] * b[0];
	else {
		n = n / 2;

		int d11 = 0;
		int d12 = n;
		int d21 = n * rowsize + 0;
		int d22 = n * (rowsize + 1);
		recMultiply(c + d11, a + d11, b + d11, n, rowsize);
		recMultiply(c + d11, a + d12, b + d21, n, rowsize);
		recMultiply(c + d12, a + d11, b + d12, n, rowsize);
		recMultiply(c + d12, a + d12, b + d22, n, rowsize);
		recMultiply(c + d21, a + d21, b + d11, n, rowsize);
		recMultiply(c + d21, a + d22, b + d21, n, rowsize);
		recMultiply(c + d22, a + d21, b + d12, n, rowsize);
		recMultiply(c + d22, a + d22, b + d22, n, rowsize);
	}
}

