#pragma once
#include <iostream>
#include <ctime>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

class AdvancedSquareMatrix
{
public:
	AdvancedSquareMatrix();
	~AdvancedSquareMatrix();


	void constructor_interface(int matrix_order);
	void cout_matrix();
	

	void comb_sort();

	//MATH MODE's:
	//0 - add
	//1 - subtract
	//2 - multiply
	//3 - divide
	void matrix_math(short math_mode, int value);

	//SWAP MODE's:
	//0 - rotate a quarter (clockwise)
	//1 - swap quarters (diagonally)
	//2 - swap quarters (horizontally)
	//3 - swap quarters (vertically)
	bool swap_quarters(short swap_mode);


	void fill_snail(int tail_length = 4, bool save_tail_effect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_post_previous = 4, short CLR_tail = 15);
	void fill_wave(int tail_length = 4, bool save_tail_effect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_post_previous = 4, short CLR_tail = 15);
	void fill_rand(int tail_length = 4, bool save_tail_effect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_post_previous = 4, short CLR_tail = 15);
	
	
	int** get_matrix();
	int get_matrix_order();
	void operator=(AdvancedSquareMatrix& source);

private:
	int** matrix;
	short** matrix_colors;

	int matrix_order;

	//CLR MEMORY
	//INDEX <MAX-3 - tail
	//INDEX =MAX-2 - post-previous
	//INDEX =MAX-1 - previous
	//INDEX =MAX   - current
	short CLRM_last_SIZE;
	short CLRM_last_total_count_erased;
	short* CLRM_last_ROW;
	short* CLRM_last_COL;
	short* CLRM_last_CLR;
	short* CLRM_last_CLR_before;

	void CLRM_constructor(int tail_length);
	bool CLRM_destructor();
	//STATUS:
	// 0 - add current (just changed)
	// >=1 - there is no current item, continue for previously entered items one step further  <- default
	void CLRM_manipulator(unsigned int coord_ROW = 0, unsigned int coord_COL = 0, unsigned short status = 1, bool save_tail_effect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_post_previous = 4, short CLR_tail = 15);


	void matrix_constructor();
	void matrix_colors_constructor(short default_color = 15);

	void matrix_value_reset(int default_value);
	void matrix_colors_reset(short default_color = 15);


	void swap_matrix_cells(int first_ROW, int first_COL, int second_ROW, int second_COL);
	void SetOutputColor(int text = 15, int bg = 0);
};