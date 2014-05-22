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
	int const startSize = 5 * 1000 * 1000;
	int const maxSize = 30 * 1000 * 1000;
	int const stepSize = 5 * 1000 * 1000;

	benchmark.setRunnableObject(tree);
	benchmark.setBenchmarkName(name);
	benchmark.makeBenchmark(startSize, startSize, 0);
	//benchmark.makeBenchmark(startSize, maxSize, stepSize);
}

//! Complect of trees for performance test
void treesBenchmark(Benchmaker &benchmark)
{
	treePretests();

	benchmark.setRoundsCount(5);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::b), "btree40");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vebLayoutBinTree), "vebLayoutBinTree");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::avlTree), "avlTree");

	//makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::stdRBTree), "stlRBTree");
}

void bTreeParamTuning(Benchmaker &benchmark)
{
	treePretests();
	benchmark.setRoundsCount(5);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(32), "btree32");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(64), "btree64");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(96), "btree96");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(128), "btree128");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(160), "btree160");
}
