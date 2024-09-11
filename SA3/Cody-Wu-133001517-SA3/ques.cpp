#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "PriorityQueueHeap.h"

using namespace std;

#ifndef INTERSECTION_ARRAY
 
vector<int> intersectionOfTwoArrays(vector<int> nums, vector<int> otherNums) {
    vector<int> intersection;

    unordered_map<int, int> num;
    unordered_map<int, int> Onum;

    for (vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter++) {
        if (num.find(*iter) == num.end()) {
            num.insert(make_pair(*iter, 1));
        }
        else {
            unordered_map<int, int>::iterator it = num.find(*iter);
            it->second++;
        }
    }

    for (vector<int>::iterator iter = otherNums.begin(); iter != otherNums.end(); iter++) {
        if (Onum.find(*iter) == Onum.end()) {
            Onum.insert(make_pair(*iter, 1));
        }
        else {
            unordered_map<int, int>::iterator it = Onum.find(*iter);
            it->second++;
        }
    }

    for (unordered_map<int, int>::iterator iter = num.begin(); iter != num.end(); iter++) {
        if (Onum.find(iter->first) != Onum.end()) {
            int amount = 0;
            if (iter->second > Onum.find(iter->first)->second) {
                amount = Onum.find(iter->first)->second;
            }
            else {
                amount = iter->second;
            }

            for (int i = 0; i < amount; i++) {
                intersection.push_back(iter->first);
            }
        }
    }

    return intersection;
}

#endif

#ifndef ROPE_GAME

int ropesGameCost(vector<int> ropes) {

    PriorityQueueHeap pq;

    for (int i = 0; i < ropes.size(); i++) {
        pq.pq_insert(ropes[i]);
    }

    int sum = 0;
    while (pq.pq_size() != 1) {
        int s1 = pq.pq_delete();
        int s2 = pq.pq_delete();
        int total = s1 + s2;
        sum += total;
        pq.pq_insert(total);
    }
    
    return sum;
}

#endif

#ifndef TEST_MODE

int main() {
    // Test cases for intersectionOfTwoArrays:
    cout << "TEST CASES FOR intersectionOfTwoArrays" << endl;
    {
        cout << "Test Case 1:" << endl;
        vector<int> nums = {9, 8, 8, 7};
        vector<int> otherNums = {8, 8, 8, 9};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and one 9" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 2:" << endl;
        vector<int> nums = {1, 8, 1, 8, 1, 7, 46, 1};
        vector<int> otherNums = {8, 1, 8, 1, 1, 203};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should contain two 8's and three 1's" << endl;
        cout << endl;
    }

    {
        cout << "Test Case 3:" << endl;
        vector<int> nums = {1, 8, 7, 5, 53};
        vector<int> otherNums = {102, 203, 201, 103, 106, 107};

        vector<int> result = intersectionOfTwoArrays(nums, otherNums);
        cout << "Returned intersection: ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
        cout << "The above intersection should be empty (should not see any numbers)" << endl;
        cout << endl;
    }

    cout << "TEST CASES FOR ropesGameCost" << endl;

    {
        cout << "Test Case 1: " << endl;
        vector<int> ropes = {3, 8, 4, 6, 7};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 63;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
        cout << endl;
    }

     {
        cout << "Test Case 2: " << endl;
        vector<int> ropes = {3, 7, 9, 4};
        int actualCost = ropesGameCost(ropes);
        int expectedCost = 44;
        cout << "Returned Total Cost: " << actualCost << endl;
        cout << "Expected Total Cost: " << expectedCost << endl;
    }

    return 0;
}
#endif
