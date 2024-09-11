#ifndef STACK_DOUBLE_ARRAY_H
#define STACK_DOUBLE_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayDouble : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayDouble();

    ~StackArrayDouble();

    StackArrayDouble(const StackArrayDouble& other);

    StackArrayDouble& operator=(const StackArrayDouble& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here

template <typename T>
StackArrayDouble<T>::StackArrayDouble(){
    length = 1;
    topIndex = -1;
    data = new T[length];
}

template <typename T>
StackArrayDouble<T>::~StackArrayDouble(){
    delete[] data;
    length = 0;
    topIndex = -1;
}

template <typename T>
StackArrayDouble<T>::StackArrayDouble(const StackArrayDouble& other) {
    length = other.length;
    topIndex = other.topIndex;
    data = new T[length];
    for (size_t i = 0; i < topIndex + 1; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
StackArrayDouble<T>& StackArrayDouble<T>::operator=(const StackArrayDouble& other) {
    delete[] data;
    length = other.length;
    topIndex = other.topIndex;
    data = new T[length];
    for (size_t i = 0; i < topIndex + 1; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

template <typename T>
bool StackArrayDouble<T>::isEmpty(){
    return (topIndex < 0);
}

template <typename T>
int StackArrayDouble<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayDouble<T>::top(){
    if (isEmpty()) {
        throw std::out_of_range("The stack is empty.");
    }
    else {
        return data[topIndex];
    }
}

template <typename T>
T StackArrayDouble<T>::pop(){
    if (isEmpty()) {
        throw std::out_of_range("The stack is empty");
    }
    else {
        T popped = data[topIndex];
        T* remake = new T[length];
        for (size_t i = 0; i < topIndex; i++) {
            remake[i] = data[i];
        }
        delete[] data;
        data = remake;
        topIndex--;
        return popped;
    }
}

template <typename T>
void StackArrayDouble<T>::push(const T& e){
    if (size() == length) {
        T* newData = new T[length * 2];
        for (size_t i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        length = length * 2;
    }

    topIndex++;
    data[topIndex] = e;
}

#endif
