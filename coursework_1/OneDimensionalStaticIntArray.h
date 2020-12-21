#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;


class OneDimensionalStaticIntArray
{
public:
	OneDimensionalStaticIntArray();
	~OneDimensionalStaticIntArray();

	///*************************************///
	///               SORTING               ///
	///*************************************///
	
	void performBubbleSort();									//236-241 ms 10000p i:552576315   76-81 ms 5000p i:26310526
	
	void performShakerSort();									//214-217 ms 10000p i:52576847    47-50 ms 5000p i:13222618
	
	void performCombSort(bool useOptimizedMethod = false);    //  1-2   ms 10000p i:379597       <=1  ms 5000p i:174812   (bool useOptimizedMethod = true)
																//115-117 ms 10000p i:50364598    29-32 ms 5000p i:12667313 (bool useOptimizedMethod = false)
	
	void performInsertSort();									// 83-90  ms 10000p i:496476083   20-26 ms 5000p i:124370287

	///*************************************///
	///              SEARCHING              ///
	///*************************************///

	int searchMax();
	int searchMin();
	void performLinearSearchAndCoutTheResult(const int value);
	void performBinSearchAndCoutTheResult(const int value);
	double computeAverageMinAndMax();
	int getNumIsLessThanInput(const int value);
	int getNumIsGreaterThanInput(const int value);

	///*************************************///
	///             INSTRUMENTS             ///
	///*************************************///

	bool swapArrayElements(unsigned int firstIndex, unsigned int secondIndex);
	void create(const int arrSize);
	int* getArrayPointer();
	int getSize();
	bool fillArrayRand(bool useSrandTimeSeed = true, long long seed = 0);
	void coutArray(bool useColorsForEvery10Elements = false);

	int& operator[](int index) {
		return pIntArray[index];
	}

	///*************************************///
	///                TESTS                ///
	///*************************************///

	// Types:
	// 0 - bubble sort
	// 1 - shaker sort
	// 2 - comb sort
	// 3 - comb sort (optimized)
	// 4 - insert sort
	void testTimeSort(int typeSort, int testNumber = 1, bool fillArrayWithRandNumbers = false, bool useSrandTimeSeed = true);

	// Types:
	// 0 - search min
	// 1 - search max
	// 2 - linear search (needs value)
	// 3 - binary search (needs value)
	void testTimeSearch(int typeSearch, int testNumber = 1, int value = 0);

private:
	int* pIntArray;
	int arrSize;
	int randMax;

	bool arrayIsSorted;

	void SetOutputColor(int text = 15, int bg = 0);
};