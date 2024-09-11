#ifndef STACK_LINEAR_ARRAY_H
#define STACK_LINEAR_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayLinear : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayLinear();

    ~StackArrayLinear();

    StackArrayLinear(const StackArrayLinear& other);

    StackArrayLinear& operator=(const StackArrayLinear& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayLinear<T>::StackArrayLinear(){
    length = 1;
    topIndex = -1;
    data = new T[length];
}

template <typename T>
StackArrayLinear<T>::~StackArrayLinear(){
    delete[] data;
    length = 0;
    topIndex = -1;
}

template <typename T>
StackArrayLinear<T>::StackArrayLinear(const StackArrayLinear& other) {
    length = other.length;
    topIndex = other.topIndex;
    data = new T[length];
    for (size_t i = 0; i < topIndex + 1; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
StackArrayLinear<T>& StackArrayLinear<T>::operator=(const StackArrayLinear& other) {
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
bool StackArrayLinear<T>::isEmpty(){
    return (topIndex < 0);
}

template <typename T>
int StackArrayLinear<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayLinear<T>::top(){
    if (isEmpty()) {
        throw std::out_of_range("The stack is empty.");
    }
    else {
        return data[topIndex];
    }
}

template <typename T>
T StackArrayLinear<T>::pop(){
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
void StackArrayLinear<T>::push(const T& e){
    if (size() == length) {
        T* newData = new T[length + 10];
        for (size_t i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        length = length + 10;
    }

    topIndex++;
    data[topIndex] = e;
}

#endif
