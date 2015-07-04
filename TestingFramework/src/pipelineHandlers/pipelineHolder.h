#pragma once

#include "benchmarkEvent.h"
#include "iEventHandler.h"

namespace benchmark
{
namespace impl
{

class PipelineHolder
{
public:
    PipelineHolder() = default;
    ~PipelineHolder();

    void appendHandler(UniqueEventHandler &&handler);

    void emitEvent(BenchmarkEvent const &event);

    void resetPipeline();

private:
    UniqueEventHandler mHeadOfChain;
};

}
}

