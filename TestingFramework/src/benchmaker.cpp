#include "benchmaker.h"

using std::cout;
using std::endl;
using namespace Benchmark;

Benchmaker::Benchmaker()
    : mLogToFile(false)
    , mRoundsCount(10)
    , mTestObj(nullptr)
{
}

Benchmaker::~Benchmaker()
{
    freeTestObject();
}

void Benchmaker::startLogging()
{
    if (mLogToFile)
    {
        createFile();
        mLogger << "N (main param), Average time[ms]:\n";
    }
}

void Benchmaker::makeBenchmark(int const &startValue, int const &maxValue, int const &stepSize)
{
    if (!mTestObj)
    {
        cout << "Set test object first!\n";
        return;
    }
    startLogging();

    cout << "Test\t" << mBenchmarkName << "\thas been started, from "
            << startValue << " to " << ((maxValue > startValue)? maxValue : startValue) << endl;

    auto startBenchmarkTime = std::chrono::high_resolution_clock::now();
    int mainParam = startValue;

    do
    {
        auto startRoundTime = std::chrono::high_resolution_clock::now();
        double average = 0;
        for (int i = 0; i < mRoundsCount; i++)
        {
            try
            {
                average += makeRound(mainParam);
            }
            catch (std::exception &e)
            {
                cout << "Test-subject\'s behavior is wrong. \nBreak\n"
                     << "cause: " << e.what() << endl;
                break;
            }
        }
        average /= mRoundsCount;

        if (mLogToFile)
        {
            putToFile(mainParam, average);
        }

        auto roundInSecs = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::high_resolution_clock::now() - startRoundTime).count();

        cout << "N = " << mainParam
                << "\tAverage time is " << average << " [ms], \tTime for round: " << roundInSecs<< " [s]" << endl;
        mainParam += ((stepSize > 0)? stepSize : 1);
    }
    while (mainParam <= maxValue);

    auto stopBenchmarkTime = std::chrono::high_resolution_clock::now();
    auto totalTimeSecs =
            std::chrono::duration_cast<std::chrono::seconds>(stopBenchmarkTime - startBenchmarkTime).count();


    cout << "Benchmark already done! Total time: " << totalTimeSecs
            << " seconds (" << (double)totalTimeSecs / 60 << " minutes)\n\n";

    closeFile();
}

void Benchmaker::setRunnableObject(TestObject *object)
{
    freeTestObject();
    mTestObj = object;
    mBenchmarkName = "";
}

void Benchmaker::setLogginToFile(bool const &mustLog)
{
    mLogToFile = mustLog;
}

void Benchmaker::setBenchmarkName(std::string const &name)
{
    mBenchmarkName = name + "_";
}

void Benchmaker::setRoundsCount(unsigned int const &count)
{
    if (!count)
        throw std::invalid_argument("Set positive number of rounds");
    mRoundsCount = count;
}

unsigned int Benchmaker::makeRound(int const &paramN)
{
    mTestObj->setParam(paramN);
    mTestObj->prepare();

    std::this_thread::sleep_for(std::chrono::milliseconds( 10 )); // invalidate pipeline and flush cache
    unsigned int result = makeTest();
    std::this_thread::sleep_for(std::chrono::milliseconds( 10 ));

    mTestObj->clear();

    return result;
}

unsigned int Benchmaker::makeTest()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    mTestObj->run();

    auto stopTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
}

void Benchmaker::freeTestObject()
{
    delete mTestObj;
    mTestObj = nullptr;
}

void Benchmaker::createFile()
{
    mResultsFilename = ((mBenchmarkName.size())? mBenchmarkName : "unnamed_") + getTimeString()
            + "(v" +std::to_string(rand() % 1000) + ").txt";

    mLogger.open(mResultsFilename, std::ios_base::out | std::ios_base::trunc);

    if (!mLogger.is_open())
    {
        mLogToFile = false;
        throw std::runtime_error("Cannot open file: " + mResultsFilename);
    }
}

std::string Benchmaker::getTimeString()
{
    size_t const bufLen = 20;
    std::string timeStr(bufLen, 0);
    auto curTimePoint = std::chrono::system_clock::now();
    auto stdTime = std::chrono::system_clock::to_time_t(curTimePoint);
    auto charUsed = std::strftime(&timeStr[0], bufLen, "%H-%M-%S", std::localtime(&stdTime));
    if (!charUsed)
        throw std::runtime_error("Cannot get current time");
    else
        timeStr = timeStr.substr(0, charUsed);

    return timeStr;
}

void Benchmaker::putToFile(int const param, double const &average)
{
    mLogger << std::to_string(param) << "\t" << std::to_string(average) << endl;
}

void Benchmaker::closeFile()
{
    if (!mLogger.is_open())
        return;

    cout << "\n Tests result stored at: " << mResultsFilename << endl << endl;
    mLogger.close();
}


