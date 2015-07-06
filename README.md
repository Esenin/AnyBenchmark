AnyBenchmark
=======================
Lang: C++ (STL only)

A framework for testing performance of algos and data-structures. It suits for benchmarks where algorithm can consume about >= 10 ms up to several seconds. 
You can choose which timer-type is more appropriate for your case. Select from "Real-time", "CPU-cycles-clock" (translates into milliseconds) or "hybrid-time" (which is close to cpu-based, but also takes into account real time)


Info: for microbenchmarking (with nanoseconds precision) please consider to use [Google Benchmark](https://github.com/google/benchmark)


Usage example
-------------
Include in your project headers:
```c++
#include "../AnyBenchmark/include/benchmaker.h"
#include "../AnyBenchmark/include/iTestObject.h"
```

Then implement ITestObject interface with your testing subject
```c++
class ITestObject
{
public:
    virtual ~ITestObject() {}

    //! set main param of test
    virtual void setParam(int const &param) = 0;

    //! called each time before "run", won't be considered by timer
    virtual void prepare() = 0;

    //! actual test content must be here
    virtual void run() = 0;

    //! clears after run-test
    virtual void clear() = 0;
};
```

After that you can create benchmark
```c++
int main()
{
    benchmark::Benchmaker benchmark;

    benchmark.setRoundsCount(10);
    benchmark.setMeasureType(benchmark::MeasureType::cpuTime);
    // Regular multiplying
    benchmark.setBenchmarkName("Naive multipying");
    benchmark.setLogginToFile(benchmark::FileOutput::csv);
    benchmark.setRunnableObject(new RegularMultiplier);
    benchmark.setTestingParam({100, 200, 500});
    benchmark.makeBenchmark();

    return 0;
}
```

Enjoy results!



Output example:
```
Test    Naive multipying_   has been started    (Using 10 repeats to get average time)
N = 100 Average time is 4.2 [ms],       Time for round: 0 [s]
N = 200 Average time is 30.6 [ms],      Time for round: 0 [s]
N = 500 Average time is 378.8 [ms],         Time for round: 4 [s]
benchmark already done! Total time: 4 seconds (0.0666667 minutes)
benchmark results are stored @ Naive multipying_17-49-42(v346).txt
```