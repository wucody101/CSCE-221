#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Node {
public:
    int key;
    std::vector<Node*> forward;

    Node(int key, int level) : key(key), forward(level + 1, nullptr) {}
};

class SkipList {
private: 
    double P;
    int MAXLVL;
    Node* header;
    int level;

public:
    SkipList(int max_lvl, double p);
    ~SkipList();
    int randomLevel();
    void insertElement(int key);
    void deleteElement(int search_key);
    bool searchElement(int key);
    void displayList();
};


SkipList::SkipList(int max_lvl, double p) : MAXLVL(max_lvl), P(p), level(0) {
    header = new Node(-1, MAXLVL);
}

SkipList::~SkipList() {
    Node* current = header->forward[0];
    while (current != nullptr) {
        Node* next = current->forward[0];
        delete current;
        current = next;
    }
    delete header;
} 

int SkipList::randomLevel() {
    
    int current = 0;

    while ((rand() % 2) < P && current < MAXLVL) {
        current++;
    }
    
    return current;
}

void SkipList::insertElement(int key) {
    if (!searchElement(key)) {
        int i = randomLevel();
        
        if (i > level) {
            level = i;
        }

        Node* current = header;
        Node* add = new Node(key, i);
        while (i >= 0) {
            while (current->forward[i] != nullptr && key > current->forward[i]->key) {
                current = current->forward[i];
            }

            Node* next = current->forward[i];
            current->forward[i] = add;
            current->forward[i]->forward[i] = next;
            i--;
        }
    }

    // displayList();
}

void SkipList::deleteElement(int search_key) {
    
    if (searchElement(search_key)) {

        int pos = level;
        Node* current = header;
        Node* deleted = nullptr;
        while (pos >= 0) {
            while (current->forward[pos] != nullptr && search_key > current->forward[pos]->key) {                
                current = current->forward[pos];
            }

            if (current->forward[pos] != nullptr && search_key == current->forward[pos]->key) {
                Node* temp = current->forward[pos]->forward[pos];
                deleted = current->forward[pos];
                current->forward[pos] = temp;
            }

            pos--;
        }
        if (deleted != nullptr) {
            delete deleted;
        }

        while (level > 0 && header->forward[level] == nullptr) {
            level--;
        }

        // displayList();
    }
}

bool SkipList::searchElement(int key) {
    
    Node* current = header;
    int i = level;
    while (i >= 0) {
        while (current->forward[i] != nullptr && key > current->forward[i]->key) {
            current = current->forward[i];
        }

        if (current->forward[i] != nullptr && current->forward[i]->key == key) {
            return true;
        }

        i--;
    }
    return false;
}

void SkipList::displayList() {
    std::cout << "\n*****Skip List******" << std::endl;
    Node* head = header;
    for (int lvl = 0; lvl <= level; lvl++) {
        std::cout << "Level " << lvl << ": ";
        Node* node = head->forward[lvl];
        while (node != nullptr) {
            std::cout << node->key << " ";
            node = node->forward[lvl];
        }
        std::cout << std::endl;
    }
}

#endif
