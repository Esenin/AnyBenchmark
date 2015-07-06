//! @author Ivan Senin (Esenin)
//! @brief Example of usage AnyBenchmark tool

#include "../include/benchmaker.h"

#include "../tests/matrixMultiplying/multiplicationTestLauncher.h"

int main()
{
    benchmark::Benchmaker benchmark;

    matrixBenchmark(benchmark);

    measurementTypeCompare(benchmark);

    return 0;
}
