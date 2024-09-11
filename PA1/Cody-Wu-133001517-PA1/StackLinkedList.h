#ifndef STACK_LinkedList_H
#define STACK_LinkedList_H
#include "AbstractStack.h"

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <typename T>
class StackLinkedList : public AbstractStack<T>{
private:
    Node<T>* head;
    int length;
public:
    StackLinkedList();

    ~StackLinkedList();

    StackLinkedList(const StackLinkedList& other);

    StackLinkedList& operator=(const StackLinkedList& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackLinkedList<T>::StackLinkedList() : head(nullptr), length(0) {
}

template <typename T>
StackLinkedList<T>::~StackLinkedList(){
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& other) : head(nullptr) {
    Node<T>* current = other.head;
    Node<T>* tail;
    length = other.length;
    head = nullptr;
    while (current != nullptr) {
        if (head == nullptr) {
            Node<T>* addNew = new Node<T>();
            addNew->data = current->data;
            head = addNew;
            tail = addNew;
        }
        else {
            Node<T>* addNew = new Node<T>();
            addNew->data = current->data;
            tail->next = addNew;
            tail = tail->next;
        }
        current = current->next;
    }
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& other) {
    if (this != &other) {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        current = other.head;
        Node<T>* tail;
        length = other.length;
        head = nullptr;
        while (current != nullptr) {
            if (head == nullptr) {
                Node<T>* addNew = new Node<T>();
                addNew->data = current->data;
                head = addNew;
                tail = addNew;
            }
            else {
                Node<T>* addNew = new Node<T>();
                addNew->data = current->data;
                tail->next = addNew;
                tail = tail->next;
            }
            current = current->next;
        }

    }
    return *this;
}

template <typename T>
bool StackLinkedList<T>::isEmpty(){
    return (length == 0);
}

template <typename T>
int StackLinkedList<T>::size(){
    return length;
}

template <typename T>
T& StackLinkedList<T>::top(){
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    else {
        return head->data;
    }
}

template <typename T>
T StackLinkedList<T>::pop(){
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    else {
        Node<T>* temp = head;
        T popped = head->data;
        head = head->next;
        length--;
        delete temp;
        return popped;
    }
}

template <typename T>
void StackLinkedList<T>::push(const T& e){
    length++;
    Node<T>* add = new Node<T>();
    add->data = e;
    add->next = head;
    head = add;
}


#endif
