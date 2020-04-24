//==============================================================================================
// File: WordLadder.cpp - Word ladder implementation
// c.f.: WordLadder.h
//
// This class implements an algorithm to solve the word ladder game.
// See https://en.wikipedia.org/wiki/Word_ladder for a definition and history.
//
// When an instance of the class is constructed, it loads in words from a
// file path into a dictionary. This dictionary will be used when finding
// neighbors to words. This class can find the minimum word ladder between
// starting and ending words and display the results of a word ladder,
// showing outputting the steps taken between the beginning and ending
// words.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       Apr 22, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <list>

WordLadder::WordLadder(string lexiconFileName, int len)
{
	// The constructor for our word ladder. We need to
	// intialize our lexicon with words from the given
	// lexicon file name. We use the passed in length
	// parameter to optimize the lexicon so that it
	// only contains words with the same length.
	//
	ifstream inputStream; // We need an input stream to read our lexicon file

	// Open the input stream with the lexicon file name as our path.
	inputStream.open(lexiconFileName);

	if (inputStream.fail()) // If the input straem fails to open,
	{
		cout << "Unable to open lexicon file.\n"; // we print a message saying we could not open the lexicon file,

		// and exit our application, as there is nothing we can do without a valid lexicon.
		// NOTE: If this implementation would be used as part of a different program, it would
		// be much better if on failure, we throw an exception or somehow notify the caller
		// that an error occurred - blindly exiting the program is usually not a good look
		// for a constructor like this!
		//
		exit(0);
	}

	string word; // We will use this to hold the word we are currently reading from our lexicon file.

	// While we successfully read another word from the input stream into our word variable...
	while (inputStream >> word)
	{
		if (word.length() == len)	// if the word's length equals the length of the words that will be in our ladder,
		{
			lexicon.insert(word);	// we insert the word into our lexicon.
		}
	}
}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	vector<string> ladder;

	if (!isWord(start) || !isWord(end))
	{
		return ladder;
	}

	vector<string> seenWords;
	vector<string> predecessors;
	list<string> queue;

	queue.push_back(start);
	seenWords.push_back(start);
	predecessors.push_back("");

	while (!queue.empty())
	{
		string qFront = queue.front();

		queue.pop_front();

		set<string> neighbors = getNeighbors(qFront);

		for (const string& s : neighbors)
		{
			if (findInVector(seenWords, s) == -1)
			{
				if (s == end)
				{
					seenWords.push_back(s);
					predecessors.push_back(qFront);

					int sIndex = findInVector(seenWords, s);

					string& word = predecessors[sIndex];

					ladder.push_back(s);

					while (word != start)
					{
						ladder.insert(ladder.begin(), word);

						sIndex = findInVector(seenWords, word);

						word = predecessors[sIndex];
					}

					ladder.insert(ladder.begin(), start);

					return ladder;
				}
				else
				{
					seenWords.push_back(s);
					predecessors.push_back(qFront);

					queue.push_back(s);
				}
			}
			
		}
	}

	return ladder;
}

void WordLadder::displayResult(vector<string> sequence)
{
	if (sequence.empty())
	{
		cout << "Word Ladder is empty - No Solution\n";

		return;
	}

	cout << "A Shortest Word Ladder (" << sequence.size() - 1 << " steps) is: ";

	for (auto iterator = sequence.begin(); iterator != sequence.end(); iterator++)
	{
		cout << *iterator;

		if (iterator != sequence.end())
		{
			cout << " ";
		}
	}

	cout << endl;
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