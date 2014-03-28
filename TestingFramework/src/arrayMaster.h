#pragma once

#include <iostream>

#include <stdlib.h>
#include <time.h>

using std::cout;
using std::endl;
using std::swap;

class ArrayMaster
{
public:
	static void clearArray(int *arr, int const length)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = 0;
		}
	}
	static void loadArrays(int *a, int *b, int const size)
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				a[i * size + j] = (rand() % 3) + 1;
				b[i * size + j] = (rand() % 3) + 1;
			}
	}

	static void showArray(int *arr, int const size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << arr[i * size + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	static void transpose(int *arr, int const size)
	{
		for (int i = 0; i < size; i++)
			for (int j = i; j < size; j++)
			{
				swap(arr[i * size + j], arr[j * size + i]);
			}
	}

	static void randomize()
	{
		srand (time(NULL));
	}

private:
	ArrayMaster();
};
