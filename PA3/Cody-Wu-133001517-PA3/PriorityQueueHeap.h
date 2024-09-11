#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

using namespace std;

template <typename Type>
class PriorityQueueHeap : public AbstractPriorityQueue<Type> {
private:
    Type *arr;
    int capacity;
    int size;
    
    void minHeapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    ~PriorityQueueHeap();

    int pq_size();
    
    Type pq_get_min();

    void pq_insert(Type value);

    Type pq_delete();
};

// Your implementation here

template <typename Type>
PriorityQueueHeap<Type>::PriorityQueueHeap(){
    arr = new Type[10];
    size = 0;
    capacity = 10;
}

template <typename Type>
PriorityQueueHeap<Type>::~PriorityQueueHeap(){
    delete[] arr;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_size() {
    return size;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_parent(int i){
    return ((i - 1) / 2);
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_get_min(){
    if (size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }
    
    else {
        return arr[0];
    }
}

template <typename Type>
void PriorityQueueHeap<Type>::pq_insert(Type x) {
    if (size == capacity) {
        Type *temp = new Type[capacity*2];

        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacity = capacity*2;
    }

    arr[size] = x;
    bubbleUp(size);
    size++;
}


template <typename Type>
void PriorityQueueHeap<Type>::bubbleUp(int i){
    if (arr[pq_parent(i)] > arr[i]) {
        Type temp = arr[i];
        arr[i] = arr[pq_parent(i)];
        arr[pq_parent(i)] = temp;
        i = pq_parent(i);
        bubbleUp(i);
    }
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_delete(){
    if (size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }

    Type deleted = arr[0];
    arr[0] = arr[size-1];
    size--;

    minHeapify(0);

    return deleted;
}

template <typename Type>
void PriorityQueueHeap<Type>::minHeapify(int i){
    int changeTo = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    
    if (left < size && arr[i] > arr[left]) {
        changeTo = left;
    }

    if (right < size && arr[changeTo] > arr[right]) {
        changeTo = right;
    }

    if (i != changeTo) {
        Type temp = arr[i];
        arr[i] = arr[changeTo];
        arr[changeTo] = temp;
        i = changeTo;
        minHeapify(i);
    }
}

#endif
