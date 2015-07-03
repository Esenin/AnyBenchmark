#include "consoleWriter.h"

using namespace Benchmark;

void ConsoleWriter::handleHook(BenchmarkEvent const &e)
{
    /*cout << "Test\t" << mBenchmarkName << "\thas been started, from "
            << startValue << " to " << ((maxValue > startValue)? maxValue : startValue) << endl;*/

    /*cout << "N = " << mainParam
                << "\tAverage time is " << average << " [ms], \tTime for round: " << roundInSecs<< " [s]" << endl;*/

    /*cout << "Benchmark already done! Total time: " << totalTimeSecs
            << " seconds (" << (double)totalTimeSecs / 60 << " minutes)\n\n";*/

    /*cout << "\n Tests result stored at: " << mResultsFilename << endl << endl;*/


    switch (e.type)
    {
    case BenchmarkEvent::EventType::reconfiguration:

        break;
    case BenchmarkEvent::EventType::benchmarkStarted:
        auto startBenchmarkTime = std::chrono::high_resolution_clock::now();


        break;
    case BenchmarkEvent::EventType::roundSeriesStarted:
        auto startRoundTime = std::chrono::high_resolution_clock::now();

        break;
    case BenchmarkEvent::EventType::roundSeriesFinished:
        auto roundInSecs = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::high_resolution_clock::now() - startRoundTime).count();

        break;
    case BenchmarkEvent::EventType::benchmarkFinished:
        auto stopBenchmarkTime = std::chrono::high_resolution_clock::now();
        auto totalTimeSecs =
                std::chrono::duration_cast<std::chrono::seconds>(stopBenchmarkTime - startBenchmarkTime).count();
        break;
    case BenchmarkEvent::EventType::benchmarkCrashed:

        break;
    default:
        break;
    }
}
