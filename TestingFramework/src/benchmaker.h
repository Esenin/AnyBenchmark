#pragma once

#include <QtCore/QFile>
#include <QtCore/QList>
#include <QtCore/QTime>
#include <iostream>

#include "testObject.h"

//! @class Benchmaker makes tests routine measuring average time for test
class Benchmaker
{
public:
	Benchmaker();
	~Benchmaker();

	//! @arg count shows how much repeats of single test will be done to get average value
	void setRoundsCount(int const &count);

	//! @arg object is a subject that will be tested
	void setRunnableObject(TestObject *object);

	//! start benchmark on given object
	//! @arg startValue is start param "N"
	//! @arg maxValue is max bound of tests
	//! @arg stepSize is a positive difference between each test
	void makeBenchmark(int const &startValue = 200, int const &maxValue = 1400, int const &stepSize = 50);

	//! @arg mustLog switches mode of logging to file
	void setLogginToFile(bool const &mustLog);

private:
	bool mLogToFile;
	int mRoundsCount;
	TestObject *mTestObj;
	QFile *mLogger;

	//! makes preparation before- and cleaning after test
	//! @return time per test in msec
	unsigned int makeRound(int const &paramN);
	//! runs single test
	unsigned int makeTest();
	void freeTestObject();
	void createFile();
	void putToFile(int const param, double const &average);
	void closeFile();
};

