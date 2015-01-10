/*
 * Game.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"

namespace Mastermind {

class Game {
public:
	Game();
	virtual ~Game();
	void play();

private:
	int maxAttempts;
	int codeLength;
};

} /* namespace Mastermind */

#endif /* GAME_H_ */
