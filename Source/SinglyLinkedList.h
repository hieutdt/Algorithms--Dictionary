#pragma once

#include "Node.h"
#include "LinkedListInterface.h"
#include <fstream>

template <class T>
class SinglyLinkedList : public LinkedListInterface<T> {
private:
	Node<T> *head;
	Node<T> *tail;
	int size;

	Node<T>* getPointerTo(int pos) const;
public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList &b);
	virtual ~SinglyLinkedList();

	bool isEmpty() const;
	int getLength() const;

	Node<T>* search(const T &) const;
	T getFirst() const;
	T getLast() const;
	T getAt(int index) const;

	void addFirst(const T &item);
	void addLast(const T &item);
	void addAt(const T &, int index);

	void removeFirst();
	void removeLast();
	void remove(const T &);

	void clear();

	void print() const;

	SinglyLinkedList operator=(const SinglyLinkedList &b);
	void writeToStream(std::ofstream &os);
};


#include <cstddef>
#include <iostream>

using namespace std;

//PRIVATE AREA

template <class T>
Node<T>* SinglyLinkedList<T>::getPointerTo(int pos) const {
	Node<T> *p = this->head;
	for (int i = 0; i < pos; i++)
		p = p->getNext();
	return p;
}

//PUBLIC AREA

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
	this->size = 0;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &b) {
	*this = b;
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	this->clear();
}

template <class T>
bool SinglyLinkedList<T>::isEmpty() const {
    return this->head == nullptr;
}

template <class T>
int SinglyLinkedList<T>::getLength() const {
	return this->size;
}

template <class T>
Node<T>* SinglyLinkedList<T>::search(const T &val) const {
	for (Node<T> *p = this->head; p; p = p->getNext())
		if (p->getKey() == val)
			return p;
    return nullptr;
}

template <class T>
void SinglyLinkedList<T>::addFirst(const T &item) {
	Node<T> *p = new Node<T>(item);
	if (this->isEmpty()) {
		head = tail = p;
	}
	else {
		p->setNext(this->head);
		this->head = p;
	}
	this->size++;
}

template <class T>
void SinglyLinkedList<T>::addLast(const T &item) {
	Node<T> *p = new Node<T>(item);
	if (this->isEmpty()) {
		head = tail = p;
	}
	else {
		tail->setNext(p);
		this->tail = p;
	}
	this->size++;
}

template <class T>
void SinglyLinkedList<T>::addAt(const T &item, int index) {
	int count = 0;

	if (index >= size)
		return;

	Node<T> *k = this->head;
	Node<T> *newNode = new Node<T>(item);

	for (Node<T> *p = this->head; p; p = p->getNext()) {
		if (count == index) {
			k->setNext(newNode);
			newNode->setNext(p);
			break;
		}
		else {
			count++;
			k = p;
		}
	}
}

template <class T>
T SinglyLinkedList<T>::getFirst() const {
	return this->head->getKey();
}

template <class T>
T SinglyLinkedList<T>::getLast() const {
	return this->tail->getKey();
}

template <class T>
T SinglyLinkedList<T>::getAt(int index) const {
	if (index >= 0 && index < this->size) {
		Node<T> *p = getPointerTo(index);
		return p->getKey();
	}
	return this->head->getKey();
}

template <class T>
void SinglyLinkedList<T>::removeLast() {
	if (isEmpty())
		return;

	if (this->size == 1) {
        this->head = this->tail = nullptr;
	}
	else {
		Node<T> *p = getPointerTo(this->size - 2);
        p->setNext(nullptr);
		Node<T> *tmp = this->tail;
		this->tail = p;
        delete tmp;
	}
	this->size--;
}

template <class T>
void SinglyLinkedList<T>::removeFirst() {
	if (isEmpty())
		return;

	if (this->size == 1) {
        this->head = this->tail = nullptr;
    }
	else {
		Node<T> *tmp = head;
		head = head->getNext();
        delete tmp;
	}
	this->size--;
}

template <class T>
void SinglyLinkedList<T>::remove(const T &val) {
    while (head->getKey() == val) {
		removeFirst();
        if (head == nullptr)
            return;
    }

	Node<T> *k = this->head;
	Node<T> *p = this->head->getNext();
	while (p) {
		if (p->getKey() == val) {
			Node<T> *tmp = p;
			k->setNext(p->getNext());
			delete tmp;
			p = k;
			this->size--;
		}
		else {
			k = k->getNext();
			p = p->getNext();
		}
	}

}

template <class T>
void SinglyLinkedList<T>::print() const {
	Node<T> *p = head;
	for (int i = 0; i < this->size; i++) {
		cout << p->getKey() << "  ";
		p = p->getNext();
	}
	cout << endl;
}

template <class T>
void SinglyLinkedList<T>::clear() {
	while (head)
		removeFirst();
}

template <class T>
SinglyLinkedList<T> SinglyLinkedList<T>::operator=(const SinglyLinkedList &b) {
	this->size = b.size;
	for (Node<T> *p = b.head; p; p = p->next) {
		addLast(p->getKey());
	}
}						


template <class T>
void SinglyLinkedList<T>::writeToStream(ofstream &os) {
	for (Node<T> *p = this->head; p; p = p->getNext()) {
		os << p->getKey() << endl;
	}
}
