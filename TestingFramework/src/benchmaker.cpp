#include "benchmaker.h"

Benchmaker::Benchmaker()
	: mLogToFile(false)
	, mRoundsCount(10)
	, mLogger(NULL)
{
	ArrayMaster::randomize();
}

Benchmaker::~Benchmaker()
{
	freeTestObject();
}

void Benchmaker::makeBenchmark(int const startValue, int const maxValue, int const stepSize)
{
	if (mLogToFile)
	{
		createFile();
		mLogger->write(QString("  N  \tTime\n").toUtf8());
	}

	cout << "Tests have been started\n";

	QTime startBenchmarkTime = QTime::currentTime();
	int curSize = startValue;
	createTestObject();

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
				<< " msecs, \t\t Time for round: " << startRoundTime.secsTo(QTime::currentTime()) << " sec"
				<< endl;
		curSize += stepSize;
	}
	while (curSize <= maxValue);

	unsigned int totalTime = startBenchmarkTime.secsTo(QTime::currentTime());
	cout << "Benchmark already done! Total time: " << totalTime
			<< " seconds (" << (double)totalTime / 60 << " minutes)\n\n";

	freeTestObject();
	closeFile();
}

void Benchmaker::setRunnableObject(Multiplier const type)
{
	mCurType = type;
}

void Benchmaker::setLogginToFile(const bool mustLog)
{
	mLogToFile = mustLog;
}

void Benchmaker::setRoundsCount(int const &count)
{
	mRoundsCount = count;
}

unsigned int Benchmaker::makeRound(int const &arrSize)
{
	mMultiplier->setMatrixSize(arrSize);
	mMultiplier->prepareMatrixes();

	unsigned int result = multiplyTest();

	mMultiplier->clear();

	return result;
}

unsigned int Benchmaker::multiplyTest()
{
	QTime startTime = QTime::currentTime();
	unsigned int msecs = 0;

	mMultiplier->run();

	msecs =  startTime.msecsTo(QTime::currentTime());
	return msecs;
}

void Benchmaker::createTestObject()
{
	switch( mCurType)
	{
	case Regular:
		mMultiplier = new RegularMultiplier();
		break;
	case Transposed:
		mMultiplier = new TransposedMultiplier();
		break;
	case Recursive:
		mMultiplier = new RecursiveMultiplier();
		break;
	}
}

void Benchmaker::freeTestObject()
{
	if (mMultiplier != NULL)
	{
		delete mMultiplier;
		mMultiplier = NULL;
	}
}

void Benchmaker::createFile()
{
	mLogger = new QFile ("multiplication_" + QTime::currentTime().toString("hh-mm-ss") + ".txt");
	mLogger->open(QFile::WriteOnly);
}

void Benchmaker::putToFile(int const param, double const &average)
{
	QString ave = QString::number(param) + " \t" + QString::number(average) + "\n";
	mLogger->write(ave.toUtf8());
	mLogger->flush();
}

void Benchmaker::closeFile()
{
	if (mLogger == NULL)
		return;

	cout << "\n Tests result stored at: " << mLogger->fileName().toStdString() << endl << endl;
	mLogger->close();
	delete mLogger;
}

