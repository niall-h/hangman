/*
	Htet, Niall
	Meng, Ramy
	Park, Juyoung

	October 11, 2020

	CS A250
	Hangman
*/

#include "Game.h"
#include <fstream>
#include <utility>
#include <iostream>
#include <ctime>

using namespace std;

// Reads the words from file called "wordslist.txt"
// Stores the words in the set
void populateWordlist(set<string>& wordList)
{
	ifstream wordFile("wordslist.txt");
	if (wordFile.is_open())
	{
		string word;
		while (getline(wordFile, word))
		{
			wordList.insert(word);
		}
		wordFile.close();
	}
}


// Reads saved user data from file called "scoreslist.txt"
// Stores data in map called scores
// map has (username, score) pairs
//
// scoreslist.txt format is as follows
// numberOfRecords
// user1 score1
// user2 score2
// user3 score3
void readUsers(map<string, int>& scores)
{
	ifstream scoreFile("scoreslist.txt");
	if (scoreFile.is_open())
	{
		int numberOfRecords;
		scoreFile >> numberOfRecords;
		scoreFile.ignore();

		string username;
		int score;
		while (scoreFile >> username)
		{
			scoreFile.ignore();
			scoreFile >> score;
			scoreFile.ignore();
			scores.insert(make_pair(username, score));
		}
		scoreFile.close();
	}
}

// Returns a word from the word set.
// Generate a random number
// Iterate through the set using an iterator and return that word.
string getWord(const set<string>& words)
{
	srand(static_cast<unsigned int>(time(NULL)));
	unsigned int randomNum = 1 + rand() % words.size();
	set<string>::const_iterator iter = words.cbegin();

	while (randomNum)
	{
		++iter;
		--randomNum;
	}

	return *iter;
}


//  Asks the user to guess a character. Keeps asking until the user has
// given a character they haven't guessed already
//
// Adds the guess to guesses
// Returns the character
char getGuess(set<char>& guesses)
{
	cout << "Guess a letter: ";
	
	char guess;
	cin >> guess;
	
	size_t initialSize = guesses.size();
	guesses.insert(guess);

	while (initialSize == guesses.size())
	{
		cout << "You already guessed that letter" << endl;
		cout << "Guess a leter: ";
		cin >> guess;
		guesses.insert(guess);
	}
	return guess;
}


// Prints username and user's current score
// If the user doesn't exist, print 0 as the current score
//  Use an iterator to iterate through the map.
//
// Prints in the form
// User <username>
// Score <score>
void printUserInfo(const string& username, const map<string, int>& scores)
{
	map<string, int>::const_iterator const_iter = scores.cbegin();
	map<string, int>::const_iterator const_endFlag = scores.cend();
	bool found = false;
	int score = 0;

	while (const_iter != const_endFlag && !found)
	{
		if (const_iter->first == username)
		{
			found = true;
			score = const_iter->second;
		}
		++const_iter;
	}

	cout << "User " << username << endl;
	cout << "Score " << score << endl;
}


// Updates the current guess
// If the letter appears in the word, replace the '-'
// with the letter
//
// Returns true if the letter was in the word; false if the letter was
// not in the word
//
// Use an iterator to iterate and modify the vector
// Use an iterator to iterate through the string
bool updateProgress(vector<char>& currentGuesses, char letter,
	const string& word)
{
	vector<char>::iterator vIter = currentGuesses.begin();
	string::const_iterator const_sIter = word.cbegin();
	string::const_iterator const_sEndFlag = word.end();
	bool found = false;

	while (const_sIter != const_sEndFlag)
	{
		if (letter == *const_sIter)
		{
			*vIter = letter;
			found = true;
		}
		++const_sIter;
		++vIter;
	}
	return found;
}


// Adds or updates the score of username
//
// If the username exists in the map, add score to the score.  To
// subtract points, pass a negative number as score.
//
// If the username does not exist, add the username and set the score
// to score
void updateScores(const string& username, int score,
	map<string, int>& scores)
{
	map<string, int>::iterator iter = scores.begin();
	map<string, int>::iterator endFlag = scores.end();
	bool found = false;

	while (iter != endFlag && !found)
	{
		if (iter->first == username)
		{
			found = true;
			iter->second += score;
		}
		++iter;
	}
	if (!found)
	{
		scores.insert(make_pair(username, score));
	}
}


// Displays the current guess with letters that have been guessed
// filled in and letters that have not been guessed represented by '-'
//
// User an iterator to iterate through the vector
void printCurrentGuess(const vector<char>& currentGuess)
{
	vector<char>::const_iterator const_iter = currentGuess.cbegin();
	vector<char>::const_iterator const_endFlag = currentGuess.cend();

	while (const_iter != const_endFlag)
	{
		cout << *const_iter;
		++const_iter;
	}
}


// Returns true if every letter in the vector has been guessed
// Returns false otherwise
bool checkWin(const string& word, const vector<char>& currentGuess)
{
	string guess = "";
	for (size_t i = 0; i < currentGuess.size(); ++i)
	{
		guess += currentGuess.at(i);
	}
	if (word == guess)
	{
		return true;
	}
	return false;
}


// Writes the user scores to a file called scoreslist.txt
// Use an iterator to iterate through the vector
//
// scoreslist.txt format is as follows
// numberOfRecords
// user1 score1
// user2 score2
// user3 score3
void writeUserList(const map<string, int>& scores)
{
	ofstream scoresList("scoreslist.txt");
	if (scoresList.is_open())
	{
		scoresList << scores.size() << endl;
		map<string, int>::const_iterator const_iter = scores.cbegin();
		map<string, int>::const_iterator const_endFlag = scores.cend();

		while (const_iter != const_endFlag)
		{
			scoresList << const_iter->first << " " << const_iter->second << endl;
			++const_iter;
		}
		scoresList.close();
	}
}