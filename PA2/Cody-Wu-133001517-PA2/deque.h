#ifndef DEQUE_H
#define DEQUE_H

#include "node.h"
using namespace std;

template <class Type>
class Deque {
private:
	int s;
	Node<Type>* firstNode;
	Node<Type>* lastNode;

public:
	Deque();
	Deque(const Deque& other); 
	Deque& operator=(const Deque& other); 
	~Deque();
	bool isEmpty();
	int size();
	Type first();
	Type last();
	void insertFirst(Type o);
	void insertLast(Type o);
	Type removeFirst();
	Type removeLast();
};

// Your implementation here 

template <class Type>
Deque<Type>::Deque() : firstNode(nullptr), lastNode(nullptr), s(0){
}

template <class Type>
Deque<Type>::~Deque() {
	Node<Type>* current = firstNode;
	while (current != nullptr) {
		Node<Type>* next = current->getNext();
		delete current;
		current = next;
	}
	s = 0;
}

template <class Type>
Deque<Type>::Deque(const Deque& other) {
	Node<Type>* current = other.firstNode;
	s = other.s;

	if (other.firstNode == nullptr && other.lastNode == nullptr) {
		firstNode = nullptr;
		lastNode = nullptr;
	}
	else {
		while (current != nullptr) {
        	if (firstNode == nullptr) {
            	Node<Type>* addNew = new Node<Type>(current->getData());
            	firstNode = addNew;
            	lastNode = addNew;
        	}
        	else {
            	Node<Type>* addNew = new Node<Type>(current->getData());
            	lastNode->setNext(addNew);
				addNew->setPrev(lastNode);
            	lastNode = addNew;
        	}
        	current = current->getNext();
    	}
	}
}

template <class Type>
Deque<Type>& Deque<Type>::operator=(const Deque& other) {
	if (this != &other) {
		s = other.s;
        while (firstNode != nullptr) {
            Node<Type>* current = firstNode;
			firstNode = firstNode->getNext();
            delete current;
        }
		lastNode = nullptr;
        Node<Type>* current = other.firstNode;
        firstNode = nullptr;
		if (other.firstNode == nullptr && other.lastNode == nullptr) {
			firstNode = nullptr;
			lastNode = nullptr;
		}
		else {
			while (current != nullptr) {
				if (firstNode == nullptr) {
					Node<Type>* addNew = new Node<Type>(current->getData());
					firstNode = addNew;
					lastNode = addNew;
				}
				else {
					Node<Type>* addNew = new Node<Type>(current->getData());
					lastNode->setNext(addNew);
					addNew->setPrev(lastNode);
					lastNode = addNew;
				}
				current = current->getNext();
			}
		}

    }
	return *this;
}

template <class Type>
bool Deque<Type>::isEmpty() {
	return (s == 0);
}

template <class Type>
int Deque<Type>::size() {
	return s;
}

template <class Type>
Type Deque<Type>::first() {
	if (isEmpty()) {
		return Type();
	}
	return firstNode->getData();
}

template <class Type>
Type Deque<Type>::last() {
	if (isEmpty()) {
		return Type();
	}
	return lastNode->getData();
}

template <class Type>
void Deque<Type>::insertFirst(Type o) {
	Node<Type>* addNew = new Node<Type>(o);
	if (isEmpty()) {
		firstNode = addNew;
		lastNode = addNew;
	}
	else {
		addNew->setNext(firstNode);
		firstNode->setPrev(addNew);
		firstNode = addNew;
	}
	s++;
}

template <class Type>
void Deque<Type>::insertLast(Type o) {
	Node<Type>* addNew = new Node<Type>(o);
	if (isEmpty()) {
		firstNode = addNew;
		lastNode = addNew;
	}
	else {
		lastNode->setNext(addNew);
		addNew->setPrev(lastNode);
		lastNode = addNew;
	}
	s++;
}

template <class Type>
Type Deque<Type>::removeFirst() {
	if (isEmpty()) {
		throw std::out_of_range("The deque is empty.");
	}
	else {
		Node<Type>* temp = firstNode;
		Type popped = firstNode->getData();
		if (firstNode == lastNode) {
			firstNode = nullptr;
			lastNode = nullptr;
		}
		else {
			firstNode = firstNode->getNext();
			firstNode->setPrev(nullptr);
		}
		s--;
		delete temp;
		return popped;
		
	}
}

template <class Type>
Type Deque<Type>::removeLast() {
	if (isEmpty()) {
		throw std::out_of_range("The deque is empty.");
	}
	else {
		Node<Type>* temp = lastNode;
		Type popped = lastNode->getData();
		if (firstNode == lastNode) {
			firstNode = nullptr;
			lastNode = nullptr;
		}
		else {
			lastNode = lastNode->getPrev();
			lastNode->setNext(nullptr);
		}
		s--;
		delete temp;
		return popped;
		
	}
}

#endif
