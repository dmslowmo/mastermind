/*
 * main.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include <iostream>
#include "Board.h"
#include "Game.h"

using namespace mastermind;
using namespace std;

int main()
{

	bool playAgain = true;
	char response;
	Game g;

	g.showOpeningScreen();
	while (playAgain) {
		g.play();
		cout << "Play again? (Y to continue, or other keys to quit): ";
		cin >> response;
		playAgain = (response == 'Y' || response == 'y');
		cout << endl;
	}

	cout << "Thanks for playing. Bye!" << endl;

	return 0;
}
