/*
 * Game.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include <Board.h>
#include <Game.h>
#include <cstdlib>
#include <iostream>
#include <istream>
#include <vector>

namespace mastermind {

Game::Game() : maxAttempts(10), codeLength(4)
{

}

Game::~Game()
{

}

void Game::play()
{

	Board board(maxAttempts, codeLength);
	int maxAttempt = 10;

	std::cout << "Game started, you have " << maxAttempts << " chances!" << std::endl;

	for (int attempt = 1; attempt <= maxAttempt; attempt++)
	{
		std::cout << "Attempt " << attempt << ": ";
		std::vector<int> guess;
		char c;
		while(std::cin >> c)
		{
			guess.push_back(atoi(&c));
			if (guess.size() == (unsigned) codeLength) break;
		}

		if (board.isCodeCracked(guess))
		{
			std::cout << "Code is correct, you won!!!" << std::endl;
			return;
		}
		guess.clear();
	}

	std::cout << "You lost :(." << "The code is: ";
	board.showCode();
}

void Game::showOpeningScreen()
{
	std::cout << "WELCOME TO MASTERMIND GAME" << std::endl;
	std::cout << std::endl;
	std::cout << "In this version, instead of 8 possible colors, 8 integers from 0 to 7 are used." << std::endl;
	std::cout << "Instead of black/white pegs as feedback, letter \'C\' and \'M\' are used respectively." << std::endl;
	std::cout << std::endl;
	std::cout << "How to play:" << std::endl;
	std::cout << "1. User needs to guess correctly the 4-digit integer code generated by the game.\n"
			  << "   Each digit is an integer from 0 to 7.\n"
			  << "2. User is allowed maximum 10 attempts.\n"
			  << "3. Enter the 4-digit guess without space or tab in between, then press \'enter\' to lock it in.\n"
			  << "   Any input that is entered after the 4th input will be ignored.\n"
			  << "4. Upon pressing \'enter\' the code will be evaluated and the feedback will be displayed, represented by:\n"
			  << "   a. Letter \'C\' for every digit that exists and is in the correct place.\n"
			  << "   b. Letter \'M\' for every digit that exists but is misplaced.\n" << std::endl;
	std::cout << std::endl;
}

} /* namespace Mastermind */
