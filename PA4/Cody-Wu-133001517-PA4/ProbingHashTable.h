#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "AbstractHashTable.h"
#include <vector>

// Linear probing hash table class
class ProbingHashTable : public AbstractHashTable {
    private:
    std::vector<HashEntry> table;
    void resizeAndRehash();
    
    public: 
    ProbingHashTable();
    ~ProbingHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};

///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
ProbingHashTable::ProbingHashTable(): AbstractHashTable() {
	maxLoadFactor = 0.7;
    table.resize(capacity);
}

// destructor
ProbingHashTable::~ProbingHashTable() {
    capacity = 11;
    num_elements = 0;
    table.resize(capacity);
}

// inserts the given string key
void ProbingHashTable::insert(std::string key, int val) {

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

        looped = (looped + 1) % capacity;

        if (looped == index) {
            resizeAndRehash();
            index = hash(key);
            looped = index;
        }
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key) {
    int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key) {
            
            table[looped].DELETED = true;
            table[looped].isFilled = false;
            num_elements--;
            
            return table[looped].val;
        }

        looped = (looped + 1) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

	throw std::out_of_range("Key is not in the table");
}

// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
	int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key && !table[looped].DELETED) {
            return table[looped].val;
        }

        looped = (looped + 1) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

    throw std::out_of_range("Key is not in the table");
}

bool ProbingHashTable::contains(std::string key) const {
	int index = hash(key);
    int looped = index;

    while (true) {
        if (table[looped].isFilled && table[looped].key == key && !table[looped].DELETED) {
            return true;
        }

        looped = (looped + 1) % capacity;

        if (looped == index || (!table[looped].DELETED && !table[looped].isFilled)) {
            break;
        }
    }

	return false;
}

void ProbingHashTable::resizeAndRehash() {
    int nextSize = findNextPrime(capacity*2);

    std::vector<HashEntry> updated(nextSize);
    capacity = nextSize;

    for (int i = 0; i < table.size(); i++) {
        if (!table[i].DELETED) {
            
            int newIndex = hash(table[i].key);
            while (updated[newIndex].isFilled) {
                newIndex = (newIndex + 1) % capacity;
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

#endif
