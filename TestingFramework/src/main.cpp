#include "benchmaker.h"

int main()
{
	Benchmaker benchmark;

	// uncomment this to save data to file
	//benchmark.setLogginToFile(true);

	benchmark.setRoundsCount(5);
	// Regular multiplying
	benchmark.setRunnableObject(Regular);
	benchmark.makeBenchmark(100, 400, 100);  // (100, 1000, 50) looks interesting

	// recursive: onlt for 2^N matrix
	benchmark.setRunnableObject(Recursive);
	benchmark.makeBenchmark(128, 0, 0);
	benchmark.makeBenchmark(256, 0, 0);
	benchmark.makeBenchmark(512, 0, 0);

	// transposed
	benchmark.setRunnableObject(Transposed);
	benchmark.makeBenchmark(100, 400, 100);
}
