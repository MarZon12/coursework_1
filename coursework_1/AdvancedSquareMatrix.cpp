#include "AdvancedSquareMatrix.h"

AdvancedSquareMatrix::AdvancedSquareMatrix() {
	matrix = nullptr;
	matrix_colors = nullptr;
	matrix_order = 0;

	CLRM_last_SIZE = 4;
	CLRM_last_total_count_erased = 0;
	CLRM_last_ROW = nullptr;
	CLRM_last_COL = nullptr;
	CLRM_last_CLR = nullptr;
	CLRM_last_CLR_before = nullptr;
};
AdvancedSquareMatrix::~AdvancedSquareMatrix() {
	//matrix destructor
	if (matrix != nullptr)
	{
		for (int i = 0; i < matrix_order; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	//matrix_colors destructor
	if (matrix_colors != nullptr)
	{
		for (int i = 0; i < matrix_order; i++)
			delete[] matrix_colors[i];
		delete[] matrix_colors;
	}

	//CLRM destructor
	if (CLRM_last_ROW != nullptr)
		delete[] CLRM_last_ROW;

	if (CLRM_last_COL != nullptr)
		delete[] CLRM_last_COL;

	if (CLRM_last_CLR != nullptr)
		delete[] CLRM_last_CLR;

	if (CLRM_last_CLR_before != nullptr)
		delete[] CLRM_last_CLR_before;
};

//  +=====================================+
//  |               PUBLIC                |
//  +=====================================+

void AdvancedSquareMatrix::constructor_interface(int matrix_order) {
	//matrix destructor
	if (matrix != nullptr)
	{
		for (int i = 0; i < this->matrix_order; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	//matrix_colors destructor
	if (matrix_colors != nullptr)
	{
		for (int i = 0; i < this->matrix_order; i++)
			delete[] matrix_colors[i];
		delete[] matrix_colors;
	}

	this->matrix_order = matrix_order;

	matrix_constructor();
	matrix_colors_constructor();
};

void AdvancedSquareMatrix::cout_matrix() {

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

	for (int ROW = 0; ROW < matrix_order; ROW++)
	{
		for (int COL = 0; COL < matrix_order; COL++)
		{
			SetOutputColor(matrix_colors[ROW][COL]);
			cout << matrix[ROW][COL] << '\t';
			SetOutputColor();
		}
		cout << endl << endl << endl;
	}
};


void AdvancedSquareMatrix::comb_sort()
{
	double factor = 1.2473309;
	double step_sort = static_cast<double>(matrix_order * matrix_order - 1);

	while (step_sort >= 1)
	{
		for (int i = 0; i + step_sort < matrix_order * matrix_order; i++)
		{
			if (matrix[i / matrix_order][i % matrix_order] > matrix[(i + static_cast<int>(step_sort)) / matrix_order][(i + static_cast<int>(step_sort)) % matrix_order])
				swap_matrix_cells(i / matrix_order, i % matrix_order, (i + static_cast<int>(step_sort)) / matrix_order, (i + static_cast<int>(step_sort)) % matrix_order);
		}
		step_sort /= factor;
	}

	bool sort_or_not;
	int i = 0;
	do
	{
		sort_or_not = true;
		for (int y = 0; y < matrix_order * matrix_order - 1 - i; y++)
		{
			if (matrix[y / matrix_order][y % matrix_order] > matrix[(y + static_cast<int>(step_sort)) / matrix_order][(y + static_cast<int>(step_sort)) % matrix_order])
			{
				swap_matrix_cells(y / matrix_order, y % matrix_order, (y + static_cast<int>(step_sort)) / matrix_order, (y + static_cast<int>(step_sort)) % matrix_order);
				sort_or_not = false;
			}
		}
		i++;
	} while (sort_or_not == false);
}

void AdvancedSquareMatrix::matrix_math(short math_mode, int value) {
	for (int ROW = 0; ROW < matrix_order; ROW++)
	{
		for (int COL = 0; COL < matrix_order; COL++)
		{
			switch (math_mode)
			{
			case 0:
				matrix[ROW][COL] += value;
				break;
			case 1:
				matrix[ROW][COL] -= value;
				break;
			case 2:
				matrix[ROW][COL] *= value;
				break;
			case 3:
				matrix[ROW][COL] /= value;
				break;
			default:
				break;
			}
		}
	}
}

bool AdvancedSquareMatrix::swap_quarters(short swap_mode) {
	if (matrix_order % 2 != 0)
	{
		cout << endl << endl
			<< "\t+====================================================================+" << endl
			<< "\t|Attention! The order of the matrix is odd! Swapping is not possible.|" << endl
			<< "\t+====================================================================+" << endl << endl;
		return false;
	}

	int middle = matrix_order / 2;

	switch (swap_mode)
	{
	case 0:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
			{
				swap_matrix_cells(ROW, COL, ROW, middle + COL);

				swap_matrix_cells(ROW, COL, middle + ROW, middle + COL);

				swap_matrix_cells(ROW, COL, middle + ROW, COL);
			}
		}
		break;

	case 1:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swap_matrix_cells(ROW, COL, middle + ROW, middle + COL);
		}

		for (int ROW = middle; ROW < matrix_order; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swap_matrix_cells(ROW, COL, ROW - middle, COL + middle);
		}
		break;

	case 2:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < matrix_order; COL++)
				swap_matrix_cells(ROW, COL, middle + ROW, COL);
		}
		break;

	case 3:
		for (int ROW = 0; ROW < matrix_order; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swap_matrix_cells(ROW, COL, ROW, middle + COL);
		}
		break;

	default:
		cout << endl << endl
			<< "\t+==================================================================+" << endl
			<< "\t|         Attention! The entered swap mode does not exist.         |" << endl
			<< "\t+==================================================================+" << endl << endl;
		return false;
		break;
	}

	return true;
}


///*************************************///
///                FILL                 ///
///*************************************///

void AdvancedSquareMatrix::fill_snail(int tail_length, bool save_tail_effect, short CLR_current, short CLR_previous, short CLR_post_previous, short CLR_tail) {
	int offset_x = 0;
	int offset_y = 0;
	bool is_end = false;

	system("cls");

	matrix_colors_reset(0);
	matrix_value_reset(0);

	srand(time(NULL));

	CLRM_constructor(tail_length);

	while (true)
	{
		is_end = true;
		for (int COL = offset_x; COL < matrix_order - offset_x; COL++)
		{
			matrix[offset_x][COL] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(offset_x, COL, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
			is_end = false;
		}
		offset_y++;

		for (int ROW = offset_y; ROW < matrix_order - offset_y + 1; ROW++)
		{
			matrix[ROW][matrix_order - offset_y] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(ROW, matrix_order - offset_y, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
			is_end = false;
		}
		offset_x++;


		for (int COL = matrix_order - offset_x - 1; COL > offset_x - 2; COL--)
		{
			matrix[matrix_order - offset_x][COL] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(matrix_order - offset_x, COL, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
			is_end = false;
		}

		for (int ROW = matrix_order - offset_y - 1; ROW > offset_y - 1; ROW--)
		{
			matrix[ROW][offset_y - 1] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(ROW, offset_y - 1, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
			is_end = false;
		}

		if (is_end)
			break;
	}

	for (int y = 0; y < CLRM_last_SIZE; y++)
	{
		CLRM_manipulator(0, 0, 1, save_tail_effect);
		cout_matrix();
		Sleep(30);
		//system("pause");
		if (y != CLRM_last_SIZE - 1)
			system("cls");
	}
}

void AdvancedSquareMatrix::fill_wave(int tail_length, bool save_tail_effect, short CLR_current, short CLR_previous, short CLR_post_previous, short CLR_tail) {
	int offset_x = 0;

	system("cls");

	matrix_colors_reset(0);
	matrix_value_reset(0);

	srand(time(NULL));

	CLRM_constructor(tail_length);

	while (true)
	{
		for (int ROW = 0; ROW < matrix_order; ROW++)
		{
			matrix[ROW][offset_x] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(ROW, offset_x, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
		}
		offset_x++;

		if (offset_x >= matrix_order)
		{
			break;
		}

		for (int ROW = matrix_order - 1; ROW >= 0; ROW--)
		{
			matrix[ROW][offset_x] = rand() % (matrix_order * matrix_order) + 1;
			CLRM_manipulator(ROW, offset_x, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
			cout_matrix();
			Sleep(30);
			//system("pause");
			system("cls");
		}
		offset_x++;

		if (offset_x >= matrix_order)
		{
			break;
		}
	}

	for (int i = 0; i < CLRM_last_SIZE; i++)
	{
		CLRM_manipulator(0, 0, 1, save_tail_effect);
		cout_matrix();
		Sleep(30);
		//system("pause");
		if (i != CLRM_last_SIZE - 1)
			system("cls");
	}
}

void AdvancedSquareMatrix::fill_rand(int tail_length, bool save_tail_effect, short CLR_current, short CLR_previous, short CLR_post_previous, short CLR_tail) {
	int rand_1(0), rand_2(0);
	bool is_true = true;

	system("cls");

	matrix_colors_reset(0);
	matrix_value_reset(0);

	srand(time(NULL));

	CLRM_constructor(tail_length);

	//srand(time(NULL));

	while (true)
	{
		is_true = false;
		rand_1 = rand() % matrix_order;
		rand_2 = rand() % matrix_order;

		while (true)
		{
			if (matrix[rand_1][rand_2] == 0)
			{
				matrix[rand_1][rand_2] = rand() % (matrix_order * matrix_order) + 1;
				break;
			}
			else {
				rand_1 = rand() % matrix_order;
				rand_2 = rand() % matrix_order;
			}
		}
		CLRM_manipulator(rand_1, rand_2, 0, save_tail_effect, CLR_current, CLR_previous, CLR_post_previous, CLR_tail);
		cout_matrix();
		Sleep(30);
		system("cls");
		for (int ROW = 0; ROW < matrix_order; ROW++)
		{
			for (int COL = 0; COL < matrix_order; COL++)
			{
				if (matrix[ROW][COL] == 0)
					is_true = true;
			}
		}

		if (is_true == false)
		{
			break;
		}

	}

	for (int i = 0; i < CLRM_last_SIZE; i++)
	{
		CLRM_manipulator(0, 0, 1, save_tail_effect);
		cout_matrix();
		Sleep(30);
		//system("pause");
		if (i != CLRM_last_SIZE - 1)
			system("cls");
	}

}


///*************************************///
///             INSTRUMENTS             ///
///*************************************///

int** AdvancedSquareMatrix::get_matrix() {
	return matrix;
}

int AdvancedSquareMatrix::get_matrix_order() {
	return matrix_order;
}

void AdvancedSquareMatrix::operator=(AdvancedSquareMatrix& source) {
	int** source_matrix = source.get_matrix();
	constructor_interface(source.get_matrix_order());

	for (int ROW = 0; ROW < matrix_order; ROW++)
	{
		for (int COL = 0; COL < matrix_order; COL++)
		{
			this->matrix[ROW][COL] = source_matrix[ROW][COL];
		}
	}
}

//  +=====================================+
//  |               PRIVATE               |
//  +=====================================+

///*************************************///
///          CLRM [ColorMemory]         ///
///*************************************///

void AdvancedSquareMatrix::CLRM_constructor(int tail_length) {
	if (CLRM_last_COL != nullptr)
		CLRM_destructor();

	CLRM_last_SIZE = tail_length;

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

bool AdvancedSquareMatrix::CLRM_destructor() {
	if (CLRM_last_ROW == nullptr)
		return false;

	CLRM_last_SIZE = 4;

	delete[] CLRM_last_ROW;
	delete[] CLRM_last_COL;
	delete[] CLRM_last_CLR;
	delete[] CLRM_last_CLR_before;

	CLRM_last_ROW = nullptr;
	CLRM_last_COL = nullptr;
	CLRM_last_CLR = nullptr;
	CLRM_last_CLR_before = nullptr;

	return true;
}

void AdvancedSquareMatrix::CLRM_manipulator(unsigned int coord_ROW, unsigned int coord_COL, unsigned short status, bool save_tail_effect, short CLR_current, short CLR_previous, short CLR_post_previous, short CLR_tail) {
	bool CLR_is_changed = false;

	for (int i = 0; i < CLRM_last_SIZE; i++) {
		if (save_tail_effect && i == 0)
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


///*************************************///
///             INSTRUMENTS             ///
///*************************************///

void AdvancedSquareMatrix::matrix_constructor() {
	matrix = new int* [matrix_order];

	for (int i = 0; i < matrix_order; i++)
		matrix[i] = new int[matrix_order] {};
};
void AdvancedSquareMatrix::matrix_colors_constructor(short default_color) {
	matrix_colors = new short* [matrix_order];
	
	for (int i = 0; i < matrix_order; i++)
		matrix_colors[i] = new short[matrix_order];

	matrix_colors_reset(default_color);
}

void AdvancedSquareMatrix::matrix_value_reset(int default_value) {
	for (int ROW = 0; ROW < matrix_order; ROW++)
	{
		for (int COL = 0; COL < matrix_order; COL++)
			matrix[ROW][COL] = default_value;
	}
}
void AdvancedSquareMatrix::matrix_colors_reset(short default_color) {
	for (int ROW = 0; ROW < matrix_order; ROW++)
	{
		for (int COL = 0; COL < matrix_order; COL++)
			matrix_colors[ROW][COL] = default_color;
	}
}


void AdvancedSquareMatrix::swap_matrix_cells(int first_ROW, int first_COL, int second_ROW, int second_COL) {
	int buffer = matrix[first_ROW][first_COL];
	matrix[first_ROW][first_COL] = matrix[second_ROW][second_COL];
	matrix[second_ROW][second_COL] = buffer;
}

void AdvancedSquareMatrix::SetOutputColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
