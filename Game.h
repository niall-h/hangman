#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <set>
#include <string>


// Reads the words from file called "wordslist.txt"
// Stores the words in the set
void populateWordlist(std::set<std::string>& wordList);


// Reads saved user data from file called "scoreslist.txt"
// Stores data in map called scores
// map has (username, score) pairs
//
// scoreslist.txt format is as follows
// numberOfRecords
// user1 score1
// user2 score2
// user3 score3
void readUsers(std::map<std::string, int>& scores);


// Returns a word from the word set.
// Generate a random number
// Iterate through the set using an iterator and return that word.
std::string getWord(const std::set<std::string>& words);


//  Asks the user to guess a character. Keeps asking until the user has
// given a character they haven't guessed already
//
// Adds the guess to guesses
// Returns the character
char getGuess(std::set<char>& guesses);


// Prints username and user's current score
// If the user doesn't exist, print 0 as the current score
//  Use an iterator to iterate through the map.
//
// Prints in the form
// User <username>
// Score <score>
void printUserInfo(const std::string& username,
		   const std::map<std::string, int>& scores);


// Updates the current guess
// If the letter appears in the word, replace the '-'
// with the letter
//
// Returns true if the letter was in the word; false if the letter was
// not in the word
//
// Use an iterator to iterate and modify the vector
// Use an iterator to iterate through the string
bool updateProgress(std::vector<char>& currentGuesses, char letter,
		    const std::string& word);


// Adds or updates the score of username
//
// If the username exists in the map, add score to the score.  To
// subtract points, pass a negative number as score.
//
// If the username does not exist, add the username and set the score
// to score
void updateScores(const std::string& username, int score,
		  std::map<std::string, int>& scores);


// Displays the current guess with letters that have been guessed
// filled in and letters that have not been guessed represented by '-'
//
// User an iterator to iterate through the vector
void printCurrentGuess(const std::vector<char>& currentGuess);


// Returns true if every letter in the vector has been guessed
// Returns false otherwise
bool checkWin(const std::string& word, const std::vector<char>& currentGuess);


// Writes the user scores to a file called scoreslist.txt
// Use an iterator to iterate through the vector
//
// scoreslist.txt format is as follows
// numberOfRecords
// user1 score1
// user2 score2
// user3 score3
void writeUserList(const std::map<std::string, int>& scores);



#endif
