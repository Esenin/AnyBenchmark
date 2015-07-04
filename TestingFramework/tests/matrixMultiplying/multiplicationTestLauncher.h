#pragma once

#include "recursiveMultiplier.h"
#include "regularMultiplier.h"
#include "transposedMultiplier.h"

void matrixBenchmark(Benchmark::Benchmaker &benchmark)
{
    benchmark.setRoundsCount(5);
    // Regular multiplying
    benchmark.setBenchmarkName("Naive multipying");
    benchmark.setLogginToFile(Benchmark::FileOutput::csv);
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.makeBenchmark(100, 400, 100);  // (100, 1000, 50) looks interesting

    // recursive: onlt for 2^N matrix
    benchmark.setBenchmarkName("recursive multipying");
    benchmark.setLogginToFile(Benchmark::FileOutput::none);
    benchmark.setRunnableObject(new RecursiveMultiplier);
    benchmark.makeBenchmark(128, 0, 0);
    benchmark.makeBenchmark(256, 0, 0);
    benchmark.makeBenchmark(512, 0, 0);

    // transposed
    benchmark.setBenchmarkName("transposed multipying");
    benchmark.setLogginToFile(Benchmark::FileOutput::humanReadable);
    benchmark.setRunnableObject(new TransposedMultiplier);
    benchmark.makeBenchmark(100, 400, 100);
}
