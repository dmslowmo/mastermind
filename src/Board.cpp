/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include "Board.h"
#include <cstdlib>
#include <chrono>
#include <map>

using namespace mastermind;
using namespace std;

namespace {

map<int, char> feedbackAllDigits;
vector<char> feedback;

bool noMisplaced(const vector<char>& feedback) {
	for (auto f : feedback) {
		if (f != CORRECT) {
			return false;
		}
	}
	return true;
}

}

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
	secretCode_.clear();
	generateCode();
}

vector<char> Board::getHint(const vector<int>& guess) {
	int bulls = 0;
	int cows = 0;
	vector<int> secretDigits(10, 0);
	vector<int> guessDigits(10, 0);
	for (size_t i = 0; i < secretCode_.size(); ++i) {
		int s = secretCode_[i];
		int g = guess[i];
		if (s == g) ++bulls;
		else {
			++secretDigits[s];
			++guessDigits[g];
		}
	}
	for (int i = 0; i < 10; ++i) {
		cows += min(secretDigits[i], guessDigits[i]);
	}

	vector<char> hint;
	for (int i = 0; i < bulls; ++i) hint.push_back(CORRECT);
	for (int i = 0; i < cows; ++i) hint.push_back(MISPLACED);
	return hint;
}

bool Board::isCodeCracked(const vector<char>& hint) const
{
	return ((hint.size() == secretCode_.size()) && noMisplaced(hint));
}

vector<int> Board::secretCode() const
{
	return secretCode_;
}

void Board::generateCode()
{
	for (int i = 0; i < codeLength; i++) {
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		srand(seed);
		secretCode_.push_back(rand()%(codeLength*2));
	}

//	code = {7,7,7,0};
//	code = {2,7,2,2};
//	code = {6,2,6,2};
//	code = {3,1,0,3};
//	display(cout, code);
}
