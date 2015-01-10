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

namespace mastermind {

class Board {
public:
	Board(int maxAttempt, int codeLength);
	virtual ~Board();
	void check(int rowIndex);
	void insert(int rowIndex, std::vector<int> guess);
	bool isMaxAttempt() const;
	bool isCodeCracked() const;
	void showCode() const;

private:
	void initialize();
	void generateCode();
	template<typename T> void display(const std::vector<T>& row) const;
	bool found(int idx, const std::vector<int>& skipIndex) const;
	std::vector<int> code;
	int codeLength;
	int maxAttempts;
	int attemptNo;
	std::map<int, std::vector<int> > guessRows;
	std::map<int, std::vector<char> > feedbackRows;
};

} /* namespace Mastermind */

#endif /* BOARD_H_ */
