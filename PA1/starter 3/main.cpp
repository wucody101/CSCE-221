#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"
#include "StackLinkedList.h"
#include <chrono>
#include <ctime>

int main() {
    // Write your own tests here

    //AbstractStack<int>* test = new StackLinkedList<int>();
    
    //std::chrono::time_point<std::chrono::system_clock> start, end;

    //start = std::chrono::system_clock::now();
    //for (int i = 0; i < 3200; i++) {
    //    int add = 5;
    //    test->push(add);
    //}
    //end = std::chrono::system_clock::now();


    //std::chrono::duration<double> elapsed_seconds = end - start;
    //std:: time_t end_time = std::chrono::system_clock::to_time_t(end);

    //std::cout << "elapsed time: " << elapsed_seconds.count()*1000000 << " microseconds\n";

    return 0;
}
