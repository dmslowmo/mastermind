/*
 * Game.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include<iostream>
#include<cstdlib>
#include<map>
#include "Game.h"

namespace Mastermind {

Game::Game() : maxAttempts(10), codeLength(4){

}

Game::~Game() {

}

void Game::play() {
	std::cout << "Game started, you have " << maxAttempts << " chances!" << std::endl;

	Board board(maxAttempts, codeLength);
	board.initialize();
	std::vector<int> guess;

	for (int i = 0; !board.isMaxAttempt(); i++) {

		std::cout << "Attempt " << i+1 << ": ";
		guess.clear();
		char c;
		while(std::cin >> c) {
			guess.push_back(atoi(&c));
			if (guess.size() == 4) break;
		}

		board.insert(i, guess);
		board.check(i);
		if (board.isCodeCracked()) {
			std::cout << "Code is correct, you won!!!" << std::endl;
			return;
		}
	}

	std::cout << "You lost :(." << "The code is: ";
	board.showCode();
}
} /* namespace Mastermind */
