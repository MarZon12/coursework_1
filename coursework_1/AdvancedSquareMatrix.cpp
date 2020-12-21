#include "AdvancedSquareMatrix.h"

AdvancedSquareMatrix::AdvancedSquareMatrix() {
	pMatrix = nullptr;
	pMatrixColors = nullptr;
	matrixOrder = 0;

	CLRM_bufferSize = 4;
	CLRM_bufferTotalCountErased = 0;
	pCLRM_bufferRow = nullptr;
	pCLRM_bufferCol = nullptr;
	pCLRM_bufferCLR = nullptr;
	pCLRM_bufferCLR_before = nullptr;
};
AdvancedSquareMatrix::~AdvancedSquareMatrix() {
	//pMatrix destructor
	if (pMatrix != nullptr)
	{
		for (int i = 0; i < matrixOrder; i++)
			delete[] pMatrix[i];
		delete[] pMatrix;
	}

	//pMatrixColors destructor
	if (pMatrixColors != nullptr)
	{
		for (int i = 0; i < matrixOrder; i++)
			delete[] pMatrixColors[i];
		delete[] pMatrixColors;
	}

	//CLRM destructor
	if (pCLRM_bufferRow != nullptr)
		delete[] pCLRM_bufferRow;

	if (pCLRM_bufferCol != nullptr)
		delete[] pCLRM_bufferCol;

	if (pCLRM_bufferCLR != nullptr)
		delete[] pCLRM_bufferCLR;

	if (pCLRM_bufferCLR_before != nullptr)
		delete[] pCLRM_bufferCLR_before;
};

//  +=====================================+
//  |               PUBLIC                |
//  +=====================================+

void AdvancedSquareMatrix::create(int matrixOrder) {
	//pMatrix destructor
	if (pMatrix != nullptr)
	{
		for (int i = 0; i < this->matrixOrder; i++)
			delete[] pMatrix[i];
		delete[] pMatrix;
	}

	//pMatrixColors destructor
	if (pMatrixColors != nullptr)
	{
		for (int i = 0; i < this->matrixOrder; i++)
			delete[] pMatrixColors[i];
		delete[] pMatrixColors;
	}

	this->matrixOrder = matrixOrder;

	matrixConstructor();
	matrixColorsConstructor();
};

void AdvancedSquareMatrix::coutMatrix() {
	for (int ROW = 0; ROW < matrixOrder; ROW++)
	{
		for (int COL = 0; COL < matrixOrder; COL++)
		{
			SetOutputColor(pMatrixColors[ROW][COL]);
			cout << pMatrix[ROW][COL] << '\t';
			SetOutputColor();
		}
		cout << endl << endl << endl;
	}
};


void AdvancedSquareMatrix::performCombSort()
{
	double factor = 1.2473309;
	double step_sort = static_cast<double>(matrixOrder * matrixOrder - 1);

	while (step_sort >= 1)
	{
		for (int i = 0; i + step_sort < matrixOrder * matrixOrder; i++)
		{
			if (pMatrix[i / matrixOrder][i % matrixOrder] > pMatrix[(i + static_cast<int>(step_sort)) / matrixOrder][(i + static_cast<int>(step_sort)) % matrixOrder])
				swapMatrixCells(i / matrixOrder, i % matrixOrder, (i + static_cast<int>(step_sort)) / matrixOrder, (i + static_cast<int>(step_sort)) % matrixOrder);
		}
		step_sort /= factor;
	}

	bool sort_or_not;
	int i = 0;
	do
	{
		sort_or_not = true;
		for (int y = 0; y < matrixOrder * matrixOrder - 1 - i; y++)
		{
			if (pMatrix[y / matrixOrder][y % matrixOrder] > pMatrix[(y + static_cast<int>(step_sort)) / matrixOrder][(y + static_cast<int>(step_sort)) % matrixOrder])
			{
				swapMatrixCells(y / matrixOrder, y % matrixOrder, (y + static_cast<int>(step_sort)) / matrixOrder, (y + static_cast<int>(step_sort)) % matrixOrder);
				sort_or_not = false;
			}
		}
		i++;
	} while (sort_or_not == false);
}

void AdvancedSquareMatrix::matrixMath(short mathMode, int value) {
	for (int ROW = 0; ROW < matrixOrder; ROW++)
	{
		for (int COL = 0; COL < matrixOrder; COL++)
		{
			switch (mathMode)
			{
			case 0:
				pMatrix[ROW][COL] += value;
				break;
			case 1:
				pMatrix[ROW][COL] -= value;
				break;
			case 2:
				pMatrix[ROW][COL] *= value;
				break;
			case 3:
				pMatrix[ROW][COL] /= value;
				break;
			default:
				break;
			}
		}
	}
}

bool AdvancedSquareMatrix::swapQuarters(short swapMode) {
	if (matrixOrder % 2 != 0)
	{
		cout << endl << endl
			<< "\t+=====================================================================+\n"
			<< "\t|Attention! The order of the pMatrix is odd! Swapping is not possible.|\n"
			<< "\t+=====================================================================+\n" << endl;
		return false;
	}

	int middle = matrixOrder / 2;

	switch (swapMode)
	{
	case 0:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
			{
				swapMatrixCells(ROW, COL, ROW, middle + COL);

				swapMatrixCells(ROW, COL, middle + ROW, middle + COL);

				swapMatrixCells(ROW, COL, middle + ROW, COL);
			}
		}
		break;

	case 1:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swapMatrixCells(ROW, COL, middle + ROW, middle + COL);
		}

		for (int ROW = middle; ROW < matrixOrder; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swapMatrixCells(ROW, COL, ROW - middle, COL + middle);
		}
		break;

	case 2:
		for (int ROW = 0; ROW < middle; ROW++)
		{
			for (int COL = 0; COL < matrixOrder; COL++)
				swapMatrixCells(ROW, COL, middle + ROW, COL);
		}
		break;

	case 3:
		for (int ROW = 0; ROW < matrixOrder; ROW++)
		{
			for (int COL = 0; COL < middle; COL++)
				swapMatrixCells(ROW, COL, ROW, middle + COL);
		}
		break;

	default:
		cout << endl << endl
			<< "\t+==================================================================+\n"
			<< "\t|         Attention! The entered swap mode does not exist.         |\n"
			<< "\t+==================================================================+\n" << endl;
		return false;
		break;
	}

	return true;
}


///*************************************///
///                FILL                 ///
///*************************************///

void AdvancedSquareMatrix::fillSnail(int tailLength, bool saveTailEffect, short CLR_current, short CLR_previous, short CLR_postPrevious, short CLR_tail) {
	int offsetX = 0;
	int offsetY = 0;
	bool isEnd = false;

	system("cls");

	resetMatrixColors(0);
	resetMatrixValue(0);

	srand(time(NULL));

	CLRM_constructor(tailLength);

	while (true)
	{
		isEnd = true;
		for (int COL = offsetX; COL < matrixOrder - offsetX; COL++)
		{
			pMatrix[offsetX][COL] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(offsetX, COL, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
			isEnd = false;
		}
		offsetY++;

		for (int ROW = offsetY; ROW < matrixOrder - offsetY + 1; ROW++)
		{
			pMatrix[ROW][matrixOrder - offsetY] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(ROW, matrixOrder - offsetY, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
			isEnd = false;
		}
		offsetX++;


		for (int COL = matrixOrder - offsetX - 1; COL > offsetX - 2; COL--)
		{
			pMatrix[matrixOrder - offsetX][COL] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(matrixOrder - offsetX, COL, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
			isEnd = false;
		}

		for (int ROW = matrixOrder - offsetY - 1; ROW > offsetY - 1; ROW--)
		{
			pMatrix[ROW][offsetY - 1] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(ROW, offsetY - 1, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
			isEnd = false;
		}

		if (isEnd)
			break;
	}

	for (int y = 0; y < CLRM_bufferSize; y++)
	{
		CLRM_manipulator(0, 0, 1, saveTailEffect);
		coutMatrix();
		Sleep(30);
		//system("pause");
		if (y != CLRM_bufferSize - 1)
			system("cls");
	}
}

void AdvancedSquareMatrix::fillWave(int tailLength, bool saveTailEffect, short CLR_current, short CLR_previous, short CLR_postPrevious, short CLR_tail) {
	int offsetX = 0;

	system("cls");

	resetMatrixColors(0);
	resetMatrixValue(0);

	srand(time(NULL));

	CLRM_constructor(tailLength);

	while (true)
	{
		for (int ROW = 0; ROW < matrixOrder; ROW++)
		{
			pMatrix[ROW][offsetX] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(ROW, offsetX, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
		}
		offsetX++;

		if (offsetX >= matrixOrder)
		{
			break;
		}

		for (int ROW = matrixOrder - 1; ROW >= 0; ROW--)
		{
			pMatrix[ROW][offsetX] = rand() % (matrixOrder * matrixOrder) + 1;
			CLRM_manipulator(ROW, offsetX, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
			coutMatrix();
			Sleep(30);
			//system("pause");
			system("cls");
		}
		offsetX++;

		if (offsetX >= matrixOrder)
		{
			break;
		}
	}

	for (int i = 0; i < CLRM_bufferSize; i++)
	{
		CLRM_manipulator(0, 0, 1, saveTailEffect);
		coutMatrix();
		Sleep(30);
		//system("pause");
		if (i != CLRM_bufferSize - 1)
			system("cls");
	}
}

void AdvancedSquareMatrix::fillRand(int tailLength, bool saveTailEffect, short CLR_current, short CLR_previous, short CLR_postPrevious, short CLR_tail) {
	int rand_1(0), rand_2(0);
	bool isTrue = true;

	system("cls");

	resetMatrixColors(0);
	resetMatrixValue(0);

	srand(time(NULL));

	CLRM_constructor(tailLength);

	while (true)
	{
		isTrue = false;
		rand_1 = rand() % matrixOrder;
		rand_2 = rand() % matrixOrder;

		while (true)
		{
			if (pMatrix[rand_1][rand_2] == 0)
			{
				pMatrix[rand_1][rand_2] = rand() % (matrixOrder * matrixOrder) + 1;
				break;
			}
			else {
				rand_1 = rand() % matrixOrder;
				rand_2 = rand() % matrixOrder;
			}
		}
		CLRM_manipulator(rand_1, rand_2, 0, saveTailEffect, CLR_current, CLR_previous, CLR_postPrevious, CLR_tail);
		coutMatrix();
		Sleep(30);
		system("cls");
		for (int ROW = 0; ROW < matrixOrder; ROW++)
		{
			for (int COL = 0; COL < matrixOrder; COL++)
			{
				if (pMatrix[ROW][COL] == 0)
					isTrue = true;
			}
		}

		if (isTrue == false)
		{
			break;
		}

	}

	for (int i = 0; i < CLRM_bufferSize; i++)
	{
		CLRM_manipulator(0, 0, 1, saveTailEffect);
		coutMatrix();
		Sleep(30);
		//system("pause");
		if (i != CLRM_bufferSize - 1)
			system("cls");
	}

}


///*************************************///
///             INSTRUMENTS             ///
///*************************************///

int** AdvancedSquareMatrix::getMatrixPointer() {
	return pMatrix;
}

int AdvancedSquareMatrix::getMatrixOrder() {
	return matrixOrder;
}

void AdvancedSquareMatrix::operator=(AdvancedSquareMatrix& source) {
	int** sourceMatrix = source.getMatrixPointer();
	create(source.getMatrixOrder());

	for (int ROW = 0; ROW < matrixOrder; ROW++)
	{
		for (int COL = 0; COL < matrixOrder; COL++)
		{
			this->pMatrix[ROW][COL] = sourceMatrix[ROW][COL];
		}
	}
}

//  +=====================================+
//  |               PRIVATE               |
//  +=====================================+

///*************************************///
///          CLRM [ColorMemory]         ///
///*************************************///

void AdvancedSquareMatrix::CLRM_constructor(int tailLength) {
	if (pCLRM_bufferCol != nullptr)
		CLRM_destructor();

	CLRM_bufferSize = tailLength;

	pCLRM_bufferRow = new short[CLRM_bufferSize] {};
	pCLRM_bufferCol = new short[CLRM_bufferSize] {};
	pCLRM_bufferCLR = new short[CLRM_bufferSize] {};
	pCLRM_bufferCLR_before = new short[CLRM_bufferSize] {};

	for (int i = 0; i < CLRM_bufferSize; i++)
	{
		pCLRM_bufferCLR[i] = pMatrixColors[0][0];
		pCLRM_bufferCLR_before[i] = pMatrixColors[0][0];
	}
}

bool AdvancedSquareMatrix::CLRM_destructor() {
	if (pCLRM_bufferRow == nullptr)
		return false;

	CLRM_bufferSize = 4;

	delete[] pCLRM_bufferRow;
	delete[] pCLRM_bufferCol;
	delete[] pCLRM_bufferCLR;
	delete[] pCLRM_bufferCLR_before;

	pCLRM_bufferRow = nullptr;
	pCLRM_bufferCol = nullptr;
	pCLRM_bufferCLR = nullptr;
	pCLRM_bufferCLR_before = nullptr;

	return true;
}

void AdvancedSquareMatrix::CLRM_manipulator(unsigned int coordRow, unsigned int coordCol, unsigned short status, bool saveTailEffect, short CLR_current, short CLR_previous, short CLR_postPrevious, short CLR_tail) {
	bool CLR_isChanged = false;

	for (int i = 0; i < CLRM_bufferSize; i++) {
		if (saveTailEffect && i == 0)
			pMatrixColors[pCLRM_bufferRow[i]][pCLRM_bufferCol[i]] = pCLRM_bufferCLR[i];
		else
			pMatrixColors[pCLRM_bufferRow[i]][pCLRM_bufferCol[i]] = pCLRM_bufferCLR_before[i];
	}

	switch (status)
	{
	case 0:
		for (int i = 0; i < CLRM_bufferSize - 1; i++)
		{
			CLR_isChanged = false;

			pCLRM_bufferRow[i] = pCLRM_bufferRow[i + 1];
			pCLRM_bufferCol[i] = pCLRM_bufferCol[i + 1];
			pCLRM_bufferCLR[i] = pCLRM_bufferCLR[i + 1];
			pCLRM_bufferCLR_before[i] = pCLRM_bufferCLR_before[i + 1];

			if (pCLRM_bufferCLR[i] == CLR_current && !CLR_isChanged) {
				pCLRM_bufferCLR[i] = CLR_previous;
				CLR_isChanged = true;
			}

			if (pCLRM_bufferCLR[i] == CLR_previous && !CLR_isChanged) {
				pCLRM_bufferCLR[i] = CLR_postPrevious;
				CLR_isChanged = true;
			}

			if (pCLRM_bufferCLR[i] == CLR_postPrevious && !CLR_isChanged) {
				pCLRM_bufferCLR[i] = CLR_tail;
				CLR_isChanged = true;
			}

			pMatrixColors[pCLRM_bufferRow[i]][pCLRM_bufferCol[i]] = pCLRM_bufferCLR[i];
		}

		pCLRM_bufferRow[CLRM_bufferSize - 1] = coordRow;
		pCLRM_bufferCol[CLRM_bufferSize - 1] = coordCol;
		pCLRM_bufferCLR[CLRM_bufferSize - 1] = CLR_current;
		pCLRM_bufferCLR_before[CLRM_bufferSize - 1] = pMatrixColors[coordRow][coordCol];
		pMatrixColors[pCLRM_bufferRow[CLRM_bufferSize - 1]][pCLRM_bufferCol[CLRM_bufferSize - 1]] = CLR_current;
		break;

	default:
		for (int i = CLRM_bufferSize - 1; i > 0; i--)
		{
			pCLRM_bufferCLR[i] = pCLRM_bufferCLR[i - 1];
			pCLRM_bufferCLR_before[i] = pCLRM_bufferCLR_before[i - 1];

			pMatrixColors[pCLRM_bufferRow[i]][pCLRM_bufferCol[i]] = pCLRM_bufferCLR[i];
		}

		pCLRM_bufferRow[CLRM_bufferTotalCountErased] = 0;
		pCLRM_bufferCol[CLRM_bufferTotalCountErased] = 0;
		pCLRM_bufferCLR[CLRM_bufferTotalCountErased] = pMatrixColors[0][0];
		pCLRM_bufferCLR_before[CLRM_bufferTotalCountErased] = pMatrixColors[0][0];
		CLRM_bufferTotalCountErased++;

		if (CLRM_bufferTotalCountErased == CLRM_bufferSize)
			CLRM_bufferTotalCountErased = 0;
		break;
	}
}


///*************************************///
///             INSTRUMENTS             ///
///*************************************///

void AdvancedSquareMatrix::matrixConstructor() {
	pMatrix = new int* [matrixOrder];

	for (int i = 0; i < matrixOrder; i++)
		pMatrix[i] = new int[matrixOrder] {};
};
void AdvancedSquareMatrix::matrixColorsConstructor(short defaultColor) {
	pMatrixColors = new short* [matrixOrder];
	
	for (int i = 0; i < matrixOrder; i++)
		pMatrixColors[i] = new short[matrixOrder];

	resetMatrixColors(defaultColor);
}

void AdvancedSquareMatrix::resetMatrixValue(int defaultValue) {
	for (int ROW = 0; ROW < matrixOrder; ROW++)
	{
		for (int COL = 0; COL < matrixOrder; COL++)
			pMatrix[ROW][COL] = defaultValue;
	}
}
void AdvancedSquareMatrix::resetMatrixColors(short defaultColor) {
	for (int ROW = 0; ROW < matrixOrder; ROW++)
	{
		for (int COL = 0; COL < matrixOrder; COL++)
			pMatrixColors[ROW][COL] = defaultColor;
	}
}


void AdvancedSquareMatrix::swapMatrixCells(int firstRow, int firstCol, int secondRow, int secondCol) {
	int buffer = pMatrix[firstRow][firstCol];
	pMatrix[firstRow][firstCol] = pMatrix[secondRow][secondCol];
	pMatrix[secondRow][secondCol] = buffer;
}

void AdvancedSquareMatrix::SetOutputColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
