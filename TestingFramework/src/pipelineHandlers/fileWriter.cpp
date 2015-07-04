#include "fileWriter.h"

using namespace benchmark::impl;
using std::endl;

FileWriter::FileWriter()
    : mOutputFormat(FileOutput::none)
{
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
        {
            auto config = dynamic_cast<const ReconfigurationEvent *>(&e);
            mOutputFormat = config->fileOutputFormat;
            mFilename = config->logFileName;
            break;
        }
        case BenchmarkEvent::EventType::benchmarkStarted:
            if (mOutputFormat != FileOutput::none)
                openFile();
            break;

        case BenchmarkEvent::EventType::roundSeriesFinished:
        {
            auto results = dynamic_cast<const RoundSeriesFinishedEvent *>(&e);
            switch (mOutputFormat)
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
        }
        case BenchmarkEvent::EventType::benchmarkCrashed:
        case BenchmarkEvent::EventType::benchmarkFinished:
            if (mOutputFormat != FileOutput::none)
                closeFile();
            break;
        default:
            break;
    }


}

void FileWriter::printHumanReadable(RoundSeriesFinishedEvent const *e)
{
    mLogger << std::to_string(e->param) << "\t\t" << std::to_string(e->milliseconds) << endl;
}

void FileWriter::printInCSV(RoundSeriesFinishedEvent const *e)
{
    mLogger << std::to_string(e->param) << "," << std::to_string(e->milliseconds) << endl;
}

void FileWriter::openFile()
{
    mLogger.open(mFilename, std::ios_base::out | std::ios_base::trunc);

    if (!mLogger.is_open())
    {
        throw std::runtime_error("Cannot open file: " + mFilename);
    }

    if (mOutputFormat == FileOutput ::humanReadable)
    {
        mLogger << "N (main param), Average time[ms]:\n";
    }
}

void FileWriter::closeFile()
{
    if (!mLogger.is_open())
        return;
    mLogger.close();
}


