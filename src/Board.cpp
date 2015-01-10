/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include<iostream>
#include<cstdlib>
#include<chrono>
#include "Board.h"

namespace Mastermind {

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';

Board::Board(int maxAttempts, int codeLength) :
		codeLength(codeLength), maxAttempts(maxAttempts), attemptNo(0) {
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
	display(feedback);
}

bool Board::found(int idx, std::vector<int> skipIndex) {
	for (auto i : skipIndex) {
		if (i == idx)
			return true;
	}
	return false;
}

void Board::insert(int rowIndex, std::vector<int> guess) {
	guessRows[rowIndex] = guess;
}

void Board::initialize() {
	code.clear();
	generateCode();
	guessRows.clear();
	feedbackRows.clear();
	attemptNo = 0;
}

bool Board::isMaxAttempt() {
	return attemptNo == maxAttempts;
}

bool Board::isCodeCracked() {
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

void Board::showCode() {
	display(code);
}

void Board::generateCode() {
	for (int i = 0; i < codeLength; i++) {
		unsigned seed =
				std::chrono::system_clock::now().time_since_epoch().count();
		srand(seed);
		code.push_back(rand()%(codeLength*2));
	}
	display(code);
	std::cout << std::endl;
}

template<typename T>
void Board::display(std::vector<T> row) {
	for (auto f : row) {
		std::cout << f;
	}
	std::cout << std::endl;
}

} /* namespace Mastermind */
