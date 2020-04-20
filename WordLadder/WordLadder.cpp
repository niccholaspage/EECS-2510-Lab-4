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
	// This method checks to see if the given string
	// is a word inside of the WordLadder's dictionary.
	// If it is, true is returned.
	//
	// We utilize set::find, which starts from the beginning
	// of the set and going to the end, looking for the
	// given string. If set::find is able to find the
	// string, it will return an iterator located at the
	// index of the given string inside of the dictionary
	// set.
	set<string>::iterator it = lexicon.find(str);

	// At this point, our iterator will either point at
	// the element in the dictionary, our string, or
	// the end of the set. If it points to the end of the
	// set, we were not able to find the given word,
	// so this will return false. Otherwise, it will
	// return true, as we found the word.
	return it != lexicon.end();
}

int WordLadder::findInVector(vector<string> vec, string str)
{
	// This method tries to find the given string inside of
	// the given vector. If it is found in the vector, the
	// index of the string is returned. Otherwise, -1 is returned.
	//
	// We utilize std::find and start from the beginning
	// of the vector and go to the end, looking for the
	// given string. If std::find is able to find the
	// string, it will return an iterator located at the
	// index of the given string inside of the vector.
	vector<string>::iterator it = find(vec.begin(), vec.end(), str);

	// At this point, our iterator will either point at
	// the element in the vector, our string, or
	// the end of the set. If it points to the end of the
	// vector, we were not able to find the given word,
	// so we return -1. Otherwise, it will
	// return true, as we found the word.
	if (it != vec.end())
	{
		return distance(vec.begin(), it);
	}
	else
	{
		return -1;
	}
}

set<string> WordLadder::getNeighbors(string word)
{
	set<string> neighbors;

	for (const string& dictWord : lexicon)
	{
		if (getHammingDistance(word, dictWord) == 1)
		{
			neighbors.insert(dictWord);
		}
	}

	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	if (str1.length() != str2.length())
	{
		return -1;
	}

	int hammingDistance = 0;

	int stringLength = str1.length();

	for (int i = 0; i < stringLength; i++)
	{
		if (str1[i] != str2[i])
		{
			hammingDistance++;
		}
	}


	return hammingDistance;
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	if (sequence.size() < 2)
	{
		return false;
	}

	for (int i = 0; i < sequence.size() - 1; i++)
	{
		string& word = sequence[i];

		string& nextWord = sequence[i + 1];

		if (getHammingDistance(word, nextWord) != 1)
		{
			return false;
		}
	}

	return true;
}

int WordLadder::getWordCount()
{
	return lexicon.size();
}