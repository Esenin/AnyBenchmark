#pragma once

#include "tests/binaryTree/testTreeAdapter.h"

using Tree::TestTreeAdapter;

//! some simple tests for validation of trees
void treePretests()
{
	int const testSize = 10000;
	Tree::BTree *bTree = new Tree::BTree();
	Tree::SplayTree *splayTree = new Tree::SplayTree();
	Tree::VEBoasTree<32> *vEBTree = new Tree::VEBoasTree<32>();
	Tree::VEBLayoutBinTree *vebLayoutTree = new Tree::VEBLayoutBinTree();
	Tree::AVLTree *avlTree = new Tree::AVLTree();
	for (int i = 0; i < testSize; i++)
	{
		bTree->insert(i);
		splayTree->insert(i);
		vEBTree->insert(i);
		vebLayoutTree->insert(i);
		avlTree->insert(i);
	}

	vebLayoutTree->buildTree();
	for (int i = 0; i < testSize; i++)
	{
		Q_ASSERT
		(
				bTree->lookup(i)
				&& splayTree->lookup(i)
				&& vEBTree->lookup(i)
				&& vebLayoutTree->lookup(i)
				&& avlTree->lookup(i)
		);
	}
	Q_ASSERT
	(
			!bTree->lookup(-1)
			&& !splayTree->lookup(-1)
			&& !vEBTree->lookup(-1)
			&& !vebLayoutTree->lookup(-1)
			&& !avlTree->lookup(-1)
	);

	delete avlTree;
	delete vebLayoutTree;
	delete vEBTree;
	delete splayTree;
	delete bTree;
}

//! that is a benchmark config
void makeBenchmarkSet(Benchmaker &benchmark, TestTreeAdapter *tree, QString const &name = QString(""))
{
	int const startSize = 5 * 1000 * 1000;
	int const maxSize = 10 * 1000 * 1000;
	int const stepSize = 5 * 1000 * 1000;

	benchmark.setRunnableObject(tree);
	benchmark.setBenchmarkName(name);
	benchmark.makeBenchmark(1000, 10000, 1000);
	benchmark.makeBenchmark(startSize, maxSize, stepSize);
}

//! Complect of trees for performance test
void treesBenchmark(Benchmaker &benchmark)
{
	treePretests();

	benchmark.setRoundsCount(5);
	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::splay), "splay_insert_only");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::b), "btree40");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vanEmdeBoas), "vEBoas");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vebLayoutBinTree), "vebLayoutBinTree");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::avlTree), "avlTree");
}
