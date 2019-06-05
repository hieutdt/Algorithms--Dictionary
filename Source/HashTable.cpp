#include "HashTable.h"
#include <fstream>

using namespace std;

hash<string> hasher;

//PRIVATE METHODS//////////////////////////////////////

bool HashTable::isPrimeNumber(int n) const {
	if (n <= 2)
		return true;
	for (int i = 2; i < sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

int HashTable::getBeforePrimeNumber(int n) const {
	for (int i = n; i > 0; i--) {
		if (isPrimeNumber(i))
			return i;
	}
	return 2;
}

int HashTable::hashCode(const string &key) const {
	size_t hashVal = hasher(key);
	return hashVal % CAPACITY;
}

//PUBLIC METHODS///////////////////////////////////////////

HashTable::HashTable() {
	this->CAPACITY = 0;
    this->arr = nullptr;
}

HashTable::HashTable(int capacity) {
	this->CAPACITY = getBeforePrimeNumber(capacity * 1.8);
	this->arr = new SinglyLinkedList<Word>[CAPACITY];
}

HashTable::~HashTable() {
	for (int i = 0; i < CAPACITY; i++)
		arr[i].clear();
	delete[] arr;
}

void HashTable::insert(const Word &item) {
	int index = hashCode(item.getWord());
	arr[index].addLast(item);
}

void HashTable::remove(const Word &item) {
	int index = hashCode(item.getWord());
	arr[index].remove(item);
}

Word* HashTable::search(const string &key) const {
	int index = hashCode(key);
	Word searchVal;
	searchVal.setWord(key);
	searchVal.setMean(" ");
	Node<Word> *val = arr[index].search(searchVal);
    if (val == nullptr)
        return nullptr;
	Word *res = new Word();
	*res = val->getKey();
	return res;
}

bool HashTable::isEmpty() const {
    if (this->arr == nullptr)
		return true;
	for (int i = 0; i < CAPACITY; i++) {
		if (!arr[i].isEmpty())
			return false;
	}
	return true;
}

void HashTable::writeToFile(const string fileName) {
	ofstream os;
	os.open(fileName);

	for (int i = 0; i < CAPACITY; i++) {
		arr[i].writeToStream(os);
	}
	os.close();
}

int HashTable::maxLong() const {
	int max = this->arr[0].getLength();
	for (int i = 0; i < CAPACITY; i++)
		if (arr[i].getLength() > max)
			max = arr[i].getLength();
	return max;
}

void HashTable::clear() {
	for (int i = 0; i < CAPACITY; i++)
		this->arr[i].clear();
	delete[] this->arr;
}
