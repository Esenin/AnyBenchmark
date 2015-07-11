#include "fileWriter.h"

using namespace benchmark;
using namespace benchmark::impl;
using std::endl;

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
            handleReconfig(config);
            break;
        }
        case BenchmarkEvent::EventType::benchmarkStarted:
        {
            handleBenchmarkStart();
            break;
        }
        case BenchmarkEvent::EventType::benchmarkCrashed:
            closeFile();
            setNewState(FWState::idle);
            break;
        case BenchmarkEvent::EventType::benchmarkFinished:
        {
            auto stopEvent = dynamic_cast<const BenchmarkFinishedEvent*>(&e);
            handleBenchmarkStop(stopEvent);
            break;
        }
        default:
            break;
    }
}

void FileWriter::printHumanReadable(ResultsQueue const* results)
{
    for (auto const &tup : *results)
        mLogger << std::to_string(std::get<0>(tup)) << "\t\t" << std::to_string(std::get<1>(tup)) << endl;
}

void FileWriter::printCSVHeader(ResultsQueue const *results)
{
    mLogger << "Benchmark";
    for (auto const &tup : *results)
        mLogger << "," << std::get<0>(tup);
    mLogger << endl;
}

void FileWriter::printInCSV(ResultsQueue const* results)
{
    if (mState == FWState::writeFirstGroupBenchmark || mState == FWState::writeBenchmark)
    {
        printCSVHeader(results);
        if (mState == FWState::writeFirstGroupBenchmark)
            setNewState(FWState::writeNextGroupBenchmark);
    }

    mLogger << mBenchmarkName;
    for (auto const &tup : *results)
        mLogger << "," << std::get<1>(tup);
    mLogger << endl;
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
        mLogger << "N (main param)\tAverage time[ms]:\n";
    }
}

void FileWriter::closeFile()
{
    if (!mLogger.is_open())
        return;
    mLogger.close();
}


void FileWriter::handleReconfig(ReconfigurationEvent const* e)
{
    mOutputFormat = e->fileOutputFormat;
    mBenchmarkName = e->benchmarkName;
    mFilename = e->filename;
    if (e->isGroupedBenchmarkSet != mIsGroupedBenchmarkSet)
    {
        handleGroupStateChange(e->isGroupedBenchmarkSet);
    }


}

void FileWriter::handleBenchmarkStart()
{
    if (mOutputFormat != FileOutput::none
        && (!mIsGroupedBenchmarkSet || (mIsGroupedBenchmarkSet && !mLogger.is_open())))
    {
        openFile();
        setNewState((mIsGroupedBenchmarkSet)? FWState::writeFirstGroupBenchmark : FWState::writeBenchmark);
    }
}

void FileWriter::handleBenchmarkStop(BenchmarkFinishedEvent const* e)
{
    if (mState == FWState::idle)
        return;

    if (mOutputFormat == FileOutput::humanReadable)
        printHumanReadable(e->pResultsQueue);
    else if (mOutputFormat == FileOutput::csv)
        printInCSV(e->pResultsQueue);

    if (mState == FWState::writeBenchmark)
    {
        closeFile();
        setNewState(FWState::idle);
    }
}

void FileWriter::handleGroupStateChange(bool isGroupedNext)
{
    if (mIsGroupedBenchmarkSet && !isGroupedNext)
    {
        if (mState == FWState::writeNextGroupBenchmark)
        {
            closeFile();
            setNewState(FWState::idle);
        }
    }
    else
        closeFile();


    mIsGroupedBenchmarkSet = isGroupedNext;
}

bool FileWriter::setNewState(FileWriter::FWState state)
{
    if (mOutputFormat == FileOutput::none)
        mState = FWState::idle;
    else
        mState = state;
    return mState == state;
}


