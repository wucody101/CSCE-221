#include <iostream>
// #include <bits/stdc++.h> 
#include <chrono>
#include <ctime>
#include "AbstractPriorityQueue.h"
#include "PriorityQueueHeap.h"
#include "UnsortedPriorityQueue.h"
#include "SortedPriorityQueue.h"
using namespace std;
#ifndef TEST

int testPqInsert(AbstractPriorityQueue<int>* pq, int size){
    int projectedSize = size;

    for (int i = 0; i < projectedSize; i++) {
        int z = rand() % 200 + 25;
        pq->pq_insert(z);
    }

    return 1;
}

int testPqDelete(AbstractPriorityQueue<int>* pq,int size, string type) {
    int projectedSize = size;

    cout << "testing sort method " << type << " priority queue for " << size << " elements" << endl;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // insert
    for (int i = 0; i < projectedSize; i++) {
        int z = rand() % 200 + 25;
        pq->pq_insert(z);
    }

    // delete
    while (pq->pq_size() != 0) {
        int num = pq->pq_delete();
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time for " << type << " priority queue sort method: " << elapsed_seconds.count()*1000 << " ms\n";

    return 1;
}

int main() {
    AbstractPriorityQueue<int>* sorted = new SortedPriorityQueue<int>();
    AbstractPriorityQueue<int>* unsorted = new UnsortedPriorityQueue<int>();
    AbstractPriorityQueue<int>* heap = new PriorityQueueHeap<int>();
    int i = 100000;

    testPqDelete(sorted,i,"sorted");
    testPqDelete(unsorted,i,"unsorted");
    testPqDelete(heap,i,"heap");

    // cout << "testing sorted priority queue for " << i << " elements" << endl;
    // std::chrono::time_point<std::chrono::system_clock> start1, end1;
    // start1 = std::chrono::system_clock::now();
    // testPqInsert(sorted,i);
    // end1 = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    // std::cout << "elapsed time for sorted priority queue: " << elapsed_seconds1.count()*1000 << " ms\n";

    // cout << "testing unsorted priority queue for " << i << " elements" << endl;
    // std::chrono::time_point<std::chrono::system_clock> start2, end2;
    // start2 = std::chrono::system_clock::now();
    // testPqInsert(unsorted,i);
    // end2 = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    // std::cout << "elapsed time for unsorted priority queue: " << elapsed_seconds2.count()*1000 << " ms\n";

    // cout << "testing heap priority queue for " << i << " elements" << endl;
    // std::chrono::time_point<std::chrono::system_clock> start3, end3;
    // start3 = std::chrono::system_clock::now();
    // testPqInsert(heap,i);
    // end3 = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds3 = end3 - start3;
    // std::cout << "elapsed time for heap priority queue: " << elapsed_seconds3.count()*1000 << " ms\n";
 
    return 0;
}
//     return new SortedPriorityQueue<int>();
//     return new UnsortedPriorityQueue<int>();
//     return new PriorityQueueHeap<int>();

#endif
