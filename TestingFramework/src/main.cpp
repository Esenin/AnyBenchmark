//! @author Ivan Senin (Esenin)
//! @brief Example of usage AnyBenchmark tool

#include "benchmaker.h"

#include "../tests/matrixMultiplying/multiplicationTestLauncher.h"

int main()
{
    Benchmark::Benchmaker benchmark;

    //uncomment this to save data to file
    benchmark.setLogginToFile(Benchmark::FileOutput::none);

    matrixBenchmark(benchmark);

    return 0;
}
