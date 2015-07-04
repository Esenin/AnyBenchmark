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
    FileWriter();
    ~FileWriter();

protected:
    virtual void handleHook(BenchmarkEvent const &e);

private:
    FileOutput mOutputFormat;
    std::string mFilename;
    std::fstream mLogger;

    void printHumanReadable(RoundSeriesFinishedEvent const *e);

    void printInCSV(RoundSeriesFinishedEvent const *e);

    void openFile();

    void closeFile();
};

}
}