#include "benchmaker.h"

//#include "tests/matrixMultiplying/multiplicationTestLauncher.h"

#include "tests/binaryTree/treeTestLauncher.h"


int main()
{
	Benchmaker benchmark;

	// uncomment this to save data to file
	//benchmark.setLogginToFile(true);

	//matrixBenchmark(benchmark);

	treesBenchmark(benchmark);
}
