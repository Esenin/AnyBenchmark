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
	mGenerator.seed(std::time(0));
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

	long long leftPointer = 0;
	long long rightPointer = mInputSize - 1;
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
	case vebLayoutBinTree:
		mTree = new VEBLayoutBinTree();
		break;
	case avlTree:
		mTree = new AVLTree();
		break;
	case stdRBTree:
		mTree = new StlMap();
	}
}

void TestTreeAdapter::createDistributer()
{
	if (mNormal != nullptr)
	{
		delete mNormal;
	}
	double const mean = mInputSize / 2;
	double const sigma = 2 * std::log(mean);
	mNormal = new std::normal_distribution<double>(mean, sigma);
}

void TestTreeAdapter::createRequests()
{
	for (int i = 0; i < mInputSize; i++)
	{
		mRequests.push_back(static_cast<long long>((*mNormal)(mGenerator)));
	}
}

void TestTreeAdapter::freeTree()
{
	if (mTree != nullptr)
	{
		delete mTree;
		mTree = nullptr;
	}
}
