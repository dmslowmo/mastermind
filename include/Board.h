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
	Board(int maxAttempt, int codeLength);
	virtual ~Board();
	std::vector<int> generateCode();
	void insert(int rowIndex, const std::vector<int>& guess);
	bool isMaxAttempt() const;
	bool isCodeCracked(const std::vector<int>& guess, const std::vector<int>& code) const;
	void showCode() const;

private:
	void initialize();
	void check(const std::vector<int>& code,
			const std::vector<int>& guess) const;
	template<typename T> void display(std::ostream& out, const std::vector<T>& row) const;
	std::vector<int> code;
	int codeLength;
	std::map<int, std::vector<int> > guessRows;
};

} /* namespace Mastermind */

#endif /* BOARD_H_ */
