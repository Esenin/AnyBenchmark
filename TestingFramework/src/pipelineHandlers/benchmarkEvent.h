#pragma once

#include <string>

namespace Benchmark
{

enum class FileOutput
{
    none = 0
    , humanReadable = 1
    , csv = 2
};

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

    BenchmarkEvent(EventType eventType) : type(eventType) {}
    virtual ~BenchmarkEvent() {}

    EventType type;
};

struct ReconfigurationEvent : public BenchmarkEvent
{
    std::string const benchmarkName;
    std::string const logFileName;
    int const roundCount;
    bool const hasBeenTestObjectChanched;
    FileOutput const fileOutputFormat;

    ReconfigurationEvent(std::string const &name, std::string const &filename, int roundCount
                         , bool hasBeenTestObjectChanched, FileOutput fileOutputFormat)
            : BenchmarkEvent(EventType::reconfiguration)
            , benchmarkName(name)
            , logFileName(filename)
            , roundCount(roundCount)
            , hasBeenTestObjectChanched(hasBeenTestObjectChanched)
            , fileOutputFormat(fileOutputFormat)
    {}
};

struct BenchmarkStartedEvent : public BenchmarkEvent
{
    BenchmarkStartedEvent() : BenchmarkEvent(EventType::benchmarkStarted) {}
};

struct RoundSeriesStartedEvent : public BenchmarkEvent
{
    int const param;
    RoundSeriesStartedEvent(int param) : BenchmarkEvent(EventType::roundSeriesStarted), param(param) {}
};

struct RoundSeriesFinishedEvent : public BenchmarkEvent
{
    int const param;
    long double const milliseconds;

    RoundSeriesFinishedEvent(int const &param, long double const &ms) :
            BenchmarkEvent(EventType::roundSeriesFinished)
            , param(param)
            , milliseconds(ms) {}
};


struct BenchmarkFinishedEvent : public BenchmarkEvent
{
    BenchmarkFinishedEvent() : BenchmarkEvent(EventType::benchmarkFinished) {}
};

struct BenchmarkCrashedEvent : public BenchmarkEvent
{
    BenchmarkCrashedEvent() : BenchmarkEvent(EventType::benchmarkCrashed) {}
};



}
