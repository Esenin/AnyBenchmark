#include "consoleWriter.h"
#include <math.h>

using namespace benchmark::impl;
using std::cout;
using std::endl;

void ConsoleWriter::handleHook(BenchmarkEvent const &e)
{
    switch (e.type)
    {
        case BenchmarkEvent::EventType::reconfiguration:
        {
            auto config = dynamic_cast<const ReconfigurationEvent *>(&e);
            mBenchmarkName = config->benchmarkName;
            mLogFilename = config->filename;
            mOutputFormat = config->fileOutputFormat;
            mRoundsCount = config->roundCount;
            break;
        }
        case BenchmarkEvent::EventType::benchmarkStarted:
        {
            cout << "Test\t" << mBenchmarkName << "\thas been started"
                 << "\t(Using " << mRoundsCount << " repeats to get average time)" << endl;
            mBenchStartedTime = std::chrono::high_resolution_clock::now();
            break;
        }
        case BenchmarkEvent::EventType::roundSeriesStarted:
        {
            mRoundStartedTime = std::chrono::high_resolution_clock::now();
            break;
        }
        case BenchmarkEvent::EventType::roundSeriesFinished:
        {
            auto result = dynamic_cast<const RoundSeriesFinishedEvent *>(&e);

            auto roundInSecs = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::high_resolution_clock::now() - mRoundStartedTime).count();

            cout << "N = " << result->param << "\tAverage time is " << result->milliseconds
                                                                       << " [ms], \t\tTime for round: " << roundInSecs << " [s]" << endl;
            break;
        }
        case BenchmarkEvent::EventType::benchmarkFinished:
        {
            auto const stopBenchmarkTime = std::chrono::high_resolution_clock::now();
            auto const totalTimeSecs =
                    std::chrono::duration_cast<std::chrono::seconds>(stopBenchmarkTime - mBenchStartedTime).count();
            auto const minutes = (double) totalTimeSecs / 60;
            auto const hours = minutes / 60;
            cout << "benchmark already done! Total time: " << totalTimeSecs << " seconds ("
                 << minutes << " minutes)\n";
            if (hours > 1.5)
            {
                cout << "It's about " << round(hours) << " hours!\n";
            }
            if (mOutputFormat != FileOutput::none)
                cout << "benchmark results are stored @ " << mLogFilename << "\n";
            cout << endl;
            break;
        }
        case BenchmarkEvent::EventType::benchmarkCrashed:
            auto crashEvent = dynamic_cast<const BenchmarkCrashedEvent *>(&e);
            cout << "benchmark has been crashed. What(): " << crashEvent->cause << endl;
            break;
    }
}
