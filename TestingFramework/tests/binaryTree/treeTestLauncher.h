#pragma once

#include "tests/binaryTree/testTreeAdapter.h"

void treePretests()
{
	int const testSize = 10000;
	Tree::BTree *bTree = new Tree::BTree();
	Tree::SplayTree *splayTree = new Tree::SplayTree();
	Tree::VEBoasTree<32> *vEBTree = new Tree::VEBoasTree<32>();
	for (int i = 0; i < testSize; i++)
	{
		bTree->insert(i);
		splayTree->insert(i);
		vEBTree->insert(i);
	}
	for (int i = 0; i < testSize; i++)
	{
		Q_ASSERT
		(
			bTree->lookup(i)
			&& splayTree->lookup(i)
			&& vEBTree->lookup(i)
		);
	}
	Q_ASSERT(!bTree->lookup(-1) && !splayTree->lookup(-1) && !vEBTree->lookup(-1));

	delete vEBTree;
	delete splayTree;
	delete bTree;
}

void treesBenchmark(Benchmaker &benchmark)
{
	int const startSize = 500 * 1000;
	int const maxSize = 5 * 1000 * 1000;
	int const stepSize = 500 * 1000;

	treePretests();
	benchmark.setRoundsCount(2);
	benchmark.setRunnableObject(new TestTreeAdapter(splay));
	benchmark.setBenchmarkName("splay_only-insert");
	benchmark.makeBenchmark(500, 10000, 500);
	benchmark.makeBenchmark(startSize, maxSize, stepSize);

	benchmark.setRunnableObject(new TestTreeAdapter(b));
	benchmark.setBenchmarkName("btree40");
	benchmark.makeBenchmark(500, 10000, 500);
	benchmark.makeBenchmark(startSize, maxSize, stepSize);

	benchmark.setRunnableObject(new TestTreeAdapter(vanEmdeBoas));
	benchmark.setBenchmarkName("vEBoas");
	benchmark.makeBenchmark(500, 10000, 500);
	benchmark.makeBenchmark(startSize, maxSize, stepSize);
}
