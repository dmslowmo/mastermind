/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include<cstdlib>
#include<chrono>
#include "Board.h"

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';

namespace {

int found(int idx, const std::vector<int>& skipIndex) {
	for (unsigned int i = 0; i < skipIndex.size(); ++i) {
		if (idx == skipIndex.at(i))
			return i;
	}
	return -1;
}

void handleCorrectInsertion(int codeIndex, std::vector<int>& skipIndex, std::vector<char>& feedback) {
	int inSkip = found(codeIndex, skipIndex);
	if (inSkip != -1) {
		feedback.erase(feedback.end() - 1);
		skipIndex.erase(skipIndex.begin() + inSkip);
	}
	feedback.insert(feedback.begin(), CORRECT);
	skipIndex.push_back(codeIndex);
}

void handleMisplacedInsertion(int codeIndex, const std::vector<int>& code,
		const std::vector<int>& guess, std::vector<int>& skipIndex,
		std::vector<char>& feedback) {
	for (unsigned int j = 0; j < code.size(); j++) {
		if ((found(j, skipIndex) == -1)
				&& (code.at(codeIndex) == guess.at(j))) {
			feedback.push_back(MISPLACED);
			skipIndex.push_back(j);
			break;
		}
	}
}
}

namespace mastermind {

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
			handleCorrectInsertion(i, skipIndex, feedback);
		}
		else {
            handleMisplacedInsertion(i, code, guess, skipIndex, feedback);
		}
		feedbackRows[rowIndex] = feedback;
	}
	std::cout << "\t\t";
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
//	code = {7,7,7,0};
//	code = {2,7,2,2};
//	code = {6,2,6,2};
//	display(std::cout, code);
}

template<typename T>
void Board::display(std::ostream& out, const std::vector<T>& row) const {
	for (auto f : row) {
		out << f;
	}
	out << std::endl;
}

} /* namespace Mastermind */
