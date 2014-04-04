#pragma once

#include <random>

#include "../../src/testObject.h"
#include "bTree.h"
#include "splayTree.h"
#include "vanEmdeBoasTree.h"

enum TreeType
{
	b
	, splay
	, vanEmdeBoas
};

class TestTreeAdapter : public TestObject
{
public:
	TestTreeAdapter(TreeType const type);
	virtual ~TestTreeAdapter();

	//! @arg param is size of test-input
	virtual void setParam(int const &param);
	virtual void prepare();
	virtual void run() throw(Error);
	virtual void clear();


protected:
	unsigned long long *mInput;
	Tree::ITree *mTree;
	std::normal_distribution<double> *mNormal;
	static unsigned long long const maxNumber = (1ULL << 32);
	int mInputSize;
	std::mt19937 mGenerator;
	TreeType mTreeType;
	int mOffset;

	void freeTestArray();

	void createTree(TreeType type);
	void createDistributer();
	void freeTree();
};

