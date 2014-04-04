#include <math.h>
#include "testTreeAdapter.h"

using namespace Tree;

TestTreeAdapter::TestTreeAdapter(TreeType const type)
	: mInput(nullptr)
	, mTree(nullptr)
	, mNormal(nullptr)
	, mInputSize(0)
	, mTreeType(type)

{
}

TestTreeAdapter::~TestTreeAdapter()
{
	freeTree();
	freeTestArray();
	delete mNormal;
}

void TestTreeAdapter::setParam(int const &param)
{
	mInputSize = param;
}

void TestTreeAdapter::prepare()
{
	createTree(mTreeType);
	createDistributer();
	mInput = new unsigned long long[mInputSize];

	unsigned long long value = 0;
	int counter = 0;
	while (counter < mInputSize)
	{
		value = static_cast<unsigned long long>((*mNormal)(mGenerator));
		if (value > maxNumber - 1)
			continue;
		mInput[counter] = value;
		mTree->insert(value);
		mTree->insert(value + 1);
		counter++;
	}
}

void TestTreeAdapter::run() throw(Error)
{
	int const peekCount = 10000;

	for (int i = 0; i < peekCount; i++)
	{
		mTree->lookup(mInput[i % mInputSize]);
	}
}

void TestTreeAdapter::clear()
{
	freeTree();
	freeTestArray();
}

void TestTreeAdapter::freeTestArray()
{
	if (mInput != nullptr)
	{
		delete[] mInput;
		mInput = nullptr;
	}
}

void TestTreeAdapter::createTree(TreeType type)
{
	switch (type)
	{
	case splay:
		mTree = new SplayTree();
		break;
	case vanEmdeBoas:
		mTree = new VEBoasTree<32>();
		break;
	case b:
		mTree = new BTree();
		break;
	}
}

void TestTreeAdapter::createDistributer()
{
	if (mNormal != nullptr)
	{
		delete mNormal;
	}
	double const mean = maxNumber / 2;
	double const sigma = 3.0 / 14.0 * mInputSize;
	mNormal = new std::normal_distribution<double>(mean, sigma);
}

void TestTreeAdapter::freeTree()
{
	if (mTree != nullptr)
	{
		delete mTree;
		mTree = nullptr;
	}
}
