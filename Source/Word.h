#pragma once

#include <string>
#include <iostream>

using namespace std;

class Word {
private:
	string _word;
	string _mean;

public:
	Word();
	Word(string word);
	Word(string word, string mean);

	void setWord(string word);
	void setMean(string mean);
	string getWord() const;
	string getMean() const;

	Word& operator=(const Word &b);
	bool operator>(const Word &b) const;
	bool operator==(const Word &b) const;
	bool operator<(const Word &b) const;
	bool operator>=(const Word &b) const;
	bool operator<=(const Word &b) const;

	friend ostream& operator<<(ostream &os, const Word& b);
};