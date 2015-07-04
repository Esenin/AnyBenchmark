#include "pipelineHolder.h"

using namespace benchmark::impl;

PipelineHolder::~PipelineHolder()
{
    resetPipeline();
}

void PipelineHolder::appendHandler(UniqueEventHandler &&handler)
{
    if (!mHeadOfChain)
        mHeadOfChain = std::move(handler);
    else
        mHeadOfChain->setNextHandler(std::move(handler));
}

void PipelineHolder::emitEvent(BenchmarkEvent const &event)
{
    mHeadOfChain->handle(event);
}

void PipelineHolder::resetPipeline()
{
    mHeadOfChain.reset(nullptr);
}
