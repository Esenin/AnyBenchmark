#pragma once

#include <memory>

#include "benchmarkEvent.h"

namespace Benchmark
{

class IEventHandler;
typedef std::unique_ptr<IEventHandler> UniqueEventHandler;

class IEventHandler
{
public:
    virtual ~IEventHandler() {}

    void setNextHandler(UniqueEventHandler &&handler)
    {
        if (mNextHandler)
            mNextHandler->setNextHandler(std::forward<UniqueEventHandler>(handler));
        else
            mNextHandler = std::move(handler);
    }

    void handle(BenchmarkEvent const &results)
    {
        handleHook(results);
        if (mNextHandler)
            mNextHandler->handle(results);
    }

protected:
    virtual void handleHook(BenchmarkEvent const &results) = 0;

private:
    UniqueEventHandler mNextHandler;
};

} // Benchmark

