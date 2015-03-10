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
const char NULLCHAR = '\0';
const int GUESS_IDX0 = 0;
const int GUESS_IDX1 = 1;
const int GUESS_IDX2 = 2;
const int GUESS_IDX3 = 3;

namespace {

std::map<int, std::vector<char> > feedbackAllDigits;
std::vector<char> feedback;

void handleCorrectInsertion(int codeIndex)
{
	feedbackAllDigits[codeIndex].at(codeIndex) = CORRECT;
}

void handleMisplacedInsertion(int codeIndex, const std::vector<int>& code,
		const std::vector<int>& guess)
{
	for (unsigned int j = 0; j < code.size(); j++)
	{
		if ( (feedbackAllDigits[codeIndex].at(j) != CORRECT)
				&& (code.at(j) == guess.at(codeIndex)) )
		{
			feedbackAllDigits[codeIndex].at(j) = MISPLACED;
		}
	}
}

void initFeedbackPerTurn()
{
	feedbackAllDigits.clear();
	feedbackAllDigits[GUESS_IDX0] = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
	feedbackAllDigits[GUESS_IDX1] = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
	feedbackAllDigits[GUESS_IDX2] = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
	feedbackAllDigits[GUESS_IDX3] = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
}

std::vector<char> constructFeedback()
{
	feedback.clear();

    std::vector<char> temp = {NULLCHAR, NULLCHAR, NULLCHAR, NULLCHAR};
	for (unsigned int codeIndex = 0; codeIndex < feedbackAllDigits.size(); ++codeIndex)
    {
        for (unsigned int j = 0; j < feedbackAllDigits[codeIndex].size(); ++j)
        {
            if (feedbackAllDigits[codeIndex][j] == CORRECT)
            {
            	temp.at(j) = CORRECT;
            	break;
            }
            else if (temp.at(j) == NULLCHAR && feedbackAllDigits[codeIndex][j] != NULLCHAR)
            {
            	temp.at(j) = MISPLACED;
            	break;
            }
        }
    }

	for (auto f : temp)
	{
		if (f == CORRECT)
		{
			feedback.insert(feedback.begin(), CORRECT);
		}
		else if (f == MISPLACED)
		{
			feedback.push_back(MISPLACED);
		}
	}

	return feedback;
}

bool noMisplaced(const std::vector<char>& feedback) {
	for (auto f : feedback) {
		if (f == MISPLACED) {
			return false;
		}
	}
	return true;
}

}

namespace mastermind {

Board::Board(int maxAttempts, int codeLength) :
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
	for (unsigned int i = 0; i < code.size(); i++) {
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

	return ((feedback.size() == code.size()) & noMisplaced(feedback));
}

void Board::showCode() const
{
	display(std::cout, code);
}

void Board::generateCode()
{
	for (int i = 0; i < codeLength; i++)
	{
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
void Board::display(std::ostream& out, const std::vector<T>& row) const
{
	for (auto f : row)
	{
		out << f;
	}
	out << std::endl;
}

} /* namespace Mastermind */
