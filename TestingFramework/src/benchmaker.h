#pragma once

#include <QtCore/QFile>
#include <QtCore/QList>
#include <QtCore/QTime>

#include "matrixMultiplier.h"
#include "recursiveMultiplier.h"
#include "regularMultiplier.h"
#include "transposedMultiplier.h"

enum Multiplier
{
	Regular
	, Transposed
	, Recursive
};

class Benchmaker
{
public:
	Benchmaker();
	~Benchmaker();

	void setRoundsCount(int const &count);
	void makeBenchmark(int const startValue = 200, int const maxValue = 1400, int const stepSize = 50);

	void setRunnableObject(Multiplier const type);
	void setLogginToFile(bool const mustLog);

private:
	bool mLogToFile;
	int mRoundsCount;
	int *sourceArray;
	MatrixMultiplier *mMultiplier;
	Multiplier mCurType;
	QFile *mLogger;

	unsigned int makeRound(int const &arrSize = 100);
	unsigned int multiplyTest();
	void createTestObject();
	void freeTestObject();
	void createFile();
	void putToFile(int const param, double const &average);
	void closeFile();
};

