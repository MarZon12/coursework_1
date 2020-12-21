#include "StringEditor.h"

StringEditor::StringEditor() {
	isInitialized = false;
}
StringEditor::~StringEditor() {

}

void StringEditor::read(short mode, const char* pArg) {
	ifstream fin;
	string filename;

	switch (mode)
	{
	case 0:
		// It's time for crutches!
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Enter a string: ";
		getline(cin, storedString);
		isInitialized = true;
		break;

	case 1:
		cout << "Enter the name of the file with the extension. (for example, text.txt; EN only)" << endl;

		// It's time for crutches!
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		getline(cin, filename);

		fin.open(filename.data());
		if (fin.is_open()) {
			getline(fin, storedString);
			fin.close();
			isInitialized = true;
		}
		else {
			cout << static_cast<char>(7) << "The file (" << filename.c_str() << ") could not be read." << endl;
			system("pause");
		}
		break;

	case 2:
		storedString = pArg;
		isInitialized = true;
		break;

	default:
		cout << static_cast<char>(7);
		cout << endl << endl
			<< "\t+=================================================================+\n"
			<< "\t|       Attention! The entered reading mode does not exist.       |\n"
			<< "\t+=================================================================+\n" << endl;
		break;
	}
}


void StringEditor::correctCaseOfLetters() {
	int offset = static_cast<int>('a') - static_cast<int>('A');

	// to lowercase
	for (int i = 1; i < storedString.length(); i++)
	{
		if (static_cast<int>(storedString[i]) >= static_cast<int>('A') && static_cast<int>(storedString[i]) <= static_cast<int>('Z'))
			storedString[i] = static_cast<char>(static_cast<int>(storedString[i]) + offset);
	}

	// to uppercase
	bool isTrue;
	int nextSentenceDotPos = 0;
	do
	{
		isTrue = false;
		for (int i = nextSentenceDotPos; i < storedString.length(); i++)
		{
			//search for the first letter for the first sentence
			if (nextSentenceDotPos == 0)
			{
				if (static_cast<int>(storedString[i]) >= static_cast<int>('A') && static_cast<int>(storedString[i]) <= static_cast<int>('Z'))
					break;

				if (static_cast<int>(storedString[i]) >= static_cast<int>('a') && static_cast<int>(storedString[i]) <= static_cast<int>('z')) {
					storedString[i] = static_cast<char>(static_cast<int>(storedString[i]) - offset);
					break;
				}
			}

			//for other
			if (nextSentenceDotPos < storedString.length() - 1)
			{
				if (storedString[nextSentenceDotPos + 1] == ' ')
				{
					if (static_cast<int>(storedString[i]) >= static_cast<int>('A') && static_cast<int>(storedString[i]) <= static_cast<int>('Z'))
						break;

					if (static_cast<int>(storedString[i]) >= static_cast<int>('a') && static_cast<int>(storedString[i]) <= static_cast<int>('z')) {
						storedString[i] = static_cast<char>(static_cast<int>(storedString[i]) - offset);
						break;
					}
				}
			}
		}

		//finding the point position for the next sentence
		for (int i = nextSentenceDotPos; i < storedString.length(); i++)
		{
			if (storedString[i] == '.' && i > nextSentenceDotPos) {
				nextSentenceDotPos = i;
				isTrue = true;
				break;
			}

		}
	} while (isTrue);
}

void StringEditor::removeExtraSpaces() {
	bool isTrue;
	do
	{
		isTrue = false;
		for (int i = 0; i < storedString.length() - 1; i++)
		{
			if (storedString[i] == ' ' && storedString[i + 1] == ' ')
			{
				for (int y = i; y < storedString.length(); y++)
					storedString[y] = storedString[y + 1];
				storedString.pop_back();
				isTrue = true;
			}

			if (storedString[i] == ' ' && storedString[i + 1] == '!'
				|| storedString[i] == ' ' && storedString[i + 1] == '"'
				|| storedString[i] == ' ' && storedString[i + 1] == ','
				|| storedString[i] == ' ' && storedString[i + 1] == '-'
				|| storedString[i] == ' ' && storedString[i + 1] == ':'
				|| storedString[i] == ' ' && storedString[i + 1] == ';'
				|| storedString[i] == ' ' && storedString[i + 1] == '?'
				|| storedString[i] == ' ' && storedString[i + 1] == '.')
			{
				for (int y = i; y < storedString.length(); y++)
					storedString[y] = storedString[y + 1];
				storedString.pop_back();
				isTrue = true;
			}
		}
	} while (isTrue);

	if (storedString[0] == ' ')
	{
		for (int y = 0; y < storedString.length(); y++)
			storedString[y] = storedString[y + 1];
		storedString.pop_back();
	}
	if (storedString[storedString.length() - 1] == ' ')
	{
		storedString.pop_back();
	}
}

void StringEditor::removeDuplicatePunctuationMarks() {
	bool isTrue;
	do
	{
		isTrue = false;
		for (int i = 0; i < storedString.length() - 1; i++)
		{
			// ! " , - : ; ?
			if (storedString[i] == '!' && storedString[i + 1] == '!'
				|| storedString[i] == '"' && storedString[i + 1] == '"'
				|| storedString[i] == ',' && storedString[i + 1] == ','
				|| storedString[i] == '-' && storedString[i + 1] == '-'
				|| storedString[i] == ':' && storedString[i + 1] == ':'
				|| storedString[i] == ';' && storedString[i + 1] == ';'
				|| storedString[i] == '?' && storedString[i + 1] == '?')
			{
				for (int y = i; y < storedString.length(); y++)
					storedString[y] = storedString[y + 1];
				storedString.pop_back();
				isTrue = true;
			}

			// ...
			if (storedString[i] == '.' && i < storedString.length() - 2)
			{
				if (storedString[i + 1] == '.' && storedString[i + 2] == '.') {
					i += 2;
				}

				if (i < storedString.length() - 1) {
					if (storedString[i + 1] == '.') {
						for (int y = i; y < storedString.length(); y++)
							storedString[y] = storedString[y + 1];
						storedString.pop_back();
						isTrue = true;
					}
				}
			}

			// .
			if (storedString[i] == '.' && i < storedString.length() - 1)
			{
				if (storedString[i + 1] == '.' && storedString[i + 2] != '.') {
					for (int y = i; y < storedString.length(); y++)
						storedString[y] = storedString[y + 1];
					storedString.pop_back();
					isTrue = true;
				}
			}
		}
	} while (isTrue);
}


void StringEditor::coutWordsThatDontContainNumbers() {
	int wordEndPos = 0;
	bool word_containsUnacceptableCharacters(false), word_isFound(false), atLeastOneWordWasFoundThatMatchesTheCondition(false), doOnce(true);

	//finding the beginning of a word
	for (int wordStartPos = 0; wordStartPos < storedString.length(); wordStartPos++)
	{
		if (static_cast<int>(storedString[wordStartPos]) >= static_cast<int>('A') && static_cast<int>(storedString[wordStartPos]) <= static_cast<int>('Z')
			|| static_cast<int>(storedString[wordStartPos]) >= static_cast<int>('a') && static_cast<int>(storedString[wordStartPos]) <= static_cast<int>('z')
			|| static_cast<int>(storedString[wordStartPos]) >= static_cast<int>('0') && static_cast<int>(storedString[wordStartPos]) <= static_cast<int>('9'))
		{
			word_isFound = true;
			wordEndPos = wordStartPos; //in case the word is the last in the string and it contains only one character

			//finding the end of a word
			for (int WEP = wordStartPos; WEP < storedString.length(); WEP++) //WEP means Word End Pos
			{
				if (static_cast<int>(storedString[WEP]) >= static_cast<int>('A') && static_cast<int>(storedString[WEP]) <= static_cast<int>('Z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('a') && static_cast<int>(storedString[WEP]) <= static_cast<int>('z'))
				{
					wordEndPos = WEP;
					continue;
				}

				//word boundary limiters
				if (!(static_cast<int>(storedString[WEP]) >= static_cast<int>('A') && static_cast<int>(storedString[WEP]) <= static_cast<int>('Z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('a') && static_cast<int>(storedString[WEP]) <= static_cast<int>('z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('0') && static_cast<int>(storedString[WEP]) <= static_cast<int>('9')))
				{
					wordEndPos = WEP - 1;
					break;
				}

				//if the word contains these characters, then look for the end of the word
				if (static_cast<int>(storedString[WEP]) >= static_cast<int>('0') && static_cast<int>(storedString[WEP]) <= static_cast<int>('9'))
				{
					for (int WEP_toSkip = WEP; WEP_toSkip < storedString.length(); WEP_toSkip++)
					{
						//word boundary limiters
						if (!(static_cast<int>(storedString[WEP_toSkip]) >= static_cast<int>('A') && static_cast<int>(storedString[WEP_toSkip]) <= static_cast<int>('Z')
							|| static_cast<int>(storedString[WEP_toSkip]) >= static_cast<int>('a') && static_cast<int>(storedString[WEP_toSkip]) <= static_cast<int>('z')
							|| static_cast<int>(storedString[WEP_toSkip]) >= static_cast<int>('0') && static_cast<int>(storedString[WEP_toSkip]) <= static_cast<int>('9')))
						{
							wordEndPos = WEP_toSkip - 1;
							break;
						}
						if (WEP_toSkip == storedString.length() - 1)
						{
							wordEndPos = WEP_toSkip;
						}
					}
					word_containsUnacceptableCharacters = true;
					break;
				}
			}
		}

		if (word_isFound)
		{
			if (word_containsUnacceptableCharacters)
			{
				word_containsUnacceptableCharacters = false;
			}
			else
			{
				atLeastOneWordWasFoundThatMatchesTheCondition = true;

				if (doOnce)
				{
					cout << "Found words that don't contain numbers: ";
					doOnce = false;
				}
				for (int i = wordStartPos; i <= wordEndPos; i++)
				{
					cout << storedString[i];
				}
				cout << ' ';
			}

			wordStartPos = wordEndPos;
			word_isFound = false;
		}

		if (wordStartPos == storedString.length() - 1)
		{
			if (atLeastOneWordWasFoundThatMatchesTheCondition == false)
				cout << "No words were found for this condition that did not contain numbers." << endl;
			else
				cout << endl;
		}
	}
}

void StringEditor::coutWordsLength() {
	int word_endPos = 0;
	bool word_containsUnacceptableCharacters(false), word_isFound(false), atLeastOneWordWasFoundThatMatchesTheCondition(false), doOnce(true);

	for (int word_startPos = 0; word_startPos < storedString.length(); word_startPos++)
	{
		if (static_cast<int>(storedString[word_startPos]) >= static_cast<int>('A') && static_cast<int>(storedString[word_startPos]) <= static_cast<int>('Z')
			|| static_cast<int>(storedString[word_startPos]) >= static_cast<int>('a') && static_cast<int>(storedString[word_startPos]) <= static_cast<int>('z')
			|| static_cast<int>(storedString[word_startPos]) >= static_cast<int>('0') && static_cast<int>(storedString[word_startPos]) <= static_cast<int>('9'))
		{
			word_endPos = word_startPos; //in case the word is the last in the string and it contains only one character

			//finding the end of a word
			for (int WEP = word_startPos; WEP < storedString.length(); WEP++) //WEP means Word End Pos
			{
				if (static_cast<int>(storedString[WEP]) >= static_cast<int>('A') && static_cast<int>(storedString[WEP]) <= static_cast<int>('Z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('a') && static_cast<int>(storedString[WEP]) <= static_cast<int>('z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('0') && static_cast<int>(storedString[WEP]) <= static_cast<int>('9'))
				{
					word_endPos = WEP;
					word_isFound = true;
					continue;
				}

				//word boundary limiters
				if (!(static_cast<int>(storedString[WEP]) >= static_cast<int>('A') && static_cast<int>(storedString[WEP]) <= static_cast<int>('Z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('a') && static_cast<int>(storedString[WEP]) <= static_cast<int>('z')
					|| static_cast<int>(storedString[WEP]) >= static_cast<int>('0') && static_cast<int>(storedString[WEP]) <= static_cast<int>('9')))
				{
					word_endPos = WEP - 1;
					word_isFound = true;
					break;
				}
			}
		}

		if (word_isFound)
		{
			if (doOnce)
			{
				cout << "Words length:\n";
				doOnce = false;
			}

			cout << word_endPos - word_startPos + 1 << "\t= ";
			for (int i = word_startPos; i <= word_endPos; i++)
			{
				cout << storedString[i];
			}
			cout << endl;

			word_startPos = word_endPos;
			word_isFound = false;
		}

		if (word_startPos == storedString.length() - 1)
		{
			//cout << endl;
		}

	}
}


void StringEditor::coutString() {
	cout << storedString << endl;
}

bool StringEditor::getInitializationStatus() {
	return isInitialized;
};

void StringEditor::coutFeatures() {
	cout << "Features:" << endl;
	cout << ".. \t\t->\t .\n"
		<< ".... .. . \t->\t ...\n"
		<< ",,,, ,, , \t->\t ,\n"
		<< "!!! \t\t->\t !\n"
		<< "??? \t\t->\t ?\n"
		<< "wOrd.woRd \t->\t Word.word\n"
		<< "  wOrd  .  woRd ->\t Word. Word\n"
		<< " (wOrd ).  woRd ->\t (Word ). Word\n"
		<< endl;
}
