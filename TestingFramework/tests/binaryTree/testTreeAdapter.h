#pragma once

#include <math.h>
#include <random>
#include <limits>
#include <thread>
#include <vector>

//#include <QDebug>

#include "../../src/testObject.h"
#include "bTree.h"
#include "advancedAvlTree.h"
#include "avlTree.h"
#include "stlMap.h"
#include "vebLayout.h"
#include "splayTreeWrap.h"

namespace Tree
{
enum TreeType
{
	b
	, advancedAvlTree
	, avlTree
	, stdRBTree
	, vebLayoutTree
	, splay
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
	std::vector<Type> mRequests;

	void createTree(TreeType type);
	void createDistributer();
	void createRequests();
	void freeTree();
};
}
