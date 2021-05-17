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

using namespace std;

int main()
{
	// Populating wordList
	set<string> wordList;
	populateWordlist(wordList);

	// Reading users into scores
	map<string, int> scores;
	readUsers(scores);

	// Output rules for the game
	cout << "------------------ HANGMAN ------------------" << endl;
	cout << "Rules: A random word will be chosen from the system.\n"
		<< "Your job is to guess a letter. If the letter is in the\n"
		<< "word, the blank(s) where the letter is will be filled.\n"
		<< "If the letter is not in the word, the blank(s) will\n"
		<< "remain the same. You have 10 tries. A correct guess\n" 
		<< "doesn't count. Good luck!\n\n";

	// Ask for username and print user info
	cout << "Enter username: ";
	string username;
	cin >> username;
	printUserInfo(username, scores);
	cout << endl;

	// Setting random word and initializing progress to ----------
	string word = getWord(wordList);
	set<char> guesses;
	vector<char> progress;
	for (size_t i = 0; i < word.size(); ++i)
	{
		progress.push_back('-');
	}

	int trial = 10;
	while (trial && !checkWin(word, progress))
	{
		bool correct = updateProgress(progress, getGuess(guesses), word);
		printCurrentGuess(progress);
		cout << endl;

		if (!correct)
		{
			--trial;
		}
	}

	if (trial != 0)
	{
		cout << "You win!" << endl;
		updateScores(username, 10, scores);
	}
	else
	{
		cout << "You lost! Word was " << word << endl;
		updateScores(username, -3, scores);
	}
	cout << endl;
	cout << "Your new score: " << scores[username];

	writeUserList(scores);

	cout << "\n\n";
	system("Pause");
	return 0;
}