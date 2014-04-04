#include "benchmaker.h"

#include <climits>
#include <iostream>

using namespace std;

/*#include "tests/matrixMultiplying/recursiveMultiplier.h"
#include "tests/matrixMultiplying/regularMultiplier.h"
#include "tests/matrixMultiplying/transposedMultiplier.h"

void matrixBenchmark(Benchmaker &benchmark)
{
	benchmark.setRoundsCount(5);
	// Regular multiplying
	benchmark.setRunnableObject(new RegularMultiplier);
	benchmark.makeBenchmark(100, 400, 100);  // (100, 1000, 50) looks interesting

	// recursive: onlt for 2^N matrix
	benchmark.setRunnableObject(new RecursiveMultiplier);
	benchmark.makeBenchmark(128, 0, 0);
	benchmark.makeBenchmark(256, 0, 0);
	benchmark.makeBenchmark(512, 0, 0);

	// transposed
	benchmark.setRunnableObject(new TransposedMultiplier);
	benchmark.makeBenchmark(100, 400, 100);
}*/

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
	treePretests();
	benchmark.setRunnableObject(new TestTreeAdapter(splay));
	benchmark.makeBenchmark(100, 1000, 50);
	benchmark.makeBenchmark(1000, 300000, 1000);

	benchmark.setRunnableObject(new TestTreeAdapter(b));
	benchmark.makeBenchmark(100, 1000, 50);
	benchmark.makeBenchmark(1000, 300000, 1000);

	benchmark.setRunnableObject(new TestTreeAdapter(vanEmdeBoas));
	benchmark.makeBenchmark(100, 1000, 50);
	benchmark.makeBenchmark(1000, 300000, 1000);
}

int main()
{
	Benchmaker benchmark;

	// uncomment this to save data to file
	benchmark.setLogginToFile(true);

	//matrixBenchmark(benchmark);

	treesBenchmark(benchmark);
}
