#include <iostream>
#include <thread>
using namespace std;

void merge(int* arr, int start, int middle, int end, int level) {
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

void mergeSort(int * arr, int start, int end, int level) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        
        if (level == 0) {
            mergeSort(arr, start, middle, level);
            mergeSort(arr, middle + 1, end, level);
            merge(arr, start, middle, end, level);
        }
        else {
            thread first (mergeSort, arr, start, middle, level - 1);
            thread second (mergeSort, arr, middle + 1, end, level - 1);

            first.join();
            second.join();

            merge(arr, start, middle, end, level);
        }
    }
}
