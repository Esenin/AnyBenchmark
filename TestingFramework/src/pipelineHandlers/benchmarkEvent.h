#pragma once

#include "../../include/constants.h"

namespace benchmark
{
namespace impl
{
struct BenchmarkEvent
{
    enum class EventType
    {
        reconfiguration
        , benchmarkStarted
        , roundSeriesStarted
        , roundSeriesFinished
        , benchmarkFinished
        , benchmarkCrashed
    };

    BenchmarkEvent(EventType eventType) : type(eventType)
    { }

    virtual ~BenchmarkEvent()
    { }

    EventType type;
};

struct ReconfigurationEvent : public BenchmarkEvent
{
    std::string benchmarkName;
    std::string filename;
    int roundCount;
    bool hasBeenTestObjectChanched;
    FileOutput fileOutputFormat;
    bool isGroupedBenchmarkSet;

    ReconfigurationEvent(std::string const &name, std::string const &filename, int roundCount, bool hasBeenTestObjectChanched
                         , FileOutput fileOutputFormat, bool isGroupedSet)
            : BenchmarkEvent(EventType::reconfiguration)
            , benchmarkName(name)
            , filename(filename)
            , roundCount(roundCount)
            , hasBeenTestObjectChanched(hasBeenTestObjectChanched)
            , fileOutputFormat(fileOutputFormat)
            , isGroupedBenchmarkSet(isGroupedSet)
    { }
};

struct BenchmarkStartedEvent : public BenchmarkEvent
{
    int benchmarkSetGroupId = -1; // -1 means there is no group now
    BenchmarkStartedEvent(int benchmarkSetGroupId) : BenchmarkEvent(EventType::benchmarkStarted)
    { }
};

struct RoundSeriesStartedEvent : public BenchmarkEvent
{
    int const param;

    RoundSeriesStartedEvent(int param) : BenchmarkEvent(EventType::roundSeriesStarted), param(param)
    { }
};

struct RoundSeriesFinishedEvent : public BenchmarkEvent
{
    int const param;
    long double const milliseconds;

    RoundSeriesFinishedEvent(int const &param, long double const &ms)
        : BenchmarkEvent(EventType::roundSeriesFinished), param(param), milliseconds(ms)
    { }
};


struct BenchmarkFinishedEvent : public BenchmarkEvent
{
    ResultsQueue const * pResultsQueue;

    BenchmarkFinishedEvent(ResultsQueue const* resultsQueue)
            : BenchmarkEvent(EventType::benchmarkFinished), pResultsQueue(resultsQueue)
    { }
};

struct BenchmarkCrashedEvent : public BenchmarkEvent
{
    std::string cause;

    BenchmarkCrashedEvent(std::string cause)
        : BenchmarkEvent(EventType::benchmarkCrashed), cause(cause)
    { }
};


}
}
