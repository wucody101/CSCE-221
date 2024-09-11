#include <iostream>
#include "SortedPriorityQueue.h"

using namespace std;


void countSort(int *arr, int n, int exp) {

    int digits[10] = {};
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        digits[index]++;
    }

    for (int i = 1; i < 10; i++) {
        digits[i] += digits[i - 1];
    }

    int sorted[n];
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        sorted[digits[index] - 1] = arr[i];
        digits[index]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
}

void radixSort(int *arr, int n) {
    
    int largest = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    int numDigit = 0;
    while (largest != 0) {
        numDigit++;
        largest /= 10;
    }

    int exp = 1;
    for (int i = 0; i < numDigit; i++) {
        countSort(arr, n, exp);
        exp *= 10;
    }
}

void insertionSort(int *arr, int n) {

    SortedPriorityQueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.pq_insert(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = pq.pq_delete();
    }

}
