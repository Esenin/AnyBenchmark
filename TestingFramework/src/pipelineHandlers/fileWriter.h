#pragma once

#include <fstream>

#include "iEventHandler.h"

namespace benchmark
{
namespace impl
{

class FileWriter : public IEventHandler
{
public:
    FileWriter() = default;
    ~FileWriter();

protected:
    virtual void handleHook(BenchmarkEvent const &e);

private:
    FileOutput mOutputFormat = FileOutput::none;
    std::string mFilename;
    std::string mBenchmarkName;
    std::fstream mLogger;
    bool mIsGroupedBenchmarkSet = false;

    enum class FWState
    {
        idle
        , writeBenchmark
        , writeFirstGroupBenchmark
        , writeNextGroupBenchmark
    };
    FWState mState = FWState::idle;
    bool setNewState(FWState state);

    void handleReconfig(ReconfigurationEvent const *e);
    void handleBenchmarkStart();
    void handleBenchmarkStop(BenchmarkFinishedEvent const *e);
    void handleGroupStateChange(bool isGroupedNext);

    void printHumanReadable(ResultsQueue const* results);
    void printCSVHeader(ResultsQueue const* results);
    void printInCSV(ResultsQueue const* results);

    void openFile();
    void closeFile();
};

}
}