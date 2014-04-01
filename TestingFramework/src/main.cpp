#include "benchmaker.h"

#include "tests/matrixMultiplying/recursiveMultiplier.h"
#include "tests/matrixMultiplying/regularMultiplier.h"
#include "tests/matrixMultiplying/transposedMultiplier.h"

int main()
{
	Benchmaker benchmark;

	// uncomment this to save data to file
	//benchmark.setLogginToFile(true);

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
}
