#include "OneDimensionalStaticIntArray.h"

OneDimensionalStaticIntArray::OneDimensionalStaticIntArray() {
	int_array = nullptr;
	arrSIZE = 0;
	max_rand = 100;

	array_is_sorted = false;
}

OneDimensionalStaticIntArray::~OneDimensionalStaticIntArray() {
	delete[] int_array;
}

///*************************************///
///               SORTING               ///
///*************************************///

void OneDimensionalStaticIntArray::bubble_sort() {
	int buffer;

	for (int i = 0; i < arrSIZE; i++)
	{
		for (int y = 0; y < arrSIZE - 1 - i; y++)
		{
			if (int_array[y] > int_array[y + 1])
			{
				buffer = int_array[y];
				int_array[y] = int_array[y + 1];
				int_array[y + 1] = buffer;
			}
		}
	}
	array_is_sorted = true;
}

void OneDimensionalStaticIntArray::shaker_sort() { 
	int buffer;
	bool sort_or_not = true;

	do {
		sort_or_not = true;
		for (int i = 0; i < arrSIZE - 1; i++) {
			if (int_array[i] > int_array[i + 1]) {

				buffer = int_array[i];
				int_array[i] = int_array[i + 1];
				int_array[i + 1] = buffer;

				sort_or_not = false;
			}
		}
		for (int i = arrSIZE - 1; i >= 1; i--) {
			if (int_array[i] < int_array[i - 1]) {

				buffer = int_array[i];
				int_array[i] = int_array[i - 1];
				int_array[i - 1] = buffer;

				sort_or_not = false;
			}
		}
	} while (sort_or_not == false);
	array_is_sorted = true;
}

void OneDimensionalStaticIntArray::comb_sort(bool use_optimized_method)
{
	double factor = 1.2473309;
	double step_sort = static_cast<double>(arrSIZE - 1);
	int buffer;

	while (step_sort >= 1)
	{
		for (int i = 0; i + step_sort < arrSIZE; i++)
		{
			if (int_array[i] > int_array[i + static_cast<int>(step_sort)])
			{
				buffer = int_array[i];
				int_array[i] = int_array[i + static_cast<int>(step_sort)];
				int_array[i + static_cast<int>(step_sort)] = buffer;
			}
		}
		step_sort /= factor;
	}

	if (use_optimized_method) { 
		bool sort_or_not;
		int i = 0;
		do
		{
			sort_or_not = true;
			for (int y = 0; y < arrSIZE - 1 - i; y++)
			{
				if (int_array[y] > int_array[y + 1])
				{
					buffer = int_array[y];
					int_array[y] = int_array[y + 1];
					int_array[y + 1] = buffer;
					sort_or_not = false;
				}
			}
			i++;
		} while (sort_or_not == false);
	}
	else 
	{
		for (int i = 0; i < arrSIZE - 1; i++)
		{
			for (int j = 0; j < arrSIZE - i - 1; j++)
			{
				if (int_array[j] > int_array[j + 1])
				{
					buffer = int_array[j];
					int_array[j] = int_array[j + 1];
					int_array[j + 1] = buffer;
				}
			}
		}
	}
	array_is_sorted = true;
}

void OneDimensionalStaticIntArray::insert_sort()
{
	int buffer,
		i_previous;

	for (int i = 1; i < arrSIZE; i++)
	{
		buffer = int_array[i];
		i_previous = i - 1;

		while (i_previous >= 0 && int_array[i_previous] > buffer)
		{
			int_array[i_previous + 1] = int_array[i_previous];
			int_array[i_previous] = buffer;
			i_previous--;
		}
	}
	array_is_sorted = true;
}

///*************************************///
///              SEARCHING              ///
///*************************************///

int OneDimensionalStaticIntArray::search_max() {
	if (!array_is_sorted)
	{
		int max = -2147483648;
		for (int i = 0; i < arrSIZE; i++)
		{
			if (max < int_array[i])
				max = int_array[i];
		}
		return max;
	}
	return int_array[arrSIZE - 1];
}

int OneDimensionalStaticIntArray::search_min() {
	if (!array_is_sorted) {
		int min = 2147483647;
		for (int i = 0; i < arrSIZE; i++)
		{
			if (min > int_array[i])
				min = int_array[i];
		}
		return min;
	}
	return int_array[0];
}

void OneDimensionalStaticIntArray::linear_search_and_cout(const int value) {
	int F_count = 0;
	for (int i = 0; i < arrSIZE; i++)
	{
		if (value == int_array[i]) {
			F_count++;
			cout << "Found: i = " << i << endl;
		}
	}
	cout << "[Linear search] The number of elements found: " << F_count << endl;
}

bool OneDimensionalStaticIntArray::binary_search_and_cout(const int value) {
	if (!array_is_sorted)
	{
		SetOutputColor(4);
		cout << "Error! The array is not sorted!" << endl;
		SetOutputColor();
		return false;
	}

	int F_count = 0;
	int left(0), right(arrSIZE - 1), mid(arrSIZE / 2);
	int right_min_1 = right - 1;
	//cout << "left = " << left << " \tmid = " << mid << " \tright = " << right << endl;
	do
	{
		
		if (left != right_min_1) {
			if (int_array[mid] < value)
			{
				left = mid;
				mid = left + (right - left) / 2;
			}
			if (int_array[mid] > value)
			{
				right = mid;
				mid = left + (right - left) / 2;
				right_min_1 = right - 1;
			}
		}
		else
			break;

		//cout << "left = " << left << " \tmid = " << mid << " \tright = " << right << endl;
		

		if (int_array[mid] == value) {
			for (int i = left; i <= right; i++)
			{
				if (int_array[i] == value)
				{
					cout << "Found: i = " << i << endl;
					F_count++;
				}
			}
			break;
		}
	} while (true);

	cout << "[Binary search] The number of elements found: " << F_count << endl;
	return true;
}

double OneDimensionalStaticIntArray::average_min_and_max() {
	return static_cast<double>(search_min() + search_max()) / 2;
}

int OneDimensionalStaticIntArray::count_numbers_is_less_than_input(const int value) {
	int counter = 0;
	for (int i = 0; i < arrSIZE; i++)
	{
		if (value > int_array[i])
			counter++;
	}
	return counter;
}

int OneDimensionalStaticIntArray::count_numbers_is_greater_than_input(const int value) {
	int counter = 0;
	for (int i = 0; i < arrSIZE; i++)
	{
		if (value < int_array[i])
			counter++;
	}
	return counter;
}

///*************************************///
///             INSTRUMENTS             ///
///*************************************///

void OneDimensionalStaticIntArray::create(const int arrSIZE) {
	delete[] int_array;
	int_array = new int[arrSIZE] { 0 };
	this->arrSIZE = arrSIZE;
}

void OneDimensionalStaticIntArray::fill_array_rand(bool use_srand_time_seed, long long seed) {
	array_is_sorted = false;
	if (use_srand_time_seed)
		srand(time(NULL));
	else
		srand(seed);
	for (int i = 0; i < arrSIZE; i++)
	{
		int_array[i] = rand() % max_rand * (rand() % 2 == 0 ? 1 : -1);
	}
}

void OneDimensionalStaticIntArray::cout_array(bool use_colors_for_every_10_elements) {
	for (int i = 0; i < this->arrSIZE; i++)
	{
		if (use_colors_for_every_10_elements)
		{
			if ((i + 1) % 10 == 0)
			{
				SetOutputColor(2);
				cout << "[" << i << "] = " << int_array[i] << endl;
				SetOutputColor();
			}
			else
				cout << "[" << i << "] = " << int_array[i] << endl;
		}
		else
			cout << "[" << i << "] = " << int_array[i] << endl;
	}
}

void OneDimensionalStaticIntArray::swapArrayElements(unsigned int index_1, unsigned int index_2) {
	if (index_1 <= arrSIZE && index_2 <= arrSIZE)
	{
		int buffer = int_array[index_1];
		int_array[index_1] = int_array[index_2];
		int_array[index_2] = buffer;
	}
	else {
		SetOutputColor(4);
		cout << "Error! One of the indexes goes out of the array!" << endl;
		SetOutputColor();
	}
}

void OneDimensionalStaticIntArray::SetOutputColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

///*************************************///
///                TESTS                ///
///*************************************///

void OneDimensionalStaticIntArray::test_time_sort(int type_sort, int test_number, bool fill_array_with_numbers, bool use_srand_time_seed) {
	clock_t full_time = 0;
	clock_t start, end;
	for (int i = 0; i < test_number; i++)
	{
		if (fill_array_with_numbers)
		{
			if (use_srand_time_seed)
				fill_array_rand();
			else
				fill_array_rand(false, i);
		}

		switch (type_sort)
		{
		case 0:
			if (i == 0)
				cout << "Started for bubble sort" << endl;
			start = clock();
			bubble_sort();
			end = clock();
			break;
		case 1:
			if (i == 0)
				cout << "Started for shaker sort" << endl;
			start = clock();
			shaker_sort();
			end = clock();
			break;
		case 2:
			if (i == 0)
				cout << "Started for comb sort" << endl;
			start = clock();
			comb_sort();
			end = clock();
			break;
		case 3:
			if (i == 0)
				cout << "Started for comb sort (optimized)" << endl;
			start = clock();
			comb_sort(1);
			end = clock();
			break;
		case 4:
			if (i == 0)
				cout << "Started for insert sort" << endl;
			start = clock();
			insert_sort();
			end = clock();
			break;
		default:
			start = end = clock();
			cout << "Invalid sorting type!" << endl;
			break;
		}
		full_time += end - start;
	}
	if (type_sort >= 0 && type_sort <= 4)
		cout << "Time: " << static_cast<float>(full_time) / test_number << " ms (" << static_cast<float>(full_time) / test_number / 1000 << " sec)" << endl;
}

void OneDimensionalStaticIntArray::test_time_search(int type_search, int test_number, int value) {
	clock_t full_time = 0;
	clock_t start, end;
	for (int i = 0; i < test_number; i++)
	{
		switch (type_search)
		{
		case 0:
			if (i == 0)
				cout << "Started for search min" << endl;
			start = clock();
			cout << "Minimum: " << search_min() << endl;
			end = clock();
			break;
		case 1:
			if (i == 0)
				cout << "Started for search max" << endl;
			start = clock();
			cout << "Maximum: " << search_max() << endl;
			end = clock();
			break;
		case 2:
			if (i == 0)
				cout << "Started for linear search" << endl;
			start = clock();
			linear_search_and_cout(value);
			end = clock();
			break;
		case 3:
			if (i == 0)
				cout << "Started for binary search" << endl;
			start = clock();
			binary_search_and_cout(value);
			end = clock();
			break;

		default:
			start = end = clock();
			cout << "Invalid searching type!" << endl;
			break;
		}
		full_time += end - start;
	}
	if (type_search >= 0 && type_search <= 3)
		cout << "Time: " << static_cast<float>(full_time) / test_number << " ms (" << static_cast<float>(full_time) / test_number / 1000 << " sec)" << endl;
}
