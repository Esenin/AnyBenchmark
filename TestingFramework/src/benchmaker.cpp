#include "../include/benchmaker.h"
#include <thread>
#include <cmath>

#include "../src/pipelineHandlers/consoleWriter.h"
#include "../src/pipelineHandlers/fileWriter.h"

using std::cout;
using std::endl;
using namespace benchmark;
using namespace benchmark::impl;

bool const hasNext = true;

namespace
{
struct TimeValue
{
    decltype(std::chrono::steady_clock::now()) realTV;
    clock_t cpuTV;
};

inline void burnTimestamp(TimeValue &start)
{
    start.cpuTV = clock();
    start.realTV = std::chrono::steady_clock::now();
}

long getElapsedTime(TimeValue const &start, TimeValue const &stop, MeasureType const &type)
{
    long const cputvDiff = (type != MeasureType::realTime)?
                           static_cast<long>(double(stop.cpuTV - start.cpuTV) / CLOCKS_PER_SEC * 1000)
                           : 0;

    long const rtvDiff = (type != MeasureType::cpuTime)?
                         std::chrono::duration_cast<std::chrono::milliseconds>(stop.realTV - start.realTV).count()
                         : 0;

    switch (type)
    {
        case MeasureType::cpuTime:
            return cputvDiff;
        case MeasureType::realTime:
            return rtvDiff;
        case MeasureType::hybrid:
            return static_cast<long>((2 * double(cputvDiff) + double(rtvDiff)) / 3 );
    }
}

} // anonymous namespace

namespace
{
    int const noGroupAvailable = -1;

} // anonymous namespace

Benchmaker::Benchmaker()
        : mFileFormat(FileOutput::none)
        , mMeasureType(MeasureType::cpuTime)
        , mGroupId(noGroupAvailable)
        , mRoundsCount(10)
        , mDivisionFactor(0)
        , mTestObj(nullptr)
        , mParamGenerator([]() { return std::make_pair(false, 0); })
{
    srand(static_cast<uint32_t>(clock()));
    mPipeline.appendHandler(UniqueEventHandler(new ConsoleWriter()));
    mPipeline.appendHandler(UniqueEventHandler(new FileWriter()));
}

Benchmaker::~Benchmaker()
{
    freeTestObject();
    mPipeline.resetPipeline();
}

ResultsQueue Benchmaker::makeBenchmark()
{
    configureBenchmark();
    mPipeline.emitEvent(BenchmarkStartedEvent(mGroupId));

    std::pair<bool, int> nextArg;
    while ((nextArg = mParamGenerator()).first == hasNext)
    {
        int mainParam = nextArg.second;
        mPipeline.emitEvent(RoundSeriesStartedEvent(mainParam));
        long double average = 0;
        int const warmupIterations = 1;
        for (int i = 0; i < mRoundsCount + warmupIterations; i++)
        {
            try
            {
                if (i)
                    average += makeRound(mainParam);
                else
                    makeRound(mainParam); // first iteration for warmup
            }
            catch (std::exception &e)
            {
                mPipeline.emitEvent(BenchmarkCrashedEvent(e.what()));
                throw;
            }
        }
        average /= mRoundsCount;
        if (mDivisionFactor)
            average /= mDivisionFactor;
        mPipeline.emitEvent(RoundSeriesFinishedEvent(mainParam, average));
        mBenchmarkResults.push_back(std::make_tuple(mainParam, average));
    }

    mPipeline.emitEvent(BenchmarkFinishedEvent(&mBenchmarkResults));
    return mBenchmarkResults;
}

void Benchmaker::setRunnableObject(ITestObject *object)
{
    freeTestObject();
    mTestObj = object;
}

void Benchmaker::setLogginToFile(FileOutput const format)
{
    if (mGroupId > noGroupAvailable + 1) // group benchmarking is already started
    {
        WARNING("Ignoring fileformat change: group benchmarks are already started");
        return;
    }
    mFileFormat = format;
}

void Benchmaker::setBenchmarkName(std::string const &name)
{
    mBenchmarkName = name;
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
    TimeValue start, stop;
    burnTimestamp(start);

    mTestObj->run();

    burnTimestamp(stop);
    return getElapsedTime(start, stop, mMeasureType);
}

void Benchmaker::configureBenchmark()
{
    static ITestObject *prevObjectPtr = nullptr;
    if (!mTestObj)
    {
        throw std::invalid_argument("Set test object first!\n");
    }

    mBenchmarkName = ((mBenchmarkName.size())? mBenchmarkName : "unnamed");

    mResultsFilename = (mGroupId <= noGroupAvailable + 1)? constructFilename() : mResultsFilename;

    mPipeline.emitEvent(ReconfigurationEvent(mBenchmarkName, mResultsFilename, mRoundsCount, (prevObjectPtr == mTestObj)
                                             , mFileFormat, mGroupId != noGroupAvailable));

    if (mGroupId != noGroupAvailable)
        ++mGroupId;

    prevObjectPtr = mTestObj;

    mBenchmarkResults.clear();
}

void Benchmaker::freeTestObject()
{
    delete mTestObj;
    mTestObj = nullptr;
}

void Benchmaker::setTestingParam(int x)
{
    if (mGroupId > noGroupAvailable + 1)
    {
        WARNING("Ignoring param generator change among group benchmark");
        return;
    }
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
            isUsed = false;
            return std::make_pair(!hasNext, 0);
        }
    };
}

void Benchmaker::setTestingParam(int from, int to, int step)
{
    if (mGroupId > noGroupAvailable + 1)
    {
        WARNING("Ignoring param generator change among group benchmark");
        return;
    }
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
    if (mGroupId > noGroupAvailable + 1)
    {
        WARNING("Ignoring param generator change among group benchmark");
        return;
    }
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
            return std::make_pair(!hasNext, 0);
        }
    };
}

void Benchmaker::setTestingParam(Benchmaker::ParamGenerator paramYielder)
{
    if (mGroupId > noGroupAvailable + 1)
    {
        WARNING("Ignoring param generator change among group benchmark");
        return;
    }
    mParamGenerator = paramYielder;
}

void Benchmaker::setMeasureType(MeasureType measureType)
{
    mMeasureType = measureType;
}

void Benchmaker::setDivisionFactor(size_t value)
{
    mDivisionFactor = value;
}

void Benchmaker::endGroup()
{
    mGroupId = noGroupAvailable;
    mPipeline.emitEvent(ReconfigurationEvent(mBenchmarkName, mResultsFilename, mRoundsCount, false, mFileFormat, false));
}

void Benchmaker::beginGroup()
{
    mGroupId = noGroupAvailable + 1;
}


std::string Benchmaker::getTimeString() const
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

std::string Benchmaker::constructFilename() const
{
    return (mGroupId != noGroupAvailable? "group_" : "") + mBenchmarkName + "_"
    + getTimeString() + "." +std::to_string(rand() % 1000) + "."
    + (mFileFormat == FileOutput::csv? "csv" : "txt");
}
