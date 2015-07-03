#pragma once

#include <fstream>

#include "iEventHandler.h"
#include "pipelineHolder.h"

namespace Benchmark
{

class FileWriter : public IEventHandler
{
public:

    FileWriter();
    ~FileWriter();

protected:
    virtual void handleHook(BenchmarkEvent const &e);

private:
    FileOutput mOutputFormat;
    std::string mBenchmarkName;
    std::fstream mLogger;

    void printHumanReadable(RoundSeriesFinishedEvent const *e);
    void printInCSV(RoundSeriesFinishedEvent const *e);
    void openFile(std::string const &filename);
    void closeFile();
};

}
