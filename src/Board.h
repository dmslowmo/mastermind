/*
 * Board.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

#define RED_PREFIX "\033[1;31m"
#define GREEN_PREFIX "\033[1;32m"
#define RESET "\033[0m"
#define BOLD_ON "\033[1;1m"

namespace mastermind {

class Board {
public:
	Board(int codeLength);
	virtual ~Board();
	virtual void generateCode();
	bool isMaxAttempt() const;
	bool isCodeCracked(const std::vector<char>& hint) const;
	std::vector<int> secretCode() const;
	std::vector<char> evaluate(const std::vector<int>& guess) const;
private:
	void initialize();
	std::vector<int> code;
	int codeLength;
};

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';
const char NULLCHAR = '\0';
const int GUESS_DIGIT0 = 0;
const int GUESS_DIGIT1 = 1;
const int GUESS_DIGIT2 = 2;
const int GUESS_DIGIT3 = 3;

} /* namespace Mastermind */

#endif /* BOARD_H_ */
