/*
 * Board.h
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <map>
#include <vector>

namespace Mastermind {

class Board {
public:
	Board(int maxAttempt, int codeLength);
	virtual ~Board();
	void check(int rowIndex);
	void insert(int rowIndex, std::vector<int> guess);
	void initialize();
	bool isMaxAttempt();
	bool isCodeCracked();
	void showCode();

private:
	void generateCode();
	template<typename T> void display(std::vector<T> row);
	bool found(int idx, std::vector<int> skipIndex);
	std::vector<int> code;
	int codeLength;
	int maxAttempts;
	int attemptNo;
	std::map<int, std::vector<int> > guessRows;
	std::map<int, std::vector<char> > feedbackRows;
};

} /* namespace Mastermind */

#endif /* BOARD_H_ */
