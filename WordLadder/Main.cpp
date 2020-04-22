//==============================================================================================
// Main.cpp - Word Ladder program
//
// This program implements an algorithm used to solve the word ladder game, which is a puzzle
// game that begins with two words. The puzzle is solved by finding a ladder or chain of words
// linking the two words together, where adjacent words in the chain can only differ by one
// letter.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       Apr 22, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#include <iostream>
#include "WordLadder.h"

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

	// We now construct a WordLadder, passing in the file path
	// to the dictionary as well as the length of the first and
	// last words. If the constructor has issues opening our
	// dictionary file, the program will exit, so we know that
	// a WordLadder successfully being constructed means that we
	// can continue and find our minimum word ladder.
	//
	WordLadder wordLadder(dictionaryFilePath, firstWord.length());

	// We call convertToUppercase on both our first and last
	// words. As seen in the comments for this method, it does
	// not return a string -- it instead takes a reference
	// to a string, and converts each character to an uppercase
	// version of the character in place, so that firstWord
	// and lastWord will both be fully uppercase. This is done
	// because every word in the dictionary file is uppercase,
	// and it makes it easier for us to check characters if they
	// are all of uniform casing.
	//
	convertToUppercase(firstWord);
	convertToUppercase(lastWord);

	// We now retrieve the minimum word ladder, going from our first word
	// to our last word. This will cause the WordLadder class to go loop
	// the neighbors for the first word, checking them to find a connection
	// that leads to the last word. If no connection can be found, an empty
	// vector ends up getting returned.
	//
	vector<string> minLadder = wordLadder.getMinLadder(firstWord, lastWord);

	// We now display our minimum word ladder. If the vector ends up
	// being empty, the output will state that no solution was found.
	// Otherwise, the shortest word ladder will be printed, with the number
	// of steps required to get to the last word, and the list of each word
	// we traversed through to get to the final word.
	//
	wordLadder.displayResult(minLadder);

	return 0; // We return 0, as we have done all we needed to do!
}