/*
 * Game.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef GAME_H_
#define GAME_H_

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
};

} /* namespace Mastermind */

#endif /* GAME_H_ */
