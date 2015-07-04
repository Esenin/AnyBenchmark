#include "../include/benchmaker.h"
#include <iostream>
#include <thread>

#include "../src/pipelineHandlers/consoleWriter.h"
#include "../src/pipelineHandlers/fileWriter.h"

using std::cout;
using std::endl;
using namespace benchmark;
using namespace benchmark::impl;

bool const hasNext = true;

Benchmaker::Benchmaker()
    : mFileFormat(FileOutput::none)
    , mRoundsCount(10)
    , mTestObj(nullptr)
    , mParamGenerator([]() { return std::make_pair(false, 0); })
{
    mPipeline.appendHandler(UniqueEventHandler(new ConsoleWriter()));
    mPipeline.appendHandler(UniqueEventHandler(new FileWriter()));
}

Benchmaker::~Benchmaker()
{
    freeTestObject();
    mPipeline.resetPipeline();
}

void Benchmaker::makeBenchmark()
{
    configureBenchmark();
    mPipeline.emitEvent(BenchmarkStartedEvent());

    std::pair<bool, int> nextArg;
    while ((nextArg = mParamGenerator()).first == hasNext)
    {
        int mainParam = nextArg.second;
        mPipeline.emitEvent(RoundSeriesStartedEvent(mainParam));
        long double average = 0;
        for (int i = 0; i < mRoundsCount; i++)
        {
            try
            {
                average += makeRound(mainParam);
            }
            catch (std::exception &e)
            {
                mPipeline.emitEvent(BenchmarkCrashedEvent(e.what()));
                throw e;
            }
        }
        average /= mRoundsCount;
        mPipeline.emitEvent(RoundSeriesFinishedEvent(mainParam, average));

    }


    mPipeline.emitEvent(BenchmarkFinishedEvent());


}

void Benchmaker::setRunnableObject(ITestObject *object)
{
    freeTestObject();
    mTestObj = object;
}

void Benchmaker::setLogginToFile(FileOutput const format)
{
    mFileFormat = format;
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

long Benchmaker::makeRound(int const &paramN)
{
    mTestObj->setParam(paramN);
    mTestObj->prepare();

    std::this_thread::sleep_for(std::chrono::milliseconds( 10 )); // invalidate CPU's pipeline and flush cache
    long result = makeTest();
    std::this_thread::sleep_for(std::chrono::milliseconds( 10 ));

    mTestObj->clear();

    return result;
}

long Benchmaker::makeTest()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    mTestObj->run();

    auto stopTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count();
}

void Benchmaker::configureBenchmark()
{
    static ITestObject *prevObjectPtr = nullptr;
    if (!mTestObj)
    {
        throw std::invalid_argument("Set test object first!\n");
    }

    mResultsFilename = ((mBenchmarkName.size())? mBenchmarkName : "unnamed_") + getTimeString()
            + "(v" +std::to_string(rand() % 1000) + ").txt";

    mPipeline.emitEvent(ReconfigurationEvent(mBenchmarkName, mResultsFilename, mRoundsCount,
                                             (prevObjectPtr == mTestObj), mFileFormat));

    prevObjectPtr = mTestObj;
}

void Benchmaker::freeTestObject()
{
    delete mTestObj;
    mTestObj = nullptr;
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


void Benchmaker::setTestingParam(int x)
{
    mParamGenerator = [x] ()
    {
        static bool isUsed = false;
        if (!isUsed)
        {
            isUsed = true;
            return std::make_pair(hasNext, x);
        }
        else
        {
            isUsed = false; // clear flag
            return std::make_pair(!hasNext, 0);
        }
    };
}

void Benchmaker::setTestingParam(int from, int to, int step)
{
    mParamGenerator = [from, to, step] ()
    {
        static int lastVal = 0;
        static bool isUsed = false;
        if (isUsed)
        {
            lastVal += step;
            if (lastVal > to)
            {
                isUsed = false; // clear
                return std::make_pair(!hasNext, 0);
            }
        }
        else
        {
            lastVal = from;
            isUsed = true;
        }
        return std::make_pair(hasNext, lastVal);
    };
}

void Benchmaker::setTestingParam(std::initializer_list<int> list)
{
    mParamList.clear();
    mParamList.reserve(list.size());
    for (int const &x : list)
        mParamList.push_back(x);
    mParamGenerator = [this] ()
    {
        static int idx = 0;
        if (idx < mParamList.size())
            return std::make_pair(hasNext, mParamList[idx++]);
        else
        {
            idx = 0;
            mParamList.clear();
            return std::make_pair(!hasNext, 0);
        }
    };
}

void Benchmaker::setTestingParam(Benchmaker::ParamGenerator paramYielder)
{
    mParamGenerator = paramYielder;
}
