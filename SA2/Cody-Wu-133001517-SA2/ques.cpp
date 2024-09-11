#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

#ifndef ASCENDING_PATHS

// You can create helper functions for count ascending paths if required here

int countAscendingPaths(Node* root){
    // use recursive
    int count = 0;

    // if current node is a leaf, add 1 to count
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

    // if left > root, traverse left (call recursive)
    if (root->left != nullptr) {
        if (root->left->data > root->data) {
            count += countAscendingPaths(root->left);
        }
    }

    // if right > root, tranverse right (call recursive)
    if (root->right != nullptr) {
        if (root->right->data > root->data) {
            count += countAscendingPaths(root->right);
        }
    }

    return count;
}

#endif

#ifndef LEFT_LEAVES

// You can create helper functions for sum of left leaves if required here

int sumOfLeftLeaves(Node* root) {
    // travserse through the list
    // if left leaf then add to sum 
    // continue to traverse list

    //    /  \
    //   / \  \
    //  /\ /\ /\

    int sum = 0;

    // backwards condition
    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    }

    // check left first
    if (root->left != nullptr) {
        //check if node is a left leaf
        if (root->left->left == nullptr && root->left->right == nullptr) {
            sum += root->left->data;
        }
        //go left
        sum += sumOfLeftLeaves(root->left);
    }

    // then check right
    if (root->right != nullptr) {
        //go right
        sum += sumOfLeftLeaves(root->right);
    }

    return sum;
}

#endif

#ifndef TEST_MODE
int main() {
    cout << "Sample Test case 1" << endl;
    {
        Node root(3);
        Node left(4), right(5);
        Node leftLeft(7), leftRight(8), rightLeft(9), rightRight(10);
        Node leftRightLeft(3), rightLeftRight(12);

        root.left = &left, root.right = &right;
        left.left = &leftLeft, left.right = &leftRight, right.left = &rightLeft, right.right = &rightRight;
        leftRight.left = &leftRightLeft, rightLeft.right = &rightLeftRight;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 10" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 3" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;
    }
    cout << endl;
    cout << endl;

    cout << "Sample Test case 2" << endl;
    {
        Node root(3);
        Node right(4);
        Node rightLeft(5), rightRight(16);
        Node rightRightLeft(14);

        root.right = &right;
        right.left = &rightLeft, right.right = &rightRight;
        rightRight.left = &rightRightLeft;

        int sumReturned = sumOfLeftLeaves(&root);
        cout << "Testing sum of left leaves" << endl;
        cout << "Expected sum of left leaves: 19" << endl;
        cout << "Returned sum of left leaves: " << sumReturned << endl;

        cout << endl;

        int numAscendingPaths = countAscendingPaths(&root);
        cout << "Testing count ascending paths" << endl;
        cout << "Expected number of ascending paths: 1" << endl;
        cout << "Returned number of ascending paths: " << numAscendingPaths << endl;
    }
}
#endif
