#include <iostream>
#include <queue>
using namespace std;

void bubbleSort(int *arr, int size){
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j + 1] < arr[j]) {
                int holder = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = holder;
            }
        }
    }
}

void heapSort(int *arr, int size){
    
    priority_queue<int> sort;
    for (int i = 0; i < size; i++) {
        sort.push(arr[i]);
    }

    for (int j = size - 1; j >= 0; j--) {
        arr[j] = sort.top();
        sort.pop();
    }
}

void merge(int* arr, int start, int middle, int end) {
    int left = middle - start + 1;
    int right = end - middle;

    int leftnums[left];
    int rightnums[right];

    for (int i = 0; i < left; i++) {
        leftnums[i] = arr[i + start];
    }
    for (int j = 0; j < right; j++) {
        rightnums[j] = arr[j + middle + 1];
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int mainIndex = start;
    while (leftIndex < left && rightIndex < right) {
        if (leftnums[leftIndex] >= rightnums[rightIndex]) {
            arr[mainIndex] = rightnums[rightIndex];
            rightIndex++;
        }
        else {
            arr[mainIndex] = leftnums[leftIndex];
            leftIndex++;
        }
        mainIndex++;
    }

    while (leftIndex < left) {
        arr[mainIndex] = leftnums[leftIndex];
        leftIndex++;
        mainIndex++;
    }

    while (rightIndex < right) {
        arr[mainIndex] = rightnums[rightIndex];
        rightIndex++;
        mainIndex++;
    }
}

void mergeSort(int * arr, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        
        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }

}

int partition(int* arr, int start, int end) {
    
    int pivot = arr[end];

    int left = start - 1;

    for (int right = start; right <= end; right++) {
        if (arr[right] < pivot) {
            left++;
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }

    left++;
    int temp = arr[left];
    arr[left] = arr[end];
    arr[end] = temp;

    return left;
}

void quickSort(int *arr, int start, int end) {
    if (start < end) {
        int p = partition(arr, start, end);
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
}
