#pragma once
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

//Сегодня мы будем тестировать данную программу на наличие ошибок, возможно, что они есть, а так же возможно, что их нет.
//Today we will test this program for errors, it is possible that they exist, and it is also possible that they do not exist.
//Today   we will test this program for errors,   it is possible   that   they   exist  , and it is also possible that they do not   exist.


class StringEditor
{
public:
	StringEditor() {

	}
	~StringEditor() {

	}

	//MODE's:
	//0 - cin
	//1 - file
	//2 - arg
	void read(short mode = 0, const char* arg = nullptr) {
		ifstream fin;
		string filename;
		
		switch (mode)
		{
		case 0:
			// It's time for crutches!
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			getline(cin, stored_string);

			break;

		case 1:
			cout << "Enter the name of the file with the extension. (for example, text.txt)" << endl;
			
			// It's time for crutches!
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			getline(cin, filename);

			fin.open(filename.data());
			if (fin.is_open()) {
				getline(fin, stored_string);
				fin.close();
			}
			else
				cout << static_cast<char>(7) << "The file (" << filename.c_str() << ") could not be read." << endl;

			break; 

		case 2:
			stored_string = arg;

			break;

		default:
			cout << static_cast<char>(7);
			cout << endl << endl
				<< "\t+=================================================================+" << endl
				<< "\t|       Attention! The entered reading mode does not exist.       |" << endl
				<< "\t+=================================================================+" << endl << endl;

			break;
		}

		cout << "String:" << endl; //WARNING
		cout_string(); //WARNING
	}

	void edit_uppercase_lowercase_letters(){
		int offset = static_cast<int>('a') - static_cast<int>('A');
		
		// to lowercase
		for (int i = 1; i < stored_string.length(); i++)
		{
			if (static_cast<int>(stored_string[i]) >= static_cast<int>('A') && static_cast<int>(stored_string[i]) <= static_cast<int>('Z'))
				stored_string[i] = static_cast<char>(static_cast<int>(stored_string[i]) + offset);
		}

		// to uppercase
		bool is_true;
		int next_sentence_dot_pos = 0;
		do
		{
			is_true = false;
			for (int i = next_sentence_dot_pos; i < stored_string.length(); i++)
			{
				//search for the first letter for the first sentence
				if (next_sentence_dot_pos == 0)
				{
					if (static_cast<int>(stored_string[i]) >= static_cast<int>('A') && static_cast<int>(stored_string[i]) <= static_cast<int>('Z'))
						break;

					if (static_cast<int>(stored_string[i]) >= static_cast<int>('a') && static_cast<int>(stored_string[i]) <= static_cast<int>('z')) {
						stored_string[i] = static_cast<char>(static_cast<int>(stored_string[i]) - offset);
						break;
					}
				}

				//for other
				if (next_sentence_dot_pos < stored_string.length() - 1)
				{
					if (stored_string[next_sentence_dot_pos + 1] == ' ')
					{
						if (static_cast<int>(stored_string[i]) >= static_cast<int>('A') && static_cast<int>(stored_string[i]) <= static_cast<int>('Z'))
							break;

						if (static_cast<int>(stored_string[i]) >= static_cast<int>('a') && static_cast<int>(stored_string[i]) <= static_cast<int>('z')) {
							stored_string[i] = static_cast<char>(static_cast<int>(stored_string[i]) - offset);
							break;
						}
					}
				}
			}

			//finding the point position for the next sentence
			for (int i = next_sentence_dot_pos; i < stored_string.length(); i++)
			{
				if (stored_string[i] == '.' && i > next_sentence_dot_pos) {
					next_sentence_dot_pos = i;
					is_true = true;
					break;
				}

			}
		} while (is_true);
	}

	void edit_remove_extra_spaces() {
		bool is_true;
		do
		{
			is_true = false;
			for (int i = 0; i < stored_string.length()-1; i++)
			{
				if (stored_string[i] == ' ' && stored_string[i + 1] == ' ')
				{
					for (int y = i; y < stored_string.length(); y++)
						stored_string[y] = stored_string[y + 1];
					stored_string.pop_back();
					is_true = true;
				}

				if (stored_string[i] == ' ' && stored_string[i + 1] == '!'
					|| stored_string[i] == ' ' && stored_string[i + 1] == '"'
					|| stored_string[i] == ' ' && stored_string[i + 1] == ','
					|| stored_string[i] == ' ' && stored_string[i + 1] == '-'
					|| stored_string[i] == ' ' && stored_string[i + 1] == ':'
					|| stored_string[i] == ' ' && stored_string[i + 1] == ';'
					|| stored_string[i] == ' ' && stored_string[i + 1] == '?'
					|| stored_string[i] == ' ' && stored_string[i + 1] == '.')
				{
					for (int y = i; y < stored_string.length(); y++)
						stored_string[y] = stored_string[y + 1];
					stored_string.pop_back();
					is_true = true;
				}
			}
		} while (is_true);

		if (stored_string[0] == ' ')
		{
			for (int y = 0; y < stored_string.length(); y++)
				stored_string[y] = stored_string[y + 1];
			stored_string.pop_back();
		}
		if (stored_string[stored_string.length() - 1] == ' ')
		{
			stored_string.pop_back();
		}
	}

	void edit_remove_duplicate_punctuation_marks() {
		bool is_true;
		do
		{
			is_true = false;
			for (int i = 0; i < stored_string.length()-1; i++)
			{
				// ! " , - : ; ?
				if (stored_string[i] == '!' && stored_string[i + 1] == '!'
					|| stored_string[i] == '"' && stored_string[i + 1] == '"'
					|| stored_string[i] == ',' && stored_string[i + 1] == ','
					|| stored_string[i] == '-' && stored_string[i + 1] == '-'
					|| stored_string[i] == ':' && stored_string[i + 1] == ':'
					|| stored_string[i] == ';' && stored_string[i + 1] == ';'
					|| stored_string[i] == '?' && stored_string[i + 1] == '?')
				{
					for (int y = i; y < stored_string.length(); y++)
						stored_string[y] = stored_string[y + 1];
					stored_string.pop_back();
					is_true = true;
				}

				// ...
				if (stored_string[i] == '.' && i < stored_string.length() - 2)
				{
					if (stored_string[i + 1] == '.' && stored_string[i + 2] == '.' ) {
						i += 2;
					}

					if (i < stored_string.length() - 1) {
						if (stored_string[i + 1] == '.'){
							for (int y = i; y < stored_string.length(); y++)
								stored_string[y] = stored_string[y + 1];
							stored_string.pop_back();
							is_true = true;
						}
					}
				}

				// .
				if (stored_string[i] == '.' && i < stored_string.length() - 1)
				{
					if (stored_string[i + 1] == '.' && stored_string[i + 2] != '.') {
						for (int y = i; y < stored_string.length(); y++)
							stored_string[y] = stored_string[y + 1];
						stored_string.pop_back();
						is_true = true;
					}
				}
			}
		} while (is_true);
	}

	void cout_string() {
		cout << stored_string << "ENDL" << endl;
	}

private:
	string stored_string;
	
	

};