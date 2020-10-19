#pragma once
#include <iostream>
#include <ctime>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

#define DEBUG5

class AdvancedSquareMatrix
{
public:
	AdvancedSquareMatrix() {
		matrix = nullptr;
		matrix_colors = nullptr;

		CLRM_last_SIZE = 4;
		CLRM_last_total_count_erased = 0;
		CLRM_last_ROW = nullptr;
		CLRM_last_COL = nullptr;
		CLRM_last_CLR = nullptr;
		CLRM_last_CLR_before = nullptr;

		//WARNING
		matrix_second = nullptr;
		matrix_second_colors = nullptr;

		matrix_order = 0;
	};
	~AdvancedSquareMatrix() {
		//matrix destructor
		if (matrix != nullptr)
		{
			for (int i = 0; i < matrix_order; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}
		//matrix_colors destructor
		if (matrix_colors != nullptr)
		{
			for (int i = 0; i < matrix_order; i++)
			{
				delete[] matrix_colors[i];
			}
			delete[] matrix_colors;
		}

	};

	void matrix_constructor_interface(int matrix_order) {
		//matrix destructor
		if (matrix != nullptr)
		{
			for (int i = 0; i < this->matrix_order; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}

		//matrix_colors destructor
		if (matrix_colors != nullptr)
		{
			for (int i = 0; i < this->matrix_order; i++)
			{
				delete[] matrix_colors[i];
			}
			delete[] matrix_colors;
		}

		this->matrix_order = matrix_order;

		matrix_constructor();
		matrix_colors_constructor();
	};

	void cout_matrix() {
		
		/*for (size_t i = 0; i < matrix_order; i++)
		{
			matrix_color_manipulator(i, i, 2);
			matrix_color_manipulator(i, matrix_order - 1 - i, 1);
			matrix_color_manipulator(matrix_order/2, i, 4);
			matrix_color_manipulator(i, matrix_order / 2, 3);

			if (i > 1 && i < matrix_order - 2 && i != matrix_order / 2 - 1 && i != matrix_order / 2 + 1 && i != matrix_order / 2)
			{
				matrix_color_manipulator(0, i, 6);
				matrix_color_manipulator(matrix_order-1, i, 6);
				matrix_color_manipulator(i, 0, 6);
				matrix_color_manipulator(i, matrix_order - 1, 6);
			}

		}
		matrix_color_manipulator(matrix_order / 2, matrix_order / 2, 6);*/
		
		for (int i = 0; i < matrix_order; i++)
		{
			for (int y = 0; y < matrix_order; y++)
			{
				SetOutputColor(matrix_colors[i][y]);
				cout << matrix[i][y] << ' ';
				SetOutputColor();
			}
			cout << endl;
		}
	};

	void fill_matrix_snail() {
		system("cls");
		matrix_colors_reset_colors(0);
		for (int i = 0; i < matrix_order; i++)
		{
			for (int y = 0; y < matrix_order; y++)
			{
				matrix[i][y] = randomize();
				martix_color_memory_manipulator(i, y, 0, true);
				//system("cls");
				cout_matrix();
				Sleep(40);
				//system("pause");
				system("cls");
			}
		}
		for (int y = 0; y < CLRM_last_SIZE; y++)
		{
			martix_color_memory_manipulator(0, 0, 1, true);
			//system("cls");
			cout_matrix();
			Sleep(40);
			//system("pause");
			system("cls");
		}
	}

private:
	int** matrix;
	short** matrix_colors;

	int** matrix_second;
	short** matrix_second_colors;

	int matrix_order;

	//CLR MEMORY
	//INDEX 0 - post-previous
	//INDEX 1 - previous
	//INDEX 2 - current
	short CLRM_last_SIZE;
	short CLRM_last_total_count_erased;
	short* CLRM_last_ROW;
	short* CLRM_last_COL;
	short* CLRM_last_CLR;
	short* CLRM_last_CLR_before;

	int randomize(bool update_randomize_seed = false, bool use_srand_time_seed = true, long long seed = 0) {
		int rand_value = 0;
		if (update_randomize_seed)
		{
			if (use_srand_time_seed)
				srand(time(NULL));
			else
				srand(seed);
		}

		rand_value = rand() % 10;//(matrix_order * matrix_order);
		if (rand_value != 0)
			return rand_value;
		else
			return rand_value + 1;
	}

	void matrix_color_manipulator(unsigned int coord_Y, unsigned int coord_X, unsigned short c_text = 15) {
		matrix_colors[coord_Y][coord_X] = c_text;
	}


	//STATUS:
	// 0 - add current (just changed)
	// >=1 - there is no current item, continue for previously entered items one step further  <- default
	void martix_color_memory_manipulator(unsigned int coord_ROW = 0, unsigned int coord_COL = 0, unsigned short status = 1, bool save_tail_effect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_post_previous = 4, short CLR_tail = 15) {
		bool CLR_is_changed = false;
		if (CLRM_last_ROW == nullptr || CLRM_last_COL == nullptr || CLRM_last_CLR == nullptr || CLRM_last_CLR_before == nullptr)
		{
			CLRM_last_ROW = new short[CLRM_last_SIZE] {};
			CLRM_last_COL = new short[CLRM_last_SIZE] {};
			CLRM_last_CLR = new short[CLRM_last_SIZE] {};
			CLRM_last_CLR_before = new short[CLRM_last_SIZE] {};
			
			for (int i = 0; i < CLRM_last_SIZE; i++)
			{
				CLRM_last_CLR[i] = matrix_colors[0][0];
				CLRM_last_CLR_before[i] = matrix_colors[0][0];
			}
		}
		else
		{
			delete[]CLRM_last_ROW,
				CLRM_last_COL,
				CLRM_last_CLR,
				CLRM_last_CLR_before;
		}
		
		for (int i = 0; i < CLRM_last_SIZE; i++) {
			if(save_tail_effect && i == 0)
				matrix_colors[CLRM_last_ROW[i]][CLRM_last_COL[i]] = CLRM_last_CLR[i];
			else
				matrix_colors[CLRM_last_ROW[i]][CLRM_last_COL[i]] = CLRM_last_CLR_before[i];
		}

		switch (status)
		{
		case 0:
			for (int i = 0; i < CLRM_last_SIZE - 1; i++)
			{
				CLR_is_changed = false;

				CLRM_last_ROW[i] = CLRM_last_ROW[i + 1];
				CLRM_last_COL[i] = CLRM_last_COL[i + 1];
				CLRM_last_CLR[i] = CLRM_last_CLR[i + 1];
				CLRM_last_CLR_before[i] = CLRM_last_CLR_before[i + 1];

				/*switch (CLRM_last_CLR[i])
				{
				case 2:
					CLRM_last_CLR[i] = CLR_previous;
					break;
				case 6:
					CLRM_last_CLR[i] = CLR_post_previous;
					break;
				case 4:
					CLRM_last_CLR[i] = CLR_tail;
					break;
				case 12:

					break;
				default:
					CLRM_last_CLR[i] = CLRM_last_CLR_before[i];
					break;
				}*/

				if (CLRM_last_CLR[i] == CLR_current && !CLR_is_changed) {
					CLRM_last_CLR[i] = CLR_previous;
					CLR_is_changed = true;
				}

				if (CLRM_last_CLR[i] == CLR_previous && !CLR_is_changed) {
					CLRM_last_CLR[i] = CLR_post_previous;
					CLR_is_changed = true;
				}

				if (CLRM_last_CLR[i] == CLR_post_previous && !CLR_is_changed) {
					CLRM_last_CLR[i] = CLR_tail;
					CLR_is_changed = true;
				}

				matrix_colors[CLRM_last_ROW[i]][CLRM_last_COL[i]] = CLRM_last_CLR[i];
			}

			CLRM_last_ROW[CLRM_last_SIZE - 1] = coord_ROW;
			CLRM_last_COL[CLRM_last_SIZE - 1] = coord_COL;
			CLRM_last_CLR[CLRM_last_SIZE - 1] = CLR_current;
			CLRM_last_CLR_before[CLRM_last_SIZE - 1] = matrix_colors[coord_ROW][coord_COL];
			matrix_colors[CLRM_last_ROW[CLRM_last_SIZE - 1]][CLRM_last_COL[CLRM_last_SIZE - 1]] = CLR_current;
			break;

		default:
			for (int i = CLRM_last_SIZE - 1; i > 0; i--)
			{
				CLRM_last_CLR[i] = CLRM_last_CLR[i - 1];
				CLRM_last_CLR_before[i] = CLRM_last_CLR_before[i - 1];
				
				matrix_colors[CLRM_last_ROW[i]][CLRM_last_COL[i]] = CLRM_last_CLR[i];
			}
			
			CLRM_last_ROW[CLRM_last_total_count_erased] = 0;
			CLRM_last_COL[CLRM_last_total_count_erased] = 0;
			CLRM_last_CLR[CLRM_last_total_count_erased] = matrix_colors[0][0];
			CLRM_last_CLR_before[CLRM_last_total_count_erased] = matrix_colors[0][0];
			CLRM_last_total_count_erased++;

			if (CLRM_last_total_count_erased == CLRM_last_SIZE)
				CLRM_last_total_count_erased = 0;
			break;
		}
	}

	void matrix_constructor() {
		matrix = new int* [matrix_order];
		for (int i = 0; i < matrix_order; i++)
		{
			matrix[i] = new int[matrix_order] {};
		}

		//WARNING
		matrix_second = new int* [matrix_order];
		for (int i = 0; i < matrix_order; i++)
		{
			matrix_second[i] = new int[matrix_order] {};
		}
	};

	void matrix_colors_constructor(short default_color = 15) {
		matrix_colors = new short* [matrix_order];
		for (int i = 0; i < matrix_order; i++)
		{
			matrix_colors[i] = new short[matrix_order] {};
		}


		//WARNING
		matrix_second_colors = new short* [matrix_order];
		for (int i = 0; i < matrix_order; i++)
		{
			matrix_second_colors[i] = new short[matrix_order] {};
		}

		matrix_colors_reset_colors(default_color);
	}

	void matrix_colors_reset_colors(short default_color = 15) {
		for (int i = 0; i < matrix_order; i++)
		{
			for (int y = 0; y < matrix_order; y++)
			{
				matrix_colors[i][y] = default_color;
			}
		}

		//WARNING
		for (int i = 0; i < matrix_order; i++)
		{
			for (int y = 0; y < matrix_order; y++)
			{
				matrix_second_colors[i][y] = default_color;
			}
		}
	}


	void SetOutputColor(int text = 15, int bg = 0) {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
	}
};

/*
1)    Используя арифметику указателей, заполняет квадратичную целочисленную матрицу порядка N (6, 8, 10) случайными числами от 1 до  N * N согласно схемам приведенным на рисунках.
	  Пользователь должен видеть процесс заполнения квадратичной матрицы.

2)    Получает новую матрицу, из матрицы п. 1, переставляя ее блоки в соответствии со схемами :

3)    Используя арифметику указателей, сортирует элементы любой сортировкой.

4)    Уменьшает, увеличивает, умножает или делит все элементы матрицы на введенное пользователем число.
*/