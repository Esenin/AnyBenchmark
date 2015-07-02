#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "testObject.h"

namespace Benchmark
{

//! @class Benchmaker makes tests routine measuring average time for test
class Benchmaker
{
public:
    Benchmaker();
    ~Benchmaker();

    //! @arg count shows how much repeats of single test will be done to get average value
    void setRoundsCount(unsigned int const &count = 10);

    //! @arg object is a subject that will be tested
    void setRunnableObject(TestObject *object);

    //! start benchmark on given object
    //! @arg startValue is start param "N"
    //! @arg maxValue is max bound of tests
    //! @arg stepSize is a positive difference between each test
    void makeBenchmark(int const &startValue = 200, int const &maxValue = 1400, int const &stepSize = 50);

    //! @arg mustLog switches mode of logging to file
    void setLogginToFile(bool const &mustLog);

    //! @arg name is prefix of filename with tests result
    //! must be called After setting new runnable object
    void setBenchmarkName(std::string const &name);


private:
    bool mLogToFile;
    int mRoundsCount;
    TestObject *mTestObj;
    std::fstream mLogger;
    std::string mBenchmarkName;
    std::string mResultsFilename;

    //! makes preparation before- and cleaning after test
    //! @return time per test in msec
    unsigned int makeRound(int const &paramN);
    //! runs single test
    unsigned int makeTest();
    void freeTestObject();
    void createFile();
    std::string getTimeString();
    void startLogging();
    void putToFile(int const param, double const &average);
    void closeFile();
};

}
