#pragma once

#include "tests/binaryTree/testTreeAdapter.h"

using Tree::TestTreeAdapter;

//! some simple tests for validation of trees
void treePretests()
{
	int const testSize = 10000;
	Tree::StlMap stlMap;
	Tree::BTree *bTree = new Tree::BTree(40);
	Tree::VEBLayoutBinTree *vebLayoutTree = new Tree::VEBLayoutBinTree();
	Tree::AVLTree *avlTree = new Tree::AVLTree();
	for (int i = 0; i < testSize; i++)
	{
		bTree->insert(i);
		vebLayoutTree->insert(i);
		avlTree->insert(i);
		stlMap.insert(i);
	}

	vebLayoutTree->buildTree();
	for (int i = testSize - 1; i >= 0; i--)
	{
		Q_ASSERT
		(
				bTree->lookup(i)
				&& vebLayoutTree->lookup(i)
				&& avlTree->lookup(i)
				&& stlMap.lookup(i)
		);
	}
	Q_ASSERT
	(
			!bTree->lookup(-1)
			&& !vebLayoutTree->lookup(-1)
			&& !avlTree->lookup(-1)
			&& !stlMap.lookup(-1)
	);

	delete avlTree;
	delete vebLayoutTree;
	delete bTree;
}

//! that is a benchmark config
void makeBenchmarkSet(Benchmaker &benchmark, TestTreeAdapter *tree, QString const &name = QString(""))
{
	int const startSize = 20 * 1000 * 1000;
	int const maxSize = 4 * 1000 * 1000;
	int const stepSize = 5 * 1000 * 1000;

	benchmark.setRunnableObject(tree);
	benchmark.setBenchmarkName(name);
	//benchmark.makeBenchmark(2000, 10000, 2000);
	benchmark.makeBenchmark(startSize, maxSize, stepSize);
}

//! Complect of trees for performance test
void treesBenchmark(Benchmaker &benchmark)
{
	treePretests();

	benchmark.setRoundsCount(3);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::b), "btree40");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vebLayoutBinTree), "vebLayoutBinTree");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::avlTree), "avlTree");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::stdRBTree), "stlRBTree");
}

void bTreeParamTuning(Benchmaker &benchmark)
{
	treePretests();
	benchmark.setRoundsCount(3);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vebLayoutBinTree), "AVL-L");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(10), "btree10");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(20), "btree20");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(40), "btree40");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(100), "btree100");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(1000), "btree1000");
}
