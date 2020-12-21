#include "OneDimensionalStaticIntArray.h"

OneDimensionalStaticIntArray::OneDimensionalStaticIntArray() {
	pIntArray = nullptr;
	arrSize = 0;
	randMax = 100;

	arrayIsSorted = false;
}

OneDimensionalStaticIntArray::~OneDimensionalStaticIntArray() {
	delete[] pIntArray;
}

///*************************************///
///               SORTING               ///
///*************************************///

void OneDimensionalStaticIntArray::performBubbleSort() {
	int buffer;

	for (int i = 0; i < arrSize; i++)
	{
		for (int y = 0; y < arrSize - 1 - i; y++)
		{
			if (pIntArray[y] > pIntArray[y + 1])
			{
				buffer = pIntArray[y];
				pIntArray[y] = pIntArray[y + 1];
				pIntArray[y + 1] = buffer;
			}
		}
	}
	arrayIsSorted = true;
}

void OneDimensionalStaticIntArray::performShakerSort() { 
	int buffer;
	bool sort_or_not = true;
	do {
		sort_or_not = true;
		for (int i = 0; i < arrSize - 1; i++) {
			if (pIntArray[i] > pIntArray[i + 1]) {

				buffer = pIntArray[i];
				pIntArray[i] = pIntArray[i + 1];
				pIntArray[i + 1] = buffer;

				sort_or_not = false;
			}
		}
		for (int i = arrSize - 1; i >= 1; i--) {
			if (pIntArray[i] < pIntArray[i - 1]) {

				buffer = pIntArray[i];
				pIntArray[i] = pIntArray[i - 1];
				pIntArray[i - 1] = buffer;

				sort_or_not = false;
			}
		}
	} while (sort_or_not == false);
	arrayIsSorted = true;
}

void OneDimensionalStaticIntArray::performCombSort(bool useOptimizedMethod)
{
	double factor = 1.2473309;
	double step_sort = static_cast<double>(arrSize - 1);
	int buffer;
	int iter = 0;
	while (step_sort >= 1)
	{
		iter++;
		for (int i = 0; i + step_sort < arrSize; i++)
		{
			if (pIntArray[i] > pIntArray[i + static_cast<int>(step_sort)])
			{
				buffer = pIntArray[i];
				pIntArray[i] = pIntArray[i + static_cast<int>(step_sort)];
				pIntArray[i + static_cast<int>(step_sort)] = buffer;
			}
		}
		step_sort /= factor;

		cout << "Iteration: " << iter << endl; //WARNING
		cout << "step_sort: " << static_cast<double>(step_sort) << endl; //WARNING
		this->coutArray(); //WARNING
		cout << endl; //WARNING
	}

	if (useOptimizedMethod) { 
		bool sort_or_not;
		int i = 0;
		do
		{
			sort_or_not = true;
			for (int y = 0; y < arrSize - 1 - i; y++)
			{
				if (pIntArray[y] > pIntArray[y + 1])
				{
					buffer = pIntArray[y];
					pIntArray[y] = pIntArray[y + 1];
					pIntArray[y + 1] = buffer;
					sort_or_not = false;
				}
			}
			i++;
		} while (sort_or_not == false);
	}
	else 
	{
		for (int i = 0; i < arrSize - 1; i++)
		{
			for (int j = 0; j < arrSize - i - 1; j++)
			{
				if (pIntArray[j] > pIntArray[j + 1])
				{
					buffer = pIntArray[j];
					pIntArray[j] = pIntArray[j + 1];
					pIntArray[j + 1] = buffer;
				}
			}
		}
	}
	arrayIsSorted = true;
}

void OneDimensionalStaticIntArray::performInsertSort()
{
	int buffer,
		i_previous;
	int iter = 0;
	for (int i = 1; i < arrSize; i++)
	{
		buffer = pIntArray[i];
		i_previous = i - 1;

		//cout << "PREV Iteration: " << i << endl; //WARNING
		//cout << "PREV buffer: " << buffer << endl; //WARNING
		//cout << "PREV i_previous: " << i_previous << endl; //WARNING
		//iter = 0;
		while (i_previous >= 0 && pIntArray[i_previous] > buffer)
		{
			//iter++;
			pIntArray[i_previous + 1] = pIntArray[i_previous];
			pIntArray[i_previous] = buffer;
			i_previous--;

			//cout << "INNNER Iteration: " << iter << endl; //WARNING
			//cout << "INNNER buffer: " << buffer << endl; //WARNING
			//cout << "INNNER i_previous: " << i_previous << endl; //WARNING
			//if (!(pIntArray[0] == 20 && pIntArray[1] == 44 && pIntArray[2] == 93 && pIntArray[3] == 31 && pIntArray[4] == 17 &&
			//	pIntArray[5] == 54 && pIntArray[6] == 55 && pIntArray[7] == 65 && pIntArray[8] == 77 && pIntArray[9] == 26))
			//{
			//	for (int t = 0; t < arrSize; t++)
			//	{
			//		cout << pIntArray[t] << ' ';
			//	} //WARNING
			//	cout << endl; //WARNING
			//}
		}
		cout << "Iteration: " << i << endl; //WARNING
		cout << "buffer: " << buffer << endl; //WARNING
		if (!(pIntArray[0] == 20 && pIntArray[1] == 44 && pIntArray[2] == 93 && pIntArray[3] == 31 && pIntArray[4] == 17 &&
			pIntArray[5] == 54 && pIntArray[6] == 55 && pIntArray[7] == 65 && pIntArray[8] == 77 && pIntArray[9] == 26))
		{
			for (int t = 0; t < arrSize; t++)
			{
				cout << pIntArray[t] << ' ';
			} //WARNING
			cout << endl; //WARNING
		}
		cout << endl; //WARNING
		cout << endl; //WARNING
	}
	arrayIsSorted = true;
}

///*************************************///
///              SEARCHING              ///
///*************************************///

int OneDimensionalStaticIntArray::searchMax() {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor(0);
		return 0;
	}

	if (!arrayIsSorted)
	{
		int max = -2147483648;
		for (int i = 0; i < arrSize; i++)
		{
			if (max < pIntArray[i])
				max = pIntArray[i];
		}
		return max;
	}
	return pIntArray[arrSize - 1];
}

int OneDimensionalStaticIntArray::searchMin() {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor();
		return 0;
	}
	if (!arrayIsSorted) {
		int min = 2147483647;
		for (int i = 0; i < arrSize; i++)
		{
			if (min > pIntArray[i])
				min = pIntArray[i];
		}
		return min;
	}
	return pIntArray[0];
}

void OneDimensionalStaticIntArray::performLinearSearchAndCoutTheResult(const int value) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created!" << endl;
		SetOutputColor();
		return;
	}

	int F_count = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (value == pIntArray[i]) {
			F_count++;
			cout << "Found: i = " << i << endl; //WARNING
		}
	}
	cout << "[Linear search] The number of elements found: " << F_count << endl; //WARNING
}

void OneDimensionalStaticIntArray::performBinSearchAndCoutTheResult(const int value) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created!" << endl;
		SetOutputColor(0);
		return;
	}

	if (!arrayIsSorted)
	{
		SetOutputColor(4);
		cout << "Error! The array is not sorted!" << endl;
		SetOutputColor();
		return;
	}

	int F_count = 0;
	int left(0), right(arrSize - 1), mid(arrSize / 2);
	int right_min1 = right - 1;
	//cout << "left = " << left << " \tmid = " << mid << " \tright = " << right << endl;
	do
	{
		
		if (left != right_min1) {
			if (pIntArray[mid] < value)
			{
				left = mid;
				mid = left + (right - left) / 2;
			}
			if (pIntArray[mid] > value)
			{
				right = mid;
				mid = left + (right - left) / 2;
				right_min1 = right - 1;
			}
		}
		else
			break;

		//cout << "left = " << left << " \tmid = " << mid << " \tright = " << right << endl;
		

		if (pIntArray[mid] == value) {
			for (int i = left; i <= right; i++)
			{
				if (pIntArray[i] == value)
				{
					cout << "Found: i = " << i << endl;
					F_count++;
				}
			}
			break;
		}
	} while (true);

	cout << "[Binary search] The number of elements found: " << F_count << endl;
	return;
}

double OneDimensionalStaticIntArray::computeAverageMinAndMax() {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor(0);
		return 0;
	}

	return static_cast<double>(searchMin() + searchMax()) / 2;

}

int OneDimensionalStaticIntArray::getNumIsLessThanInput(const int value) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor();
		return 0;
	}
	int counter = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (value > pIntArray[i])
			counter++;
	}
	return counter;
}

int OneDimensionalStaticIntArray::getNumIsGreaterThanInput(const int value) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor();
		return 0;
	}
	int counter = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (value < pIntArray[i])
			counter++;
	}
	return counter;
}

///*************************************///
///             INSTRUMENTS             ///
///*************************************///

void OneDimensionalStaticIntArray::create(const int arrSize) {
	delete[] pIntArray;
	pIntArray = new int[arrSize] { 0 };
	this->arrSize = arrSize;
}

int* OneDimensionalStaticIntArray::getArrayPointer() {
	return pIntArray;
}

int OneDimensionalStaticIntArray::getSize() {
	return arrSize;
}

bool OneDimensionalStaticIntArray::fillArrayRand(bool useSrandTimeSeed, long long seed) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created!" << endl;
		SetOutputColor();
		return false;
	}
	arrayIsSorted = false;

	if (useSrandTimeSeed)
		srand(time(NULL));
	else
		srand(seed);

	for (int i = 0; i < arrSize; i++)
		pIntArray[i] = rand() % randMax * (rand() % 2 == 0 ? 1 : -1);

	return true;
}

void OneDimensionalStaticIntArray::coutArray(bool useColorsForEvery10Elements) {
	for (int i = 0; i < this->arrSize; i++)
	{
		if (useColorsForEvery10Elements)
		{
			if ((i + 1) % 10 == 0)
			{
				SetOutputColor(2);
				cout << "[" << i << "] = " << pIntArray[i] << endl;
				SetOutputColor();
			}
			else
				cout << "[" << i << "] = " << pIntArray[i] << endl;
		}
		else
			cout << "[" << i << "] = " << pIntArray[i] << endl;
	}
}

bool OneDimensionalStaticIntArray::swapArrayElements(unsigned int firstIndex, unsigned int secondIndex) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created! Returned 0" << endl;
		SetOutputColor();
		return false;
	}
	if (firstIndex <= arrSize && secondIndex <= arrSize)
	{
		int buffer = pIntArray[firstIndex];
		pIntArray[firstIndex] = pIntArray[secondIndex];
		pIntArray[secondIndex] = buffer;
		return true;
	}
	else {
		SetOutputColor(4);
		cout << "Error! One of the indexes goes out of the array!" << endl;
		SetOutputColor();
		return false;
	}
}

void OneDimensionalStaticIntArray::SetOutputColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

///*************************************///
///                TESTS                ///
///*************************************///

void OneDimensionalStaticIntArray::testTimeSort(int typeSort, int testNumber, bool fillArrayWithRandNumbers, bool useSrandTimeSeed) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created!" << endl;
		SetOutputColor();
		return;
	}
	clock_t fullTime = 0;
	clock_t startTime, endTime;
	for (int i = 0; i < testNumber; i++)
	{
		if (fillArrayWithRandNumbers)
		{
			if (useSrandTimeSeed)
				fillArrayRand();
			else
				fillArrayRand(false, i);
		}

		switch (typeSort)
		{
		case 0:
			if (i == 0)
				cout << "Started for bubble sort" << endl;
			startTime = clock();
			performBubbleSort();
			endTime = clock();
			break;
		case 1:
			if (i == 0)
				cout << "Started for shaker sort" << endl;
			startTime = clock();
			performShakerSort();
			endTime = clock();
			break;
		case 2:
			if (i == 0)
				cout << "Started for comb sort" << endl;
			startTime = clock();
			performCombSort();
			endTime = clock();
			break;
		case 3:
			if (i == 0)
				cout << "Started for comb sort (optimized)" << endl;
			startTime = clock();
			performCombSort(1);
			endTime = clock();
			break;
		case 4:
			if (i == 0)
				cout << "Started for insert sort" << endl;
			startTime = clock();
			performInsertSort();
			endTime = clock();
			break;
		default:
			startTime = endTime = clock();
			cout << "Invalid sorting type!" << endl;
			break;
		}
		fullTime += endTime - startTime;
	}
	if (typeSort >= 0 && typeSort <= 4)
		cout << "Time: " << static_cast<float>(fullTime) / testNumber << " ms (" << static_cast<float>(fullTime) / testNumber / 1000 << " sec)" << endl;
}

void OneDimensionalStaticIntArray::testTimeSearch(int typeSearch, int testNumber, int value) {
	if (pIntArray == nullptr)
	{
		SetOutputColor(4);
		cout << "Attention! Error: array not created!" << endl;
		SetOutputColor();
		return;
	}
	clock_t fullTime = 0;
	clock_t startTime, endTime;
	for (int i = 0; i < testNumber; i++)
	{
		switch (typeSearch)
		{
		case 0:
			if (i == 0)
				cout << "Started for search min" << endl;
			startTime = clock();
			cout << "Minimum: " << searchMin() << endl;
			endTime = clock();
			break;
		case 1:
			if (i == 0)
				cout << "Started for search max" << endl;
			startTime = clock();
			cout << "Maximum: " << searchMax() << endl;
			endTime = clock();
			break;
		case 2:
			if (i == 0)
				cout << "Started for linear search" << endl;
			startTime = clock();
			performLinearSearchAndCoutTheResult(value);
			endTime = clock();
			break;
		case 3:
			if (i == 0)
				cout << "Started for binary search" << endl;
			startTime = clock();
			performBinSearchAndCoutTheResult(value);
			endTime = clock();
			break;

		default:
			startTime = endTime = clock();
			cout << "Invalid searching type!" << endl;
			break;
		}
		fullTime += endTime - startTime;
	}
	if (typeSearch >= 0 && typeSearch <= 3)
		cout << "Time: " << static_cast<float>(fullTime) / testNumber << " ms (" << static_cast<float>(fullTime) / testNumber / 1000 << " sec)" << endl;
}
