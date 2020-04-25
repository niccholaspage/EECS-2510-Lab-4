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
	// This method simply takes a word ladder sequence,
	// which is just a vector of strings, and displays
	// the steps taken to transition from the first word
	// in the ladder to the last word, as well as
	// outputting the number of steps needed to reach
	// the final word.
	//
	if (sequence.empty()) // If our sequence is empty,
	{
		// we output that there was no solution. This means that
		// with the loaded dicionary, there is no way to get between
		// the beginning word to the ending word, changing only
		// a single character at a time.
		//
		cout << "Word Ladder is empty - No Solution\n";

		return; // We return, as we've already displayed that our ladder was empty.
	}

	// Since we have a non-empty sequence, we output the required text
	// from our lab document, simply stating what the shortest word ladder is,
	// as well as the steps it takes to get there, which is simply the size of the
	// sequence minus one, as the beginning word does NOT count as a step.
	cout << "A Shortest Word Ladder (" << sequence.size() - 1 << " steps) is: ";

	// We now need to loop through every item in our sequence so we can print
	// out each word. While we could use a simple for loop with an index,
	// this iterator style of looping seems more versatile to me and can be
	// used with more container types, like a set. We simply start
	// our iterator at the beginning of the sequence, and increment our iterator
	// after every pass through an item. Once the iterator has reached the end,
	// we are finished.
	//
	for (auto iterator = sequence.begin(); iterator != sequence.end(); iterator++)
	{
		// We simply dereference out iterator, which will give us the item in the
		// sequence at the iterator's position, then output it.
		cout << *iterator;

		// if we haven't reached the last item of our sequence yet,
		if (iterator != sequence.end() - 1)
		{
			cout << " "; // we display a space so that the sequence is properly spaced out.
		}
	}

	cout << endl; // Finally, we finish off with a new line since we've displayed our entire sequence.
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
	// This method finds the neighbors of the given
	// word. Neighbors are found by looping through
	// each	word inside of the lexicon, checking if
	// they are a neighbor of the given word,
	// and adding them to a set of neighbors if so.
	//
	set<string> neighbors; // We start with an empty set of neighbors

	// We loop through every word inside of our
	// lexicon. While we could have used a for loop
	// with just the string type instead of a constant
	// string reference, that would have been incredibly
	// inefficient, as that would result in a useless string
	// copy for EACH pass of the for loop.
	for (const string& lexiconWord : lexicon)
	{
		// We check if the hamming distance between the
		// given word and our lexicon's word is one.
		// If it is, then the lexicon word only differs
		// by a single character from the given word,
		// so it IS a neighbor.
		if (getHammingDistance(word, lexiconWord) == 1)
		{
			// Since we know the lexicon word is a neighbor,
			// we insert it into our set.
			neighbors.insert(lexiconWord);
		}
	}

	// Now that we've determined all of our neighbors, we simply return them.
	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	// This method takes the two given words, and calculates
	// their hamming distance (see https://en.wikipedia.org/wiki/Hamming_distance)
	// by comparing them character by character, finally returning
	// it to the caller of the method.
	//
	// If the length of the two strings is not the same,
	if (str1.length() != str2.length())
	{
		// we return -1, as two string strings can only have
		// a hamming distance if they are the same length.
		return -1;
	}

	// We use an unsigned integer, as hamming distances can only be positive,
	// to keep of track of the hamming distance as we loop through the characters.
	unsigned int hammingDistance = 0;

	// We get the length of our initial string, so that we don't have to repeatedly
	// call the length method during our loop, as our string length won't change.
	int stringLength = str1.length();

	for (int i = 0; i < stringLength; i++) // We loop through every index from zero to the stringLength - 1...
	{
		if (str1[i] != str2[i])	// If the character at str1[i] is NOT the same as the one at str2[i],
		{
			hammingDistance++;	// we increment the hamming distance by 1 since the characters differ.
		}
	}


	return hammingDistance; // At this point, we've calculated our hamming distance so we just return it.
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	// This method checks the given vector
	// of strings and determines if it makes
	// up a valid word ladder. A word ladder
	// is defined as every pair of adjacent
	// words having a hamming distance of 1.
	//
	// If we have less than two words in our sequence,
	// by definition we do not have a word ladder,
	// as there are no pairs of adjacent words.
	if (sequence.size() < 2)
	{
		return false;
	}

	// To check if the sequence is a valid word ladder,
	// we need to check if adjacent words have a hamming
	// distance of one. To do this, we loop through
	// every point in the sequence, except for the one
	// representing the last item in the sequence, and check
	// each item's hamming distance with the item right after
	// it.
	for (auto iterator = sequence.begin(); iterator != sequence.end() - 1; iterator++)
	{
		string& word = *iterator;			// We first get the word located at our position in the iterator,

		string& nextWord = *(iterator + 1);	// as well as the word right after the word at our iterator.

		// We now get the hamming distance between our two words.
		// If it is not one, then this sequence is NOT a word ladder,
		if (getHammingDistance(word, nextWord) != 1)
		{
			return false; // so we immediately return false.
		}
	}

	// At this point, we know all adjacent words have a
	// hamming distance of one, so we return true, as
	// we know that we have a valid word ladder.
	return true;
}

int WordLadder::getWordCount()
{
	// This method simply returns the total number of words
	// in the lexicon, which can be used to ensure that words
	// were properly loaded into the dictionary.
	//
	// We use set's size method to return the number of items
	// in the set, which is the number of words in the lexicon.
	return lexicon.size();
}