#include "benchmaker.h"

#include <climits>
#include <iostream>
#include <stdlib.h>
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

#include "tests/binaryTree/vanEmdeBoasTree.h"
#include "tests/binaryTree/splayTree.h"

void treesBenchmark(Benchmaker &benchmark)
{
	SplayTree tree;
	tree.insert(5);
	unsigned long long const start = 199999;
	unsigned long long const top = 200033;


	for (unsigned long long i = 0; i <= 10; i++)
	{
		tree.insert(i);
	}

	cout << "\nsearching:\n";
	for (unsigned long long i = 0; i <= 13; i++)
	{
		cout << (tree.lookup(i)? i : 777) << "\n";
	}
	for (unsigned long long i = start; i <= top + 10; i++)
	{
		cout << (tree.lookup(i)? i : 777) << "\n";
	}

	int i = 0;
	cin >> i;

	Q_UNUSED(benchmark);
}

int main()
{
	Benchmaker benchmark;

	// uncomment this to save data to file
	//benchmark.setLogginToFile(true);

	//matrixBenchmark(benchmark);
	treesBenchmark(benchmark);
	//cout << sizeof(unsigned short);
}
