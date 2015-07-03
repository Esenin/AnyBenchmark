#include "fileWriter.h"

using namespace Benchmark;

FileWriter::FileWriter()
    : mOutputFormat(FileOutput::none)
{
    openFile();

    if (output == Format::humanReadable)
    {
        mLogger << "N (main param), Average time[ms]:\n";
    }
}

FileWriter::~FileWriter()
{
    closeFile();
}

void FileWriter::handleHook(BenchmarkEvent const &e)
{
    switch (e.type)
    {
    case BenchmarkEvent::EventType::reconfiguration:
        auto config = dynamic_cast<ReconfigurationEvent *>(&e);
        mOutputFormat = config->fileOutputFormat;
        mBenchmarkName = config->benchmarkName;
        break;
    case BenchmarkEvent::EventType::roundSeriesFinished:
        auto results = dynamic_cast<RoundSeriesFinishedEvent *>(&e);
        switch(mOutputFormat)
        {
        case FileOutput::csv:
            printInCSV(results);
            break;
        case FileOutput::humanReadable:
            printHumanReadable(results);
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }


}

void FileWriter::printHumanReadable(RoundSeriesFinishedEvent const *e)
{
    mLogger << std::to_string(e.param) << "\t" << std::to_string(e.milliseconds) << endl;
}

void FileWriter::printInCSV(RoundSeriesFinishedEvent const *e)
{
    mLogger << std::to_string(e.param) << "," << std::to_string(e.milliseconds) << endl;
}

void FileWriter::openFile(const std::string &filename)
{
    mLogger.open(filename, std::ios_base::out | std::ios_base::trunc);

    if (!mLogger.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

void FileWriter::closeFile()
{
    if (!mLogger.is_open())
        return;
    mLogger.close();
}


