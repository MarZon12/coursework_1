#pragma once
#include <windows.h>

#include <iostream>
#include <iomanip>

#include <ctime>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;

const int N = 10000; //WARNING

class OneDimensionalStaticArray
{
public:
	OneDimensionalStaticArray() { //WARNING
		fill_array_rand();
	}

	void cout_array() {
		for (int i = 0; i < N; i++)
		{
			cout << int_array[i] << endl;  //WARNING
		}
	}

	void bubble_sort() { //415 ms 10000p i:105252631   95-104 ms 5000p i:26310526
		int buffer;
		for (int i = 0; i < N; i++)
		{
			for (int y = 0; y < N - 1; y++)
			{
				if (int_array[y] > int_array[y + 1])
				{
					buffer = int_array[y];
					int_array[y] = int_array[y + 1];
					int_array[y + 1] = buffer;
				}
			}
		}
	}

	void NEWbubble_sort() { //411 ms 10000p i:103760149  92-95 ms 5000p i:25784052
		int buffer;
		bool sort_or_not;
		do
		{
			sort_or_not = true;
			for (int y = 0; y < N - 1; y++)
			{
				if (int_array[y] > int_array[y + 1])
				{
					buffer = int_array[y];
					int_array[y] = int_array[y + 1];
					int_array[y + 1] = buffer;
					sort_or_not = false;
				}
			}
		} while (sort_or_not == false);

	}

	void shaker_sort() {


	}

	//bool sort_or_not = true;

	//do {
	//	sort_or_not = true;
	//	for (int i = 0; i < n; i++) { // n - размер сортируемого массива
	//		if (chisla[i] > chisla[i + 1]) {
	//			swap(chisla[i], chisla[i + 1]);
	//			sort_or_not = false;
	//		}
	//	}
	//	for (int i = 4; i >= 1; i--) {
	//		if (chisla[i] < chisla[i - 1]) {
	//			swap(chisla[i], chisla[i - 1]);
	//			sort_or_not = false;
	//		}
	//	}
	//} while (sort_or_not == false);

	void test_time() {
		long long time = 0;
		long long iter = 0;
		for (int i = 0; i < 20; i++)
		{
			srand(i);
			fill_array_rand();
			clock_t start = clock();
			bubble_sort();
			clock_t end = clock();
			time += (end - start);
			iter += iterations;
		}
		cout.setf(std::ios_base::fixed);
		cout.precision(17);
		cout << "Clock: " << (time)/19 << endl;
		cout << "Iterations = " << iter/19 << endl;
	}

	void fill_array_rand() {
		//srand(time(0));
		for (int i = 0; i < N; i++)
		{
			int_array[i] = rand() % 100 * (rand() % 2 == 0 ? 1 : -1);
		}
	}

private:
	int int_array[N];
	long long iterations;
	

	void SetOutputColor(int text = 15, int bg = 0) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
	}
};

/*
Задание к практической работе №2 "ОДНОМЕРНЫЕ СТАТИЧЕСКИЕ МАССИВЫ"
Необходимо написать программу, которая:

1)    Создает целочисленный массив размерности N = 100. Элементы массивы должны принимать случайное значение в диапазоне от - 99 до 99.

2)    Отсортировать заданный в пункте 1 элементы массива[…] сортировкой.Определить время, затраченное на сортировку, используя библиотеку chrono.

3)    Найти максимальный и минимальный элемент массива.Подсчитайте время поиска этих элементов в отсортированном массиве и неотсортированном, используя библиотеку chrono.

4)    Выводит среднее значение(если необходимо, число нужно округлить) максимального и минимального значения.Выводит все числа, которые равны этому значению.

5)    Выводит количество элементов в отсортированном массиве, которые меньше числа a, которое инициализируется пользователем.

6)    Выводит количество элементов в отсортированном массиве, которые больше числа b, которое инициализируется пользователем.

7)    Выводит информацию о том, есть ли введенное пользователем число в отсортированном массиве.Реализуйте алгоритм бинарного поиска.Сравните скорость его работы с обычным перебором. (*)

8)     Меняет местами элементы массива, индексы которых вводит пользователь.Выведите скорость обмена, используя библиотеку chrono.


1 Bubble sort (пузырьковая сортировка)

2 Shaker sort (шейкер-сортировка)

3 Comb sort (сортировка расчёской)

4 Insert sort (сортировка вставками)

5 (*) Quick sort (быстрая сортировка)

*/