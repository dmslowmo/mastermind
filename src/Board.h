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
	std::vector<char> getHint(const std::vector<int>& guess);
private:
	void initialize();
	std::vector<int> secretCode_;
	int codeLength;
};

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';

} /* namespace Mastermind */

#endif /* BOARD_H_ */
