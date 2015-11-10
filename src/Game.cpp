/*
 * Game.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include "Game.h"
#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <istream>

using namespace mastermind;
using namespace std;

namespace
{
template<typename T>
void display(ostream& out, const vector<T>& row)
{
	for (auto f : row) {
		string prefix = "";
		string postfix = "";
		if (f == Correct) {
			prefix = GreenPrefix;
			postfix = ResetColor;
		}
		out << prefix << f << postfix;
	}
	out << endl;
}
}

Game::Game() : maxAttempts(10), codeLength(4)
{
}

Game::~Game()
{
}

vector<int> Game::readGuess() {
	char c;
	vector<int> guess;
	while (cin >> c) {
		guess.push_back(atoi(&c));
		if (guess.size() == (unsigned) (codeLength)) break;
	}

	return guess;
}

void Game::play()
{

	Board board(codeLength);

	cout << "Game started, you have " << maxAttempts << " chances!" << endl;

	for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
		cout << "Attempt #" << attempt << ": ";
		vector<char> hint = board.getHint(readGuess());
		display(cout, hint);
		if (board.isCodeCracked(hint)) {
			cout << BoldOn << "Code is correct, you won!!!" << ResetColor << endl;
			return;
		}
	}

	cout << "You lost :(." << "The code is: " << RedPrefix;
	display(cout, board.secretCode());
	cout << ResetColor;
}

void Game::showOpeningScreen()
{
	cout << BoldOn << "WELCOME TO MASTERMIND GAME" << ResetColor << endl;
	cout << endl;
	cout << "In this version, instead of 8 possible colors, 8 integers from 0 to 7 are used." << endl;
	cout << "Instead of black/white pegs as feedback, letter \'C\' and \'M\' are used respectively." << endl;
	cout << endl;
	cout << BoldOn << "How to play:" << ResetColor << endl;
	cout << "1. User needs to guess correctly the 4-digit integer code generated by the game.\n"
			  << "   Each digit is an integer from " << BoldOn << "0 to 7." << ResetColor << "\n"
			  << "2. User is allowed maximum 10 attempts.\n"
			  << "3. Enter the 4-digit guess without space or tab in between, then press \'enter\' to lock it in.\n"
			  << "   Any input that is entered after the 4th digit will be ignored.\n"
			  << "4. Upon pressing \'enter\' the code will be evaluated and the feedback will be displayed, represented by:\n"
			  << "   a. Letter \'C\' for every digit that exists and is in the correct place.\n"
			  << "   b. Letter \'M\' for every digit that exists but is misplaced.\n" << endl;
	cout << endl;
}
