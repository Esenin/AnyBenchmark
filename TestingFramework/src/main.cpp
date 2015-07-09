//! @author Ivan Senin (Esenin)
//! @brief Example of usage AnyBenchmark tool

#include "../include/benchmaker.h"

#include "../tests/matrixMultiplying/multiplicationTestLauncher.h"

int main()
{
    benchmark::Benchmaker benchmark;

    DEBUG("Check debug macro 1");
    matrixBenchmark(benchmark);

    DEBUG2("Check debug macro 2");

//    measurementTypeCompare(benchmark);

    return 0;
}
