#pragma once


namespace Benchmark
{

struct BenchmarkEvent
{
    virtual ~BenchmarkEvent() {}
    enum class EventType
    {
        reconfiguration
        , benchmarkStarted
        , roundSeriesStarted
        , roundSeriesFinished
        , benchmarkFinished
        , benchmarkCrashed
    } type;
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
        : type(EventType::reconfiguration)
        , benchmarkName(name)
        , logFileName(filename)
        , roundCount(roundCount)
        , hasBeenTestObjectChanched(hasBeenTestObjectChanched)
        , fileOutputFormat(fileOutputFormat) {}
};

struct BenchmarkStartedEvent : public BenchmarkEvent
{
    BenchmarkStartedEvent() : type(EventType::benchmarkStarted) {}
};

struct RoundSeriesStartedEvent : public BenchmarkEvent
{
    int const param;
    RoundSeriesStartedEvent(int param) : type(EventType::roundSeriesStarted), param(param) {}
};

struct RoundSeriesFinishedEvent : public BenchmarkEvent
{
    int const param;
    double const milliseconds;
    RoundSeriesFinishedEvent(int const &param, double const &ms) :
        type(EventType::roundSeriesFinished)
      , param(param)
      , milliseconds(ms) {}
};


struct BenchmarkFinishedEvent : public BenchmarkEvent
{
    BenchmarkFinishedEvent() : type(EventType::benchmarkFinished) {}
};

struct BenchmarkCrashedEvent : public BenchmarkEvent
{
    BenchmarkCrashedEvent() : type(EventType::benchmarkCrashed) {}
};



}
