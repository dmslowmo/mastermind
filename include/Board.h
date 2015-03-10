/*
 * Board.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <map>
#include <vector>

namespace mastermind {

class Board {
public:
	Board(int codeLength);
	virtual ~Board();
	void generateCode();
	bool isMaxAttempt() const;
	bool isCodeCracked(const std::vector<int>& guess) const;
	void showCode() const;

private:
	void initialize();
	void check(const std::vector<int>& code,
			const std::vector<int>& guess) const;
	template<typename T> void display(std::ostream& out, const std::vector<T>& row) const;
	std::vector<int> code;
	int codeLength;
};

} /* namespace Mastermind */

#endif /* BOARD_H_ */
