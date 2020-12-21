#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

class StringEditor
{
public:
	StringEditor();
	~StringEditor();

	//MODE's:
	//0 - cin
	//1 - file
	//2 - pArg
	void read(short mode = 0, const char* pArg = nullptr);


	void correctCaseOfLetters();

	void removeExtraSpaces();

	void removeDuplicatePunctuationMarks();


	void coutWordsThatDontContainNumbers();

	void coutWordsLength();


	void coutString();

	void coutFeatures();

	bool getInitializationStatus();

private:
	string storedString;
	bool isInitialized;
};