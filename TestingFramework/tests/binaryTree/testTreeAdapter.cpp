#include "testTreeAdapter.h"

using namespace Tree;

TestTreeAdapter::TestTreeAdapter(TreeType const type)
	: mTree(nullptr)
	, mNormal(nullptr)
	, mInputSize(0)
	, mOffset(0)
	, mTreeParam(40)
	, mTreeType(type)
{
	int const seed = 2014;
	mGenerator.seed(seed);
}

TestTreeAdapter::TestTreeAdapter(int const &bTreeSize)
	: TestTreeAdapter(TreeType::b)
{
	mTreeParam = bTreeSize;
}

TestTreeAdapter::~TestTreeAdapter()
{
	freeTree();
	delete mNormal;
}

void TestTreeAdapter::setParam(int const &param)
{
	mInputSize = param;
	mOffset = mInputSize / 2;
}

void TestTreeAdapter::prepare()
{
	createTree(mTreeType);
	createDistributer();
	std::thread requestFilling(&TestTreeAdapter::createRequests, this);

	Type leftPointer = 0;
	Type rightPointer = mInputSize - 1;
	while (rightPointer - leftPointer >= 0)
	{
		mTree->insert(leftPointer++);
		mTree->insert(rightPointer--);
	}

	if (mTree->isBuildable())
	{
		mTree->buildTree();
	}

	requestFilling.join();
}

void TestTreeAdapter::run() throw(Error)
{
	int const peekCount = 1000000;
	for (int i = 0; i < peekCount; i++)
	{
		if (!mTree->lookup(mRequests[i % mInputSize]))
		{
			throw Error();
		}
	}
}

void TestTreeAdapter::clear()
{
	freeTree();
	mRequests.clear();
}

void TestTreeAdapter::createTree(TreeType type)
{
	switch (type)
	{
	case b:
		mTree = new BTree(mTreeParam);
		break;
	case advancedAvlTree:
		mTree = new AdvancedAvlTree();
		break;
	case avlTree:
		mTree = new AVLTree();
		break;
	case stdRBTree:
		mTree = new StlMap();
		break;
	case vebLayoutTree:
		mTree = new VebLayoutTree();
		break;
	case splay:
		mTree = new SplayTreeWrap();
		break;
	default:
	{
		throw std::runtime_error("unexpected tree type");
	}
	}
}

void TestTreeAdapter::createDistributer()
{
	if (mNormal != nullptr)
	{
		delete mNormal;
	}
	double const tenPercentCovering = 0.354;
	double const mean = mInputSize / 2;
	int const radius = mInputSize / 3 * 2;
	double const sigma = std::sqrt(radius) * std::sqrt(tenPercentCovering * std::sqrt(radius));
	mNormal = new std::normal_distribution<double>(mean, sigma);
}

void TestTreeAdapter::createRequests()
{
//	Type min = mInputSize;
//	Type max = -mInputSize;
	for (Type i = 0; i < mInputSize; i++)
	{
		Type current = static_cast<Type>((*mNormal)(mGenerator));

		//Type current = lrand48() % mInputSize;
//		if (current > mInputSize)
//			current = mInputSize - 1;
//		if (current < 0)
//			current = 0;
		mRequests.push_back(current);
//		if (current < min)
//			min = current;
//		if (current > max)
//			max = current;
	}
//	qDebug() << "from" << min << "to " << max << "\t rate" << QString::number(double(max - min) / mInputSize, 'f')
//			<< "% c" << mInputSize;
}

void TestTreeAdapter::freeTree()
{
	if (mTree != nullptr)
	{
		delete mTree;
		mTree = nullptr;
	}
}
