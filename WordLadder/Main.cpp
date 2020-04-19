#include <iostream>
#include "WordLadder.h"
#include "ctime"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		cout << "Not enough arguments provided. Example usage:\n";
		cout << "WordLadder dictionary_file_path first_word last_word\n";

		return 0;
	}

	string dictionaryFilePath = argv[1];
	string firstWord = argv[2];
	string lastWord = argv[3];

	if (firstWord.length() != lastWord.length())
	{
		cout << "The first and final word do not have the same length.\n";

		return 0;
	}

	auto start = clock();

	WordLadder wordLadder(dictionaryFilePath, firstWord.length());

	auto elapsed = clock() - start;

	cout << "Elapsed time: " << elapsed / 1000.0 << " seconds.\n";

	return 0;
}