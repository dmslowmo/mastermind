/*
 * Game.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>

enum class ColorCode;

namespace mastermind {

class Game {
public:
	Game();
	virtual ~Game();
	void play();
	void showOpeningScreen();
private:
	std::vector<int> readGuess();
private:
	int maxAttempts;
	int codeLength;
};

constexpr auto BoldRedPrefix   = "\033[1;31m";
constexpr auto BoldGreenPrefix = "\033[1;32m";
constexpr auto ResetColor  = "\033[0m";
constexpr auto BoldOn      = "\033[1;1m";

} /* namespace Mastermind */

#endif /* GAME_H_ */
