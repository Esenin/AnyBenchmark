//! @author Ivan Senin (Esenin)
//! @brief Example of usage AnyBenchmark tool

#include "../include/benchmaker.h"

#include "../tests/matrixMultiplying/multiplicationTestLauncher.h"

int main()
{
    benchmark::Benchmaker benchmark;

    DEBUG("Check debug macro 1");

    benchmarkGroupTest(benchmark);

    DEBUG2("Check debug macro 2");
    matrixBenchmark(benchmark);

    WARNING("Warning test");

//    measurementTypeCompare(benchmark);

    return 0;
}
