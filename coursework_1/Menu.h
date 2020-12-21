#pragma once
#include <iostream>
#include <windows.h>

#include "BinaryRepresentation.h"
#include "OneDimensionalStaticIntArray.h"
#include "AdvancedSquareMatrix.h"
#include "StringEditor.h"

using std::cout;
using std::cin;
using std::endl;

class Menu
{
public:
	Menu();
	~Menu();

	void openMainMenu();

	//  +=====================================+
	//  |  THE MAIN MENU OF PRACTICAL WORKS   |
	//  +=====================================+

	void Pw1_openMainMenu();

	void Pw2_openMainMenu();

	void Pw3_openMainMenu();

	void Pw4_openMainMenu();

	//  +=====================================+
	//  |     SUBMENU OF PRACTICAL WORKS      |
	//  +=====================================+

	void Pw1_openSubmenuBin();

private:
	BinaryRepresentation binaryReprObj;

	OneDimensionalStaticIntArray intArrayObj;

	AdvancedSquareMatrix squareMatrixObj;
	AdvancedSquareMatrix squareMatrixObj2;

	StringEditor stringEditorObj;

	int getIntChoice();

	void clearCin();

	bool performTheActionAgain();
};

