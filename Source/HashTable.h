#pragma once

#include "SinglyLinkedList.h"
#include "Word.h"

#include <string>

using namespace std;

class HashTable {
public:
	SinglyLinkedList<Word> *arr;
	int CAPACITY;

	bool isPrimeNumber(int n) const;
	int getBeforePrimeNumber(int n) const;

	int hashCode(const string &key) const;
public:
	HashTable();
	HashTable(int capacity);
	~HashTable();

	bool isEmpty() const;
	void insert(const Word &item);
	void clear();
	void remove(const Word &item);
	Word* search(const string &key) const;
	void writeToFile(const string fileName);
	int maxLong() const;
};