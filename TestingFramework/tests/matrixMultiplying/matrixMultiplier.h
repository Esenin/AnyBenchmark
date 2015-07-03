#pragma once
#include "../../src/iTestObject.h"
#include "arrayMaster.h"

class MatrixMultiplier : public Benchmark::ITestObject
{
public:
    MatrixMultiplier();
    virtual ~MatrixMultiplier();

    void setParam(int const &param);
    virtual void prepare();
    virtual void run() = 0;
    virtual void clear();

protected:
    int mMatrixSize;
    int *mA;
    int *mB;
    int *mC;
};


