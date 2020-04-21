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
	// This is the entry point of the application, so we check
	// our arguments to make sure they are correct, and attempt
	// to get the word ladder between the starting and ending
	// words the user provides, using the dictionary provided
	// in the arguments.
	//
	if (argc != 4) // If our argument count isn't exactly four,
	{
		// Tell the user the wrong number of arguments was provided,
		// and give them an example usage of the program so that
		// they know how to use it!
		//
		cout << "Wrong number of arguments provided. Example usage:\n";
		cout << "WordLadder dictionary_file_path first_word last_word\n";

		return 0; // There is nothing left to do, so we can return here, ending the program.
	}

	string dictionaryFilePath = argv[1];	// Get the file path to the dictionary
	string firstWord = argv[2];				// Get the word we are going to be starting at
	string lastWord = argv[3];				// Get the word we will be ending at

	if (firstWord.length() != lastWord.length()) // If the words aren't equal the same length,
	{
		// we tell the user that they don't have the same length.
		// We can't go from the first word to the end word changing
		// one letter at a time if they aren't the same length, as we
		// are not allowed to add or remove characters!
		//
		cout << "The first and final word do not have the same length.\n";

		return 0; // We can't do anything with these word inputs, so we return, ending the program.
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