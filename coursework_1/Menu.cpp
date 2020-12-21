#include "Menu.h"

Menu::Menu() {
}
Menu::~Menu() {
}

void Menu::openMainMenu() {
	int choice;
	while (true)
	{
		cout << "[Main Menu]\n\n"
			<< "Select a practical work:\n"
			<< "1 - Practical work #1\n" // READY
			<< "2 - Practical work #2\n" // READY
			<< "3 - Practical work #3\n" // IN PROCESS
			<< "4 - Practical work #4\n"
			<< "5 - exit"
			<< endl;
		choice = this->getIntChoice();
		system("cls");
		switch (choice)
		{
		case 1:
			this->Pw1_openMainMenu();
			break;

		case 2:
			this->Pw2_openMainMenu();
			break;

		case 3:
			this->Pw3_openMainMenu();
			break;

		case 4:
			this->Pw4_openMainMenu();
			break;

		default:
			return;
			break;
		}
	}
}

//  +=====================================+
//  |  THE MAIN MENU OF PRACTICAL WORKS   |
//  +=====================================+

void Menu::Pw1_openMainMenu() {
	int choice;

	while (true)
	{
		cout << "[Practical work #1]\n\n"

			<< "Select the function you are interested in:\n"
			<< "1 - To convert a decimal number to binary\n"
			<< "2 - To convert a binary number to decimal (before that, you must select item 1)\n\n"

			<< "3 - Get information about the amount of memory used by different data types.\n"
			<< "4 - Get a binary representation (before that, you must select item 1)\n"
			<< "5 - Get a decimal representation (before that, you must select item 2)\n\n"

			<< "6 - Colors switcher: the colors are currently " << (binaryReprObj.getColorsState() ? "activated" : "deactivated") << "\n\n"

			<< "7 - return back"
			<< endl;
		choice = this->getIntChoice();
		system("cls");

		switch (choice)
		{
		case 1:
			this->Pw1_openSubmenuBin();
			break;

		case 2:
			if (binaryReprObj.convertBinToDec() != nullptr)
				cout << binaryReprObj.convertBinToDec() << endl;
			system("pause");
			system("cls");
			break;

		case 3:
			binaryReprObj.coutWeightDataTypes();
			system("pause");
			system("cls");
			break;

		case 4:
			binaryReprObj.coutBinRepresentation();
			system("pause");
			system("cls");
			break;

		case 5:
			if (binaryReprObj.getDecRepresentation() != nullptr)
				cout << binaryReprObj.getDecRepresentation() << endl;
			system("pause");
			system("cls");
			break;

		case 6:
			binaryReprObj.setColorsState(!binaryReprObj.getColorsState());
			break;

		default:
			system("cls");
			return;
			break;
		}
	}
}

void Menu::Pw2_openMainMenu() {
	int choice;
	int buffer;
	int buffer2;
	bool needsClearScreen = false;

	while (true)
	{
		needsClearScreen = true;
		cout << "[Practical work #2]\n\n"
			<< "Select the function you are interested in:\n"
			<< "Basic:\n"
			<< "1  - Create an array (size now: " << intArrayObj.getSize() << ")\n"
			<< "2  - Fill the array with random numbers\n"
			<< "3  - Output an array\n\n"

			<< "Sorting:\n"
			<< "4  - Bubble sort\n"
			<< "5  - Shaker sort\n"
			<< "6  - Comb sort\n"
			<< "7  - Comb sort (optimized)\n"
			<< "8  - Insert sort\n\n"

			<< "Search:\n"
			<< "9  - Minimum value\n"
			<< "10 - Maximum value\n"
			<< "11 - Average value\n\n"

			<< "12 - Linear search\n"
			<< "13 - Binary search\n\n"

			<< "14 - The number of elements that is less than the one you entered\n"
			<< "15 - The number of elements that is greater than the one you entered\n\n"

			<< "Other:\n"
			<< "16 - Swap the elements\n\n"

			<< "17 - return back"
			<< endl;
		choice = this->getIntChoice();
		system("cls");

		switch (choice)
		{
		case 1:
			while (true)
			{
				cout << "Enter the size of the array.\n";
				buffer = this->getIntChoice();
				if (buffer <= 0)
				{
					cout << "The array size cannot be less than or equal to 0. Try again!" << endl;
					system("pause");
					system("cls");
				}
				else {
					intArrayObj.create(buffer);
					system("cls");
					break;
				}
			}
			cout << "[Notification] The array is created!" << endl << endl;
			needsClearScreen = false;
			break;

		case 2:
			cout << (intArrayObj.fillArrayRand() ? "[Notification] The array is filled with random numbers!" : "[Notification] Something went wrong...") << endl << endl;
			needsClearScreen = false;
			break;

		case 3:
			cout << "Array:" << endl;
			intArrayObj.coutArray();
			break;

		case 4:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSort(0);
			needsClearScreen = false;
			cout << endl;
			break;

		case 5:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSort(1);
			needsClearScreen = false;
			cout << endl;
			break;

		case 6:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSort(2);
			needsClearScreen = false;
			cout << endl;
			break;

		case 7:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSort(3);
			needsClearScreen = false;
			cout << endl;
			break;

		case 8:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSort(4);
			needsClearScreen = false;
			cout << endl;
			break;

		case 9:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSearch(0);
			needsClearScreen = false;
			cout << endl;
			break;

		case 10:
			cout << "[Notification box]" << endl;
			intArrayObj.testTimeSearch(1);
			needsClearScreen = false;
			cout << endl;
			break;

		case 11:
			cout << "[Notification] Average min & max: " << intArrayObj.computeAverageMinAndMax() << endl;
			needsClearScreen = false;
			cout << endl;
			break;

		case 12:
			cout << "Enter a number: ";
			this->clearCin();
			cin >> buffer;
			system("cls");
			intArrayObj.testTimeSearch(2, 1, buffer);
			break;

		case 13:
			cout << "Enter a number: ";
			this->clearCin();
			cin >> buffer;
			system("cls");
			intArrayObj.testTimeSearch(3, 1, buffer);
			break;

		case 14:
			cout << "Enter a number: ";
			this->clearCin();
			cin >> buffer;
			cout << "The number of elements that is less than the one you entered: " << intArrayObj.getNumIsLessThanInput(buffer) << endl;
			break;

		case 15:
			cout << "Enter a number: ";
			this->clearCin();
			cin >> buffer;
			cout << "The number of elements that is greater than the one you entered: " << intArrayObj.getNumIsGreaterThanInput(buffer) << endl;
			break;

		case 16:
			cout << "Enter a first index: ";
			this->clearCin();
			cin >> buffer;
			cout << "Enter a second index: ";
			this->clearCin();
			cin >> buffer2;
			cout << (intArrayObj.swapArrayElements(buffer, buffer2) ? "Successfully!" : "Something went wrong...") << endl;
			break;

		default:
			system("cls");
			return;
			break;
		}

		if (needsClearScreen)
		{
			system("pause");
			system("cls");
		}

	}
}

void Menu::Pw3_openMainMenu() {
	int choice;
	int buffer;

	while (true)
	{
		cout << "[Practical work #3]\n\n";

		if (squareMatrixObj.getMatrixPointer() != nullptr)
		{
			cout << "Main matrix:" << endl;
			squareMatrixObj.coutMatrix();
		}

		cout << "Select the function you are interested in:\n"
			<< "1  - Create a square Matrix\n"
			<< "2  - Fill in the matrix using the snail method\n"
			<< "3  - Fill in the matrix using the wave method\n"
			<< "4  - Fill in the matrix using the rand method\n\n"

			<< "Get a new matrix by rearranging:\n"
			<< "5  - clockwise rotation method\n"
			<< "6  - diagonal method\n"
			<< "7  - horizontal method\n"
			<< "8  - vertical method\n"
			<< "9  - Output an additional and main matrix\n\n"

			<< "10  - To sort the main matrix\n\n"

			<< "Math (main matrix):\n"
			<< "11 - Multiply all cells by a number\n"
			<< "12 - Divide all cells by a number\n"
			<< "13 - Add a number to all cells\n"
			<< "14 - Subtract a number from all cells\n\n"

			<< "15 - return back"
			<< endl;
		choice = this->getIntChoice();
		system("cls");

		switch (choice)
		{
		case 1:
			while (true)
			{
				cout << "Enter the order of the matrix.";
				buffer = this->getIntChoice();
				if (buffer <= 0)
				{
					cout << "The matrix order cannot be less than or equal to 0. Try again!" << endl;
					system("pause");
					system("cls");
				}
				else {
					squareMatrixObj.create(buffer);
					squareMatrixObj.resetMatrixColors(0);
					system("cls");
					break;
				}
			}
			cout << "[Notification] The matrix is created!" << endl << endl;
			break;

		case 2:
			squareMatrixObj.fillSnail(4, true);
			system("pause");
			system("cls");
			break;

		case 3:
			squareMatrixObj.fillWave(4, true);
			system("pause");
			system("cls");
			break;

		case 4:
			squareMatrixObj.fillRand(4, true);
			system("pause");
			system("cls");
			break;

		case 5:
			squareMatrixObj2 = squareMatrixObj;
			squareMatrixObj2.swapQuarters(0);
			cout << "[Notification] Completed!" << endl << endl;
			break;

		case 6:
			squareMatrixObj2 = squareMatrixObj;
			squareMatrixObj2.swapQuarters(1);
			cout << "[Notification] Completed!" << endl << endl;
			break;

		case 7:
			squareMatrixObj2 = squareMatrixObj;
			squareMatrixObj2.swapQuarters(2);
			cout << "[Notification] Completed!" << endl << endl;
			break;

		case 8:
			squareMatrixObj2 = squareMatrixObj;
			squareMatrixObj2.swapQuarters(3);
			cout << "[Notification] Completed!" << endl << endl;
			break;

		case 9:
			cout << "Main matrix:" << endl;
			squareMatrixObj.coutMatrix();
			cout << "Additional matrix:" << endl;
			squareMatrixObj2.coutMatrix();
			system("pause");
			system("cls");
			break;

		case 10:
			squareMatrixObj.performCombSort();
			cout << "[Notification] Completed!" << endl << endl;
			break;

		case 11:
			cout << "Enter a number." << endl;
			buffer = this->getIntChoice();
			squareMatrixObj.matrixMath(2, buffer);
			break;

		case 12:
			while (true)
			{
				cout << "Enter a number." << endl;
				buffer = this->getIntChoice();
				if (buffer == 0)
				{
					cout << "The number cannot be equal to 0. Try again!" << endl;
					system("pause");
					system("cls");
				}
				else {
					squareMatrixObj.matrixMath(3, buffer);
					system("cls");
					break;
				}
			}
			break;

		case 13:
			cout << "Enter a number." << endl;
			buffer = this->getIntChoice();
			squareMatrixObj.matrixMath(0, buffer);
			break;

		case 14:
			cout << "Enter a number." << endl;
			buffer = this->getIntChoice();
			squareMatrixObj.matrixMath(1, buffer);
			break;

		default:
			system("cls");
			return;
			break;
		}
	}
}

void Menu::Pw4_openMainMenu() {
	int choice;

	while (true)
	{
		cout << "[Practical work #4]\n\n";

		if (stringEditorObj.getInitializationStatus() == true)
		{
			cout << "String: ";
			stringEditorObj.coutString();
			cout << endl;
		}

		cout << "Select the function you are interested in:\n"
			<< "1 - Enter a string using the keyboard\n"
			<< "2 - Enter a string using a file\n\n"

			<< "Editing:\n"
			<< "3 - Remove extra spaces\n"
			<< "4 - Remove duplicate punctuation marks\n"
			<< "5 - Correct case of letters\n\n"

			<< "6 - Display sequence words that do not contain numbers\n"
			<< "7 - Display the number of characters in each word in the sequence\n\n"

			<< "8 - Display features\n\n"

			<< "9 - return back"
			<< endl;
		choice = this->getIntChoice();
		system("cls");

		switch (choice)
		{
		case 1:
			stringEditorObj.read(0);
			system("cls");
			break;

		case 2:
			stringEditorObj.read(1);
			system("cls");
			break;

		case 3:
			stringEditorObj.removeExtraSpaces();
			break;

		case 4:
			stringEditorObj.removeDuplicatePunctuationMarks();
			break;

		case 5:
			stringEditorObj.correctCaseOfLetters();
			break;

		case 6:
			stringEditorObj.coutWordsThatDontContainNumbers();
			system("pause");
			system("cls");
			break;

		case 7:
			stringEditorObj.coutWordsLength();
			system("pause");
			system("cls");
			break;

		case 8:
			stringEditorObj.coutFeatures();
			system("pause");
			system("cls");
			break;

		default:
			system("cls");
			return;
			break;
		}
	}
}

//  +=====================================+
//  |     SUBMENU OF PRACTICAL WORKS      |
//  +=====================================+

void Menu::Pw1_openSubmenuBin() {
	int choice;

	short ch_1 = 0;
	int ch_2 = 0;
	long ch_3 = 0;
	long long ch_4 = 0;

	unsigned short ch_5 = 0;
	unsigned int ch_6 = 0;
	unsigned long ch_7 = 0;
	unsigned long long ch_8 = 0;

	float ch_9 = 0;
	double ch_10 = 0;

	char ch_11 = 0;
	unsigned char ch_12 = 0;

	while (true)
	{
		system("cls");
		cout << "Select the type of variable you want to use:\n"
			<< "1  - short\n"
			<< "2  - int\n"
			<< "3  - long\n"
			<< "4  - long long\n\n"

			<< "5  - unsigned short\n"
			<< "6  - unsigned int\n"
			<< "7  - unsigned long\n"
			<< "8  - unsigned long long\n\n"

			<< "9  - float\n"
			<< "10 - double\n\n"

			<< "11 - char (ANSI)\n"
			<< "12 - unsigned char (ANSI)\n\n"

			<< "13 - return back"
			<< endl;

		choice = this->getIntChoice();
		system("cls");
		this->clearCin();
		cout << "Enter the value of the variable: ";

		switch (choice)
		{
		case 1:
			cin >> ch_1;
			system("cls");
			binaryReprObj.convertDecToBin(ch_1);
			break;

		case 2:
			cin >> ch_2;
			system("cls");
			binaryReprObj.convertDecToBin(ch_2);
			break;

		case 3:
			cin >> ch_3;
			system("cls");
			binaryReprObj.convertDecToBin(ch_3);
			break;

		case 4:
			cin >> ch_4;
			system("cls");
			binaryReprObj.convertDecToBin(ch_4);
			break;

		case 5:
			cin >> ch_5;
			system("cls");
			binaryReprObj.convertDecToBin(ch_5);
			break;

		case 6:
			cin >> ch_6;
			system("cls");
			binaryReprObj.convertDecToBin(ch_6);
			break;

		case 7:
			cin >> ch_7;
			system("cls");
			binaryReprObj.convertDecToBin(ch_7);
			break;

		case 8:
			cin >> ch_8;
			system("cls");
			binaryReprObj.convertDecToBin(ch_8);
			break;

		case 9:
			cin >> ch_9;
			system("cls");
			binaryReprObj.convertDecToBin(ch_9);
			break;

		case 10:
			cin >> ch_10;
			system("cls");
			binaryReprObj.convertDecToBin(ch_10);
			break;

		case 11:
			cin >> ch_11;
			system("cls");
			binaryReprObj.convertDecToBin(ch_11);
			break;

		case 12:
			cin >> ch_12;
			system("cls");
			binaryReprObj.convertDecToBin(ch_12);
			break;

		default:
			system("cls");
			return;
			break;
		}
		binaryReprObj.coutBinRepresentation();

		if (!performTheActionAgain()) {
			system("cls");
			return;
		}
	}
}


//PRIVATE

int Menu::getIntChoice() {
	int choice;
	this->clearCin();
	cout << endl;
	cout << "Your choice: ";
	cin >> choice;

	return choice;
}

void Menu::clearCin() {
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
}

bool Menu::performTheActionAgain() {
	cout << endl;
	cout << "Perform the action again?\n"
		<< "1 - Yes\n"
		<< "2 - No"
		<< endl;
	if (this->getIntChoice() == 1) {
		system("cls");
		return true;
	}
	else {
		system("cls");
		return false;
	}
}
