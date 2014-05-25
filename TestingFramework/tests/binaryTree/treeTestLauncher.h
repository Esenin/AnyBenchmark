#pragma once

#include <set>

#include "tests/binaryTree/testTreeAdapter.h"

using Tree::TestTreeAdapter;

//! some simple tests for validation of trees
void treePretests()
{
	int const testSize = 10000;
	std::vector<Tree::ITree*> trees;
	trees.push_back(new Tree::StlMap());
	trees.push_back(new Tree::AdvancedAvlTree());
	trees.push_back(new Tree::AVLTree());
	trees.push_back(new Tree::VebLayoutTree());
	trees.push_back(new Tree::SplayTreeWrap());
	trees.push_back(new Tree::BTree());

	std::set<int> requests;
	for (int i = 0; i < testSize / 10; ++i)
	{
		int value = rand() % testSize;
		requests.insert(value);
		for (Tree::ITree *tree : trees)
		{
			tree->insert(value);
		}
	}

	for (Tree::ITree *tree : trees)
	{
		if (tree->isBuildable())
			tree->buildTree();
	}

	for (int i = testSize; i >= 0; --i)
	{
		bool answer = requests.find(i) != requests.end();
		for (Tree::ITree *tree : trees)
		{
			Q_ASSERT(tree->lookup(i) == answer);
		}
	}

	for (Tree::ITree *tree : trees)
	{
		delete tree;
	}
}

//! that is a benchmark config
void makeBenchmarkSet(Benchmaker &benchmark, TestTreeAdapter *tree, QString const &name = QString(""))
{
	int const startSize = 1 * 1000 * 1000;
	int const maxSize = 15 * 1000 * 1000;
	int const stepSize = 500 * 1000;

	benchmark.setRunnableObject(tree);
	benchmark.setBenchmarkName(name);
	benchmark.makeBenchmark(10000, 0, 10000);
	//benchmark.makeBenchmark(startSize, maxSize, stepSize);
}

//! Complect of trees for performance test
void treesBenchmark(Benchmaker &benchmark)
{
	treePretests();

	benchmark.setRoundsCount(7);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::vebLayoutTree), "vebLayoutTree");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::splay), "splay");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::avlTree), "Avl");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(64), "btree64");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::advancedAvlTree), "advancedAvlTree");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(Tree::stdRBTree), "stlRBTree");
}

void bTreeParamTuning(Benchmaker &benchmark)
{
	treePretests();
	benchmark.setRoundsCount(5);

	makeBenchmarkSet(benchmark, new TestTreeAdapter(160), "btree160");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(128), "btree128");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(96), "btree96");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(64), "btree64");

	makeBenchmarkSet(benchmark, new TestTreeAdapter(32), "btree32");
}
