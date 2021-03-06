/*
 * Board.cpp
 *
 *  Created on: 9 Jan, 2015
 *      Author: daniel
 */

#include "Board.h"
#include <chrono>
#include <sstream>

using namespace mastermind;
using namespace std;

using SysClock = chrono::system_clock;

namespace {

bool noMisplaced(const Hint& feedback) {
	for (auto f : feedback) {
		if (f != Correct) {
			return false;
		}
	}
	return true;
}

} //unnamed namespace

Board::Board(int codeLength) : codeLength(codeLength)
{
	initialize();
}

Board::~Board()
{
}

void Board::initialize()
{
	secretCode_.clear();
	generateSecretCode();
}

Hint Board::getHint(const Code& guess)
{
	int correct = 0;
	int misplaced = 0;
	vector<int> secretDigits(10, 0);
	vector<int> guessDigits(10, 0);
	for (size_t i = 0; i < secretCode_.size(); ++i) {
		int s = secretCode_[i];
		int g = guess[i];
		if (s == g) ++correct;
		else {
			++secretDigits[s];
			++guessDigits[g];
		}
	}
	for (int i = 0; i < 10; ++i) {
		misplaced += min(secretDigits[i], guessDigits[i]);
	}

	Hint hint;
	for (int i = 0; i < correct; ++i) hint.push_back(Correct);
	for (int i = 0; i < misplaced; ++i) hint.push_back(Misplaced);
	return hint;
}

bool Board::isCodeCracked(const Hint& hint) const
{
	return ((hint.size() == secretCode_.size()) && noMisplaced(hint));
}

string Board::secretCode() const
{
	ostringstream code;
	for (auto c : secretCode_) code << c;
	return code.str();
}

void Board::generateSecretCode()
{
	for (int i = 0; i < codeLength; i++) {
		unsigned seed = SysClock::now().time_since_epoch().count();
		srand(seed);
		secretCode_.push_back(rand()%(codeLength*2));
	}

//	code = {7,7,7,0};
//	code = {2,7,2,2};
//	code = {6,2,6,2};
//	code = {3,1,0,3};
//	display(cout, code);
}
