#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

#include "AbstractHashTable.h"
#include <vector>

// Double hashing hash table class
class DoubleHashTable : public AbstractHashTable {
    private:
    // helper functions
    int secondHash(std::string s) const;
    std::vector<HashEntry> table;
    int prevPrime;
    void resizeAndRehash();

    public: 
    DoubleHashTable();
    ~DoubleHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
DoubleHashTable::DoubleHashTable(): AbstractHashTable() {
	maxLoadFactor = 0.7;
    prevPrime = 7;
    table.resize(capacity);
}

// destructor
DoubleHashTable::~DoubleHashTable() {
	capacity = 11;
    num_elements = 0;
    table.clear();
}

// inserts the given string key
void DoubleHashTable::insert(std::string key, int val) {

    int index = hash(key);
    int looped = index;

    while (true) {
        
        if (!table[looped].DELETED && !table[looped].isFilled) {
            table[looped].key = key;
            table[looped].val = val;
            table[looped].isFilled = true;
            table[looped].DELETED = false;
            num_elements++;

            if (load_factor() > maxLoadFactor) {
                resizeAndRehash();
            }

            return;
        }

        if (table[looped].DELETED && !contains(key)) {
            table[looped].key = key;
            table[looped].val = val;
            table[looped].isFilled = true;
            table[looped].DELETED = false;
            num_elements++;

            if (load_factor() > maxLoadFactor) {
                resizeAndRehash();
            }

            return;
        }

        if (table[looped].key == key) {
            table[looped].val = val;
            table[looped].DELETED = false;
            table[looped].isFilled = true;

            return;
        }

        looped = (looped + secondHash(key)) % capacity;

        if (looped == index) {
            resizeAndRehash();
            index = hash(key);
            looped = index;
        }
    }
	
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int DoubleHashTable::remove(std::string key) {

    int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key) {
            
            table[looped].DELETED = true;
            table[looped].isFilled = false;
            num_elements--;
            
            return table[looped].val;
        }

        looped = (looped + secondHash(key)) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

	throw std::out_of_range("Key is not in the table");

}

// getter to obtain the value associated with the given key
int DoubleHashTable::get(std::string key) const {

    int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key && !table[looped].DELETED) {
            return table[looped].val;
        }

        looped = (looped + secondHash(key)) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

    throw std::out_of_range("Key is not in the table");
}

bool DoubleHashTable::contains(std::string key) const {

    int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key && !table[looped].DELETED) {
            return true;
        }

        looped = (looped + secondHash(key)) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

	return false;
}

void DoubleHashTable::resizeAndRehash() {
	int nextSize = findNextPrime(capacity*2);

    std::vector<HashEntry> updated(nextSize);
    capacity = nextSize;

    for (int i = capacity-1; i >= prevPrime; i--) {
        if (isPrime(i)) {
            prevPrime = i;
            break;
        }
    }

    for (int i = 0; i < table.size(); i++) {
        if (!table[i].DELETED) {
            
            int newIndex = hash(table[i].key);
            while (updated[newIndex].isFilled) {
                newIndex = (newIndex + secondHash(table[i].key)) % capacity;
            }

            updated[newIndex].DELETED = table[i].DELETED;
            updated[newIndex].isFilled = table[i].isFilled;
            updated[newIndex].key = table[i].key;
            updated[newIndex].val = table[i].val;
        }
    }

    table.clear();
    table = updated;
}

// helper functions 
int DoubleHashTable::secondHash(std::string s) const {
	return prevPrime - (hash(s) % prevPrime);
}


#endif
