#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H

template <typename Type>
class SortedPriorityQueue {
    private:
        Type *arr;
        int capacity;
        int startIndex;
        int size;

    public:
        SortedPriorityQueue();

        ~SortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
SortedPriorityQueue<Type>::SortedPriorityQueue() {
    arr = new Type[10];
    capacity = 10;
    size = 0;
    startIndex = 0;
}

template <typename Type>
SortedPriorityQueue<Type>::~SortedPriorityQueue(){
    delete[] arr;
}

template <typename Type>
void SortedPriorityQueue<Type>::pq_insert(Type value) {
    if (size == capacity) {
        Type *temp = new Type[capacity*2];

        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacity = capacity*2;
    }

    if (value < arr[size-1]) {
        int insertIndex = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] > value) {
                insertIndex = i;
                break;
            }
        }

        for (int j = size; j > insertIndex; j--) {
            arr[j] = arr[j-1];
        }

        arr[insertIndex] = value;
    }
    
    else {
        arr[size] = value;
    }

    size++;
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_delete(){
    if (size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }
    
    Type deleted = arr[startIndex];
    size--;
    startIndex++;

    return deleted;
}

#endif
