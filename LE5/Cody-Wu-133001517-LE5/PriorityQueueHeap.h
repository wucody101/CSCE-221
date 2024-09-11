#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename Type, typename Compare = std::greater<Type>>
class PriorityQueueHeap {
private:
    Compare compare;
    Type *arr;
    int capacity;
    int size;

    void heapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    PriorityQueueHeap(const PriorityQueueHeap& other);

    PriorityQueueHeap(const Compare& comp);

    PriorityQueueHeap& operator=(const PriorityQueueHeap& other);

    ~PriorityQueueHeap();

    int pq_size();

    bool is_pq_empty();
    
    Type pq_top();

    void pq_insert(Type x);

    Type pq_delete();
};

// Your implementation here

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap() : compare() {
    arr = new Type[10];
    size = 0;
    capacity = 10;
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::~PriorityQueueHeap(){
    delete[] arr;
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const Compare& _comp) {
    arr = new Type[10];
    size = 0;
    capacity = 10;
    compare = _comp;
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const PriorityQueueHeap& other) {
    size = other.size;
    capacity = other.capacity;
    compare = other.compare;

    arr = new Type[capacity];

    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
    
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>& PriorityQueueHeap<Type, Compare>::operator=(const PriorityQueueHeap& other) {
    if (this != &other) {
        delete[] arr;
        
        size = other.size;
        capacity = other.capacity;
        compare = other.compare;

        arr = new Type[capacity];

        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    
    return *this;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_size() {
    return size;
}

template <typename Type, typename Compare>
bool PriorityQueueHeap<Type, Compare>::is_pq_empty(){
    return (size == 0);
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_parent(int i){
    return ((i - 1) / 2);
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_top(){
    if (is_pq_empty()) {
        throw std::out_of_range("Priority Queue is empty");
    }
    
    else {
        return arr[0];
    }
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::pq_insert(Type x) {
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

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::bubbleUp(int i){
     
    if (compare(arr[pq_parent(i)], arr[i]) && i > 0) {
        Type temp = arr[i];
        arr[i] = arr[pq_parent(i)];
        arr[pq_parent(i)] = temp;
        i = pq_parent(i);
        bubbleUp(i);
    }

}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_delete(){

    if (is_pq_empty()) {
        throw std::out_of_range("Priority Queue is empty");
    }

    Type deleted = arr[0];
    arr[0] = arr[size-1];
    size--;

    heapify(0);

    return deleted;
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::heapify(int i){
    
    int changeTo = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    
    if (left < size && compare(arr[i], arr[left])) {
        changeTo = left;
    }

    if (right < size && compare(arr[changeTo], arr[right])) {
        changeTo = right;
    }

    if (i != changeTo) {
        Type temp = arr[i];
        arr[i] = arr[changeTo];
        arr[changeTo] = temp;
        i = changeTo;
        heapify(i);
    }

}

#endif
