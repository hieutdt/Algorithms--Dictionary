#pragma once

#include "Node.h"

template <class T>
class LinkedListInterface {
public:
    virtual ~LinkedListInterface() {}
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;

	virtual Node<T>* search(const T &) const = 0;
	virtual T getFirst() const = 0;
	virtual T getLast() const = 0;
	virtual T getAt(int index) const = 0;

	virtual void addFirst(const T &) = 0;
	virtual void addLast(const T &) = 0;
	virtual void addAt(const T &, int index) = 0;

	virtual void removeFirst() = 0;
	virtual void removeLast() = 0;
	virtual void remove(const T &) = 0;

	virtual void clear() = 0;
};

