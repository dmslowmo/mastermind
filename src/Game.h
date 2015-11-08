/*
 * Game.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>

namespace mastermind {

class Game {
public:
	Game();
	virtual ~Game();
	void play();
	void showOpeningScreen();

private:
	int maxAttempts;
	int codeLength;

	std::vector<int> readGuess();
};

} /* namespace Mastermind */

#endif /* GAME_H_ */
