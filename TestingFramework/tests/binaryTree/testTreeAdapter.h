#pragma once

#include <math.h>
#include <random>
#include <limits>
#include <thread>
#include <vector>

#include "../../src/testObject.h"
#include "bTree.h"
#include "vEBLayoutBinTree.h"
#include "avlTree.h"
#include "stlMap.h"

namespace Tree
{
enum TreeType
{
	b
	, vebLayoutBinTree
	, avlTree
	, stdRBTree
};

//! @class TestTreeAdapter is a wrap of Tree for a benchmark
class TestTreeAdapter : public TestObject
{
public:
	//! @arg type select what kind of tree will be used in testing
	TestTreeAdapter(TreeType const type);
	TestTreeAdapter(int const &bTreeSize);
	virtual ~TestTreeAdapter();

	//! @arg param is size of test-input
	virtual void setParam(int const &param);
	virtual void prepare();
	virtual void run() throw(Error);
	virtual void clear();

protected:
	Tree::ITree *mTree;
	std::normal_distribution<double> *mNormal;
	int mInputSize;
	int mOffset;
	int mTreeParam;
	std::mt19937 mGenerator;
	TreeType mTreeType;
	std::vector<long long> mRequests;

	void createTree(TreeType type);
	void createDistributer();
	void createRequests();
	void freeTree();
};
}
