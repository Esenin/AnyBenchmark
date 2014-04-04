#include "benchmaker.h"

using std::cout;
using std::endl;

Benchmaker::Benchmaker()
	: mLogToFile(false)
	, mRoundsCount(10)
	, mTestObj(nullptr)
	, mLogger(nullptr)
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
		mLogger->write(QString("  N  \tTime\n").toUtf8());
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

	cout << "Test\t" << mBenchmarkName.toStdString() << "\thave been started\n";

	QTime startBenchmarkTime = QTime::currentTime();
	int curSize = startValue;

	do
	{
		QTime startRoundTime = QTime::currentTime();
		double average = 0;
		for (int i = 0; i < mRoundsCount; i++)
		{
			average += makeRound(curSize);
		}
		average /= mRoundsCount;

		if (mLogToFile)
		{
			putToFile(curSize, average);
		}

		cout << "N = " << curSize
				<< "\taverage is " << average
				<< " msecs, \tTime for round: " << startRoundTime.secsTo(QTime::currentTime()) << " sec"
				<< endl;
		curSize += ((stepSize > 0)? stepSize : 1);
	}
	while (curSize <= maxValue);

	unsigned int totalTime = startBenchmarkTime.secsTo(QTime::currentTime());
	cout << "Benchmark already done! Total time: " << totalTime
			<< " seconds (" << (double)totalTime / 60 << " minutes)\n\n";

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

void Benchmaker::setBenchmarkName(QString const &name)
{
	mBenchmarkName = name + "_";
}

void Benchmaker::setRoundsCount(int const &count)
{
	mRoundsCount = count;
}

unsigned int Benchmaker::makeRound(int const &paramN)
{
	mTestObj->setParam(paramN);
	mTestObj->prepare();

	unsigned int result = makeTest();

	mTestObj->clear();

	return result;
}

unsigned int Benchmaker::makeTest()
{
	QTime startTime = QTime::currentTime();
	unsigned int msecs = 0;

	mTestObj->run();

	msecs = startTime.msecsTo(QTime::currentTime());
	return msecs;
}

void Benchmaker::freeTestObject()
{
	if (mTestObj != nullptr)
	{
		delete mTestObj;
		mTestObj = nullptr;
	}
}

void Benchmaker::createFile()
{
	mBenchmarkName = (mBenchmarkName.count())? mBenchmarkName : "unnamed_";
	mLogger = new QFile (mBenchmarkName + QTime::currentTime().toString("hh-mm-ss-zzz") + ".txt");
	if (!mLogger->open(QFile::WriteOnly))
	{
		mLogToFile = false;
		cout << "Cannot open file: " << mLogger->fileName().toStdString() << endl;
	}
}

void Benchmaker::putToFile(int const param, double const &average)
{
	QString ave = QString::number(param) + " \t" + QString::number(average) + "\n";
	mLogger->write(ave.toUtf8());
	mLogger->flush();
}

void Benchmaker::closeFile()
{
	if (mLogger == nullptr || !mLogToFile)
		return;

	cout << "\n Tests result stored at: " << mLogger->fileName().toStdString() << endl << endl;
	mLogger->close();
	delete mLogger;
}

