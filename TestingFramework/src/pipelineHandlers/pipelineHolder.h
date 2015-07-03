#pragma once

#include <memory>

#include "benchmarkEvent.h"
#include "iEventHandler.h"

namespace Benchmark
{

class PipelineHolder
{
public:
    PipelineHolder();
    ~PipelineHolder();

    void appendHandler(UniqueEventHandler handler);

    void emitEvent(BenchmarkEvent const &event);

    void resetPipeline();

private:
    UniqueEventHandler headOfChain;
};


}

