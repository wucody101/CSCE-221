#ifndef CHAINING_H
#define CHAINING_H

#include "AbstractHashTable.h"
#include <vector>
#include <list>


// Chaining hash table class
class ChainingHashTable: public AbstractHashTable {
    private:
    std::vector<std::list<HashEntry>> table;
    void resizeAndRehash();

    public: 
    ChainingHashTable();
    ~ChainingHashTable(); 
    void insert(std::string key, const int val); 
    int remove(std::string key); 
    int get(std::string key) const;
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor
ChainingHashTable::ChainingHashTable(): AbstractHashTable() {
	maxLoadFactor = 3;
    table.resize(capacity);
    
}

// destructor
ChainingHashTable::~ChainingHashTable() {
    capacity = 11;
    num_elements = 0;
    table.resize(capacity);
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {
    
    int index = hash(key);
    
    for (std::list<HashEntry>::iterator iter = table[index].begin(); iter != table[index].end(); iter++) {
        if ((*iter).key == key) {
            (*iter).val = val;
            return;
        }
    }

    table[index].push_back(HashEntry(key, val));

    num_elements++;
    if (load_factor() > maxLoadFactor) {
        resizeAndRehash();
    }
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ChainingHashTable::remove(std::string key) {
    
    int index = hash(key);
    
    for (std::list<HashEntry>::iterator iter = table[index].begin(); iter != table[index].end(); iter++) {
        if ((*iter).key == key) {
            int deleted = (*iter).val;
            table[index].erase(iter);
            num_elements--;
            return deleted;
        }
    }

    throw std::out_of_range("Key is not in the list");
	
}

// getter to obtain the value associated with the given key
int ChainingHashTable::get(std::string key) const {
    
    int index = hash(key);
    
    for (std::list<HashEntry>::const_iterator iter = table[index].begin(); iter != table[index].end(); iter++) {
        if ((*iter).key == key) {
            return (*iter).val;
        }
    }
	
    throw std::out_of_range("Key is not in the list");
}

bool ChainingHashTable::contains(const std::string key) const {
	
    int index = hash(key);
    
    for (std::list<HashEntry>::const_iterator iter = table[index].begin(); iter != table[index].end(); iter++) {
        if ((*iter).key == key) {
            return true;
        }
    }
	
    return false;
}

void ChainingHashTable::resizeAndRehash() {

    int nextSize = findNextPrime(capacity*2);

    std::vector<std::list<HashEntry>> updated(nextSize);
    capacity = nextSize;

    for (int i = 0; i < table.size(); i++) {
        for (std::list<HashEntry>::const_iterator iter = table[i].begin(); iter != table[i].end(); iter++) {
            int newIndex = hash((*iter).key);
            updated[newIndex].push_back(*iter);
        }
    }

    table.clear();
    table = updated;
}

#endif
