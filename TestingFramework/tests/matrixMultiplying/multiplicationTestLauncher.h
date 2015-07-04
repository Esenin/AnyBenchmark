#pragma once

#include "recursiveMultiplier.h"
#include "regularMultiplier.h"
#include "transposedMultiplier.h"

void matrixBenchmark(benchmark::Benchmaker &benchmark)
{
    benchmark.setRoundsCount(5);
    // Regular multiplying
    benchmark.setBenchmarkName("Naive multipying");
    benchmark.setLogginToFile(benchmark::FileOutput::csv);
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.setTestingParam(100, 400, 100);  // (100, 1000, 50) looks interesting
    benchmark.makeBenchmark();

    // recursive: onlt for 2^N matrix
    benchmark.setBenchmarkName("recursive multipying");
    benchmark.setLogginToFile(benchmark::FileOutput::none);
    benchmark.setRunnableObject(new RecursiveMultiplier);
    benchmark.setTestingParam({128, 256, 512});
    benchmark.makeBenchmark();

    // transposed
    benchmark.setBenchmarkName("transposed multipying");
    benchmark.setLogginToFile(benchmark::FileOutput::humanReadable);
    benchmark.setRunnableObject(new TransposedMultiplier);
    benchmark.setTestingParam(100, 400, 100);
    benchmark.makeBenchmark();
}
