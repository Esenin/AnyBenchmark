#pragma once

#include <chrono>

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
    FileOutput mOutputFormat;
};

}

