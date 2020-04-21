#include <iostream>
#include "WordLadder.h"
#include "ctime"

using namespace std;

void convertToUppercase(string& str)
{
	//This method simply takes a given string
	// and converts its characters to uppercase
	// versions, if possible. It takes a string
	// reference, and updates the characters of
	// the reference instead of returning a new
	// string, for slightly more efficient code.
	//
	for (unsigned int i = 0; i < str.length(); i++) // loop through each element of the string...
	{
		str[i] = toupper(str[i]); // and  set each character to the uppercase version of itself.
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Wrong number of arguments provided. Example usage:\n";
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

	convertToUppercase(firstWord);
	convertToUppercase(lastWord);

	vector<string> minLadder = wordLadder.getMinLadder(firstWord, lastWord);

	wordLadder.displayResult(minLadder);

	auto elapsed = clock() - start;

	cout << "Elapsed time: " << elapsed / 1000.0 << " seconds.\n";

	return 0;
}