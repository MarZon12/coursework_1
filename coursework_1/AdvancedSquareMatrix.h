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


	void create(int matrixOrder);
	void coutMatrix();
	

	void performCombSort();

	//MATH MODE's:
	//0 - add
	//1 - subtract
	//2 - multiply
	//3 - divide
	void matrixMath(short mathMode, int value);

	//SWAP MODE's:
	//0 - rotate a quarter (clockwise)
	//1 - swap quarters (diagonally)
	//2 - swap quarters (horizontally)
	//3 - swap quarters (vertically)
	bool swapQuarters(short swapMode);


	void fillSnail(int tailLength = 4, bool saveTailEffect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_postPrevious = 4, short CLR_tail = 15);
	void fillWave(int tailLength = 4, bool saveTailEffect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_postPrevious = 4, short CLR_tail = 15);
	void fillRand(int tailLength = 4, bool saveTailEffect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_postPrevious = 4, short CLR_tail = 15);
	
	
	int** getMatrixPointer();
	int getMatrixOrder();
	void operator=(AdvancedSquareMatrix& source);

	void resetMatrixValue(int defaultValue);
	void resetMatrixColors(short defaultColor = 15);

private:
	int** pMatrix;
	short** pMatrixColors;

	int matrixOrder;

	//CLR MEMORY
	//INDEX <MAX-3 - tail
	//INDEX =MAX-2 - post-previous
	//INDEX =MAX-1 - previous
	//INDEX =MAX   - current
	short CLRM_bufferSize;
	short CLRM_bufferTotalCountErased;
	short* pCLRM_bufferRow;
	short* pCLRM_bufferCol;
	short* pCLRM_bufferCLR;
	short* pCLRM_bufferCLR_before;

	void CLRM_constructor(int tailLength);
	bool CLRM_destructor();
	//STATUS:
	// 0 - add current (just changed)
	// >=1 - there is no current item, continue for previously entered items one step further  <- default
	void CLRM_manipulator(unsigned int coordRow = 0, unsigned int coordCol = 0, unsigned short status = 1, bool saveTailEffect = false, short CLR_current = 2, short CLR_previous = 6, short CLR_postPrevious = 4, short CLR_tail = 15);


	void matrixConstructor();
	void matrixColorsConstructor(short defaultColor = 15);

	


	void swapMatrixCells(int firstRow, int firstCol, int secondRow, int secondCol);
	void SetOutputColor(int text = 15, int bg = 0);
};