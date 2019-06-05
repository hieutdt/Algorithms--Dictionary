#include "Word.h"

using namespace std;

Word::Word() {
	this->_word = "";
	this->_mean = "";
}

Word::Word(string word) {
	this->_word = word;
}

Word::Word(string word, string mean) {
	this->_word = word;
	this->_mean = mean;
}

void Word::setWord(string word) {
	this->_word = word;
}

void Word::setMean(string mean) {
	this->_mean = mean;
}

string Word::getWord() const {
	return this->_word;
}

string Word::getMean() const {
	return this->_mean;
}

Word& Word::operator=(const Word &b) {
	this->_mean = b._mean;
	this->_word = b._word;
	return *this;
}

bool Word::operator>(const Word &b) const {
	return this->_word > b._word;
}

bool Word::operator<(const Word &b) const {
	return this->_word < b._word;
}

bool Word::operator==(const Word &b) const {
	return this->_word == b._word;
}

bool Word::operator<=(const Word &b) const {
	return this->_word <= b._word;
}

bool Word::operator>=(const Word &b) const {
	return this->_word >= b._word;
}

ostream& operator<<(ostream& os, const Word &b) {
	os << b._word << "   " << b._mean << endl;
	return os;
}