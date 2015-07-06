#pragma once

#include "recursiveMultiplier.h"
#include "regularMultiplier.h"
#include "transposedMultiplier.h"

void measurementTypeCompare(benchmark::Benchmaker &benchmark)
{
    benchmark.setRoundsCount(10);
    benchmark.setLogginToFile(benchmark::FileOutput::none);
    benchmark.setTestingParam(500);
    benchmark.setMeasureType(benchmark::MeasureType::realTime);

    benchmark.setBenchmarkName("Naive multipying, real time measurement");
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.makeBenchmark();
    benchmark.setBenchmarkName("Transposed multipying, real time");
    benchmark.setRunnableObject(new TransposedMultiplier);
    benchmark.makeBenchmark();

    benchmark.setMeasureType(benchmark::MeasureType::cpuTime);

    benchmark.setBenchmarkName("Naive multipying, CPU time measurement");
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.makeBenchmark();
    benchmark.setBenchmarkName("Transposed multipying, CPU time");
    benchmark.setRunnableObject(new TransposedMultiplier);
    benchmark.makeBenchmark();

    benchmark.setMeasureType(benchmark::MeasureType::hybrid);
    benchmark.setBenchmarkName("Naive multipying, Hybrid time measurement");
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.makeBenchmark();
    benchmark.setBenchmarkName("Transposed multipying, Hybrid time");
    benchmark.setRunnableObject(new TransposedMultiplier);
    benchmark.makeBenchmark();
}


void matrixBenchmark(benchmark::Benchmaker &benchmark)
{
    benchmark.setRoundsCount(5);
    benchmark.setMeasureType(benchmark::MeasureType::cpuTime);
    // Regular multiplying
    benchmark.setBenchmarkName("Naive multipying");
    benchmark.setLogginToFile(benchmark::FileOutput::csv);
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.setTestingParam(100, 400, 100);  // (100, 1000, 50) looks interesting
    benchmark.makeBenchmark();

    // recursive: only for 2^N matrix
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
