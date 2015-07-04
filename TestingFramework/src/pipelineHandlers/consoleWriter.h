#pragma once

#include <iostream>
#include <ostream>
#include <chrono>
#include <math.h>

#include "iEventHandler.h"
#include "pipelineHolder.h"

namespace Benchmark
{

class ConsoleWriter : public IEventHandler
{
public:
protected:
    virtual void handleHook(BenchmarkEvent const &e);
private:
    std::string mBenchmarkName;
    std::string mLogFilename;
    FileOutput mOutputFormat;
    int mRoundsCount;

    typedef decltype(std::chrono::high_resolution_clock::now()) TimePoint;

    TimePoint mBenchStartedTime, mRoundStartedTime;
};

}

