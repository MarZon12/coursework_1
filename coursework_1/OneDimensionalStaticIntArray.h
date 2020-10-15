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
	
	void bubble_sort();									//236-241 ms 10000p i:552576315   76-81 ms 5000p i:26310526
	
	void shaker_sort();									//214-217 ms 10000p i:52576847    47-50 ms 5000p i:13222618
	
	void comb_sort(bool use_optimized_method = false);  //  1-2   ms 10000p i:379597       <=1  ms 5000p i:174812   (bool use_optimized_method = true)
														//115-117 ms 10000p i:50364598    29-32 ms 5000p i:12667313 (bool use_optimized_method = false)
	
	void insert_sort();									//83-90   ms 10000p i:496476083   20-26 ms 5000p i:124370287

	///*************************************///
	///              SEARCHING              ///
	///*************************************///

	int search_max();
	int search_min();
	void linear_search_and_cout(const int value);
	bool binary_search_and_cout(const int value);
	double average_min_and_max();
	int count_numbers_is_less_than_input(const int value);
	int count_numbers_is_greater_than_input(const int value);

	///*************************************///
	///             INSTRUMENTS             ///
	///*************************************///

	void swapArrayElements(unsigned int index_1, unsigned int index_2);
	void create(const int arrSIZE);
	void fill_array_rand(bool use_srand_time_seed = true, long long seed = 0);
	void cout_array(bool use_colors_for_every_10_elements = false);

	///*************************************///
	///                TESTS                ///
	///*************************************///

	// Types:
	// 0 - bubble sort
	// 1 - shaker sort
	// 2 - comb sort
	// 3 - comb sort (optimized)
	// 4 - insert sort
	void test_time_sort(int type_sort, int test_number = 1, bool fill_array_with_numbers = false, bool use_srand_time_seed = true);

	// Types:
	// 0 - search min
	// 1 - search max
	// 2 - linear search (needs value)
	// 3 - binary search (needs value)
	void test_time_search(int type_search, int test_number = 1, int value = 0);

private:
	int* int_array;
	int arrSIZE;
	int max_rand;

	bool array_is_sorted;

	void SetOutputColor(int text = 15, int bg = 0);
};