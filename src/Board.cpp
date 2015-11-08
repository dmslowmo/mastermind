/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include "Board.h"
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <map>

//FEEDBACK codes
const char CORRECT = 'C';
const char MISPLACED = 'M';
const char NULLCHAR = '\0';
const int GUESS_DIGIT0 = 0;
const int GUESS_DIGIT1 = 1;
const int GUESS_DIGIT2 = 2;
const int GUESS_DIGIT3 = 3;

namespace {

std::map<int, char> feedbackAllDigits;
std::vector<char> feedback;

template<typename T>
void display(std::ostream& out, const std::vector<T>& row)
{
	for (auto f : row) {
		std::string prefix = "";
		std::string postfix = "";
		if (f == CORRECT) {
			prefix = GREEN_PREFIX;
			postfix = RESET;
		}
		out << prefix << f << postfix;
	}
	out << std::endl;
}

void handleCorrectInsertion(int codeIndex)
{
	feedbackAllDigits[codeIndex] = CORRECT;
}

void handleMisplacedInsertion(int codeIndex, const std::vector<int>& code,
		const std::vector<int>& guess)
{
	for (unsigned int j = 0; j < guess.size(); ++j) {
		if ( j != (unsigned) codeIndex && guess.at(j) == code.at(codeIndex) &&
				feedbackAllDigits.at(codeIndex) != CORRECT) {
			feedbackAllDigits[codeIndex] = MISPLACED;
		}
	}
}

void initFeedbackPerTurn()
{
	feedbackAllDigits.clear();
	feedbackAllDigits[GUESS_DIGIT0] = NULLCHAR;
	feedbackAllDigits[GUESS_DIGIT1] = NULLCHAR;
	feedbackAllDigits[GUESS_DIGIT2] = NULLCHAR;
	feedbackAllDigits[GUESS_DIGIT3] = NULLCHAR;
}

std::vector<char> constructFeedback()
{
	feedback.clear();

	std::vector<char> temp = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
	for (unsigned int codeIndex = 0; codeIndex < feedbackAllDigits.size(); ++codeIndex) {
		if (feedbackAllDigits[codeIndex] == MISPLACED) {
			feedback.push_back(feedbackAllDigits[codeIndex]);
		}
		else {
			feedback.insert(feedback.begin(), feedbackAllDigits[codeIndex]);
		}
    }

	return feedback;
}

bool noMisplaced(const std::vector<char>& feedback) {
	for (auto f : feedback) {
		if (f != CORRECT) {
			return false;
		}
	}
	return true;
}

}

namespace mastermind
{

Board::Board(int codeLength) :
		codeLength(codeLength)
{
	initialize();
}

Board::~Board()
{
}

void Board::initialize()
{
	code.clear();
	generateCode();
	initFeedbackPerTurn();
}

void Board::check(const std::vector<int>& code, const std::vector<int>& guess) const {
	initFeedbackPerTurn();
	for (unsigned int i = 0; i < code.size(); ++i) {
		if (code.at(i) == guess.at(i)) {
			handleCorrectInsertion(i);
		} else {
			handleMisplacedInsertion(i, code, guess);
		}
	}
	feedback = constructFeedback();
	std::cout << "\t\t";
	display(std::cout, feedback);
}

bool Board::isCodeCracked(const std::vector<int>& guess) const
{
	check(code, guess);
	return ((feedback.size() == code.size()) && noMisplaced(feedback));
}

void Board::showCode() const
{
	display(std::cout, code);
}

void Board::generateCode()
{
	for (int i = 0; i < codeLength; i++) {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		srand(seed);
		code.push_back(rand()%(codeLength*2));
	}

//	code = {7,7,7,0};
//	code = {2,7,2,2};
//	code = {6,2,6,2};
//	code = {3,1,0,3};
//	display(std::cout, code);
}

} /* namespace Mastermind */
