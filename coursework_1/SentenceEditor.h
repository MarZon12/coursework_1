#pragma once
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class SentenceEditor
{
public:
	SentenceEditor(int word_max_length = 10) {
		word_counter = 0;
		this->word_max_length = word_max_length;

		words = nullptr;
	}
	~SentenceEditor() {
		if (words != nullptr)
		{
			for (int i = 0; i < word_max_length; i++)
				delete[] words[i];
			delete words;
		}
	}

	void sentence_reader() {
		char* word_buffer = new char[word_max_length + 1]{};
		
		do
		{
			cin.width(word_max_length + 1);

			cin >> word_buffer;

			for (int i = 0; i < word_max_length + 1; i++)
			{
				cout << word_buffer[i];
			}
			cout << endl;
			cout << word_buffer << endl;
		} while (true);

		delete[] word_buffer;
	}

private:
	int word_counter;
	int word_max_length;

	char** words;

	void add_new_word() {
		if (words == nullptr)
			cout << "NEW ONE" << endl;
		char** words_copy;

	}
};

