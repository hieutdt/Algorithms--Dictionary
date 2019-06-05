#pragma once

template <class T>
class Node {
private:
	T key;
	Node<T> *next;
public:
	Node();
	Node(const T &key);
	Node(const T &key, const Node<T> *nextNode);
	void setKey(const T &key);
	void setNext(Node<T> *next);
	T getKey() const;
	Node<T>* getNext() const;
};


#include <cstddef>

template <class T>
Node<T>::Node() {
	this->key = 0;
    this->next = nullptr;
}

template <class T>
Node<T>::Node(const T &key) {
	this->key = key;
    this->next = nullptr;
}

template <class T>
Node<T>::Node(const T &key, const Node<T> *next) {
	this->key = key;
	this->next = next;
}

template <class T>
void Node<T>::setKey(const T &key) {
	this->key = key;
}

template <class T>
void Node<T>::setNext(Node<T> *next) {
	this->next = next;
}

template <class T>
T Node<T>::getKey() const {
	return this->key;
}

template <class T>
Node<T>* Node<T>::getNext() const {
	return this->next;
}




