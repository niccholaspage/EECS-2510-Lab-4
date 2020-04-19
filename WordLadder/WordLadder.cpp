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

void WordLadder::displayResult(vector<string> sequence)
{
	if (sequence.empty())
	{
		cout << "Word Ladder is empty - No Solution\n";
	}

	cout << "There is one, I promise.\n";
}

bool WordLadder::isWord(string str)
{
	//TODO: Ask if we should use this method or some other way.
	set<string>::iterator it = find(lexicon.begin(), lexicon.end(), str);

int WordLadder::findInVector(vector<string> vec, string str)
{
	vector<string>::iterator it = find(vec.begin(), vec.end(), str);

	if (it != vec.end())
	{
		return distance(vec.begin(), it);
	}
	else
	{
		return -1;
	}
}