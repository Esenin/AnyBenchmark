#pragma once

#include <chrono>

#include "iEventHandler.h"

namespace benchmark
{
namespace impl
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
}
