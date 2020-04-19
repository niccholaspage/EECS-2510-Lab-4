#include "WordLadder.h"
#include <fstream>
#include <iostream>

WordLadder::WordLadder(string lexiconFileName, int len)
{
	ifstream inputStream;

	inputStream.open(lexiconFileName);

	if (inputStream.fail())
	{
		cout << "Unable to open dictionary file.\n";

		exit(0);
	}

	string word;

	while (inputStream >> word)
	{
		if (word.length() == len)
		{
			lexicon.insert(word);
		}
	}

}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	return vector<string>();
}