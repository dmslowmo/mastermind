/*
 * Board.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <string>

namespace mastermind {

using Code = std::vector<int>;
using Hint = std::vector<char>;

class Board {
public:
	Board(int codeLength);
	virtual ~Board();
	virtual void generateCode();
	bool isMaxAttempt() const;
	bool isCodeCracked(const Hint& hint) const;
	Code secretCode() const;
	Hint getHint(const Code& guess);
private:
	void initialize();
	Code secretCode_;
	int codeLength;
};

constexpr char CORRECT = 'C';
constexpr char MISPLACED = 'M';
constexpr auto RED_PREFIX = "\033[1;31m";
constexpr auto GREEN_PREFIX = "\033[1;32m";
constexpr auto RESET = "\033[0m";
constexpr auto BOLD_ON = "\033[1;1m";

} /* namespace mastermind */

#endif /* BOARD_H_ */
