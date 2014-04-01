#pragma once

#include <QtCore/QFile>
#include <QtCore/QList>
#include <QtCore/QTime>
#include <iostream>

#include "testObject.h"

class Benchmaker
{
public:
	Benchmaker();
	~Benchmaker();

	void setRoundsCount(int const &count);
	void makeBenchmark(int const &startValue = 200, int const &maxValue = 1400, int const &stepSize = 50);

	void setRunnableObject(TestObject *object);
	void setLogginToFile(bool const &mustLog);

private:
	bool mLogToFile;
	int mRoundsCount;
	TestObject *mTestObj;
	QFile *mLogger;

	unsigned int makeRound(int const &paramN);
	unsigned int makeTest();
	void freeTestObject();
	void createFile();
	void putToFile(int const param, double const &average);
	void closeFile();
};

