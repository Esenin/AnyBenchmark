//! @author Ivan Senin (Esenin)
//! @brief Example of usage AnyBenchmark tool

#include "../include/benchmaker.h"

#include "../tests/matrixMultiplying/multiplicationTestLauncher.h"

int main()
{
    benchmark::Benchmaker benchmark;

    //uncomment this to save data to file
    benchmark.setLogginToFile(benchmark::FileOutput::none);

    matrixBenchmark(benchmark);

    return 0;
}
