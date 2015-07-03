#pragma once

#include <memory>

#include "benchmarkEvent.h"
#include "iEventHandler.h"

namespace Benchmark
{

enum class FileOutput
{
    none = 0
    , humanReadable = 1
    , csv = 2
};

typedef std::unique_ptr<IEventHandler> UniqueEventHandler;

class PipelineHolder
{
public:
    PipelineHolder();
    ~PipelineHolder();

    void appendHandler(UniqueEventHandler handler);

    void emitEvent(BenchmarkEvent const &event);

    void resetPipeline();

private:
    UniqueResultHandler headOfChain;
};


}

