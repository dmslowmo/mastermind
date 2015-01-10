/*
 * main.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include<iostream>
#include "Board.h"
#include "Game.h"

using namespace mastermind;

int main() {

	bool playAgain = true;
	char response;
	Game g;
	g.showOpeningScreen();
	while (playAgain) {
		g.play();
		std::cout << "Play again? (Y to continue, or other keys to quit): ";
		std::cin >> response;
		playAgain = (response == 'Y' || response == 'y');
		std::cout << std::endl;
	}

	std::cout << "Thanks for playing. Bye!" << std::endl;

	return 0;
}
