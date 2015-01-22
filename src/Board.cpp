/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include<cstdlib>
#include<chrono>
#include "Board.h"

namespace {

bool found(int idx, const std::vector<int>& skipIndex) {
	for (auto i : skipIndex) {
		if (i == idx)
			return true;
	}
	return false;
}

}

namespace mastermind {

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';

Board::Board(int maxAttempts, int codeLength) :
		codeLength(codeLength), maxAttempts(maxAttempts), attemptNo(0) {
	initialize();
}

Board::~Board() {
}

void Board::check(int rowIndex) {
	attemptNo++;
	std::vector<int> skipIndex;
	std::vector<int> guess = guessRows.at(rowIndex);
	std::vector<char> feedback;

	for(unsigned int i = 0; i < code.size(); i++) {
		if (code.at(i) == guess.at(i)) {
			feedback.insert(feedback.begin(), CORRECT);
			skipIndex.push_back(i);
		}
		else {
			for (unsigned int j = 0; j < code.size(); j++) {
				if (!found(j, skipIndex) && code.at(i) == guess.at(j)) {
					feedback.push_back(MISPLACED);
					skipIndex.push_back(j);
					break;
				}
			}
		}
		feedbackRows[rowIndex] = feedback;
	}
	std::cout << "\t";
	display(std::cout, feedback);
}

void Board::insert(int rowIndex, const std::vector<int>& guess) {
	guessRows[rowIndex] = guess;
}

void Board::initialize() {
	code.clear();
	generateCode();
	guessRows.clear();
	feedbackRows.clear();
	attemptNo = 0;
}

bool Board::isMaxAttempt() const {
	return attemptNo == maxAttempts;
}

bool Board::isCodeCracked() const {
	std::vector<char> feedback = feedbackRows.at(attemptNo-1);

	if (feedback.size() < code.size()) {
		return false;
	}
	else {
		for (auto f : feedback) {
			if (f == MISPLACED) {
				return false;
			}
		}
	}
	return true;
}

void Board::showCode() const {
	display(std::cout, code);
}

void Board::generateCode() {
	for (int i = 0; i < codeLength; i++) {
		unsigned seed =
				std::chrono::system_clock::now().time_since_epoch().count();
		srand(seed);
		code.push_back(rand()%(codeLength*2));
	}
//	display(code);
}

template<typename T>
void Board::display(std::ostream& out, const std::vector<T>& row) const {
	for (auto f : row) {
		out << f;
	}
	out << std::endl;
}

} /* namespace Mastermind */
