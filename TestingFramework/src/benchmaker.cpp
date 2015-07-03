#include "benchmaker.h"

using std::cout;
using std::endl;
using namespace Benchmark;

Benchmaker::Benchmaker()
    : mFileFormat(FileOutput::none)
    , mRoundsCount(10)
    , mTestObj(nullptr)
{
    mPipeline.appendHandler(UniqueEventHandler(new ConsoleWriter()));
    mPipeline.appendHandler(UniqueEventHandler(new FileWriter()));
}

Benchmaker::~Benchmaker()
{
    freeTestObject();
    mPipeline.resetPipeline();
}

void Benchmaker::makeBenchmark(int const &startValue, int const &maxValue, int const &stepSize)
{
    configureBenchmark();
    mPipeline.emitEvent(BenchmarkStartedEvent());

    int mainParam = startValue;
    do
    {
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
                cout << "Test-subject\'s behavior is wrong. \nBreak\n"
                     << "cause: " << e.what() << endl;
                break;
            }
        }
        average /= mRoundsCount;
        mPipeline.emitEvent(RoundSeriesFinishedEvent(mainParam, average));

        mainParam += ((stepSize > 0)? stepSize : 1);
    }
    while (mainParam <= maxValue);

    mPipeline.emitEvent(BenchmarkFinishedEvent());


}

void Benchmaker::setRunnableObject(ITestObject *object)
{
    freeTestObject();
    mTestObj = object;
    mBenchmarkName = "";
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


