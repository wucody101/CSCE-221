//Least Recently Used Cache Implementation
// The size of the Cache is limited to maxSize. If the cache is full and we want to insert a new item, we remove the least recently used item from the cache.
// Implement with O(1) time complexity the following functions:
    // 1. insertKeyValue(string key, int value) - insert a key value pair into the cache. If the key already exists, update the value of the key.
    // 2. getValue(string key) - return the value of the key if it exists, otherwise return NULL.
    // 3. mostRecentKey() - return the key of the most recently used value.

#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node {
public:
	string key;
	int value;
	Node (string key,int value) {
		this->key = key;
		this->value = value;
	}
};


//LRU Cache Data Structure
class LRUCache{
private: 
	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

public:
	LRUCache(int maxSize);
	void insertKeyValue(string key,int value);
	int* getValue(string key);
	string mostRecentKey();

};

LRUCache::LRUCache(int maxSize){
	this->maxSize = maxSize > 1 ? maxSize : 1;
}

void LRUCache::insertKeyValue(string key,int value){
   // Your implementation here

	if (m.find(key) != m.end()) {
		list<Node>::iterator iter = m[key];
		iter->value = value;
		l.splice(l.begin(), l, iter);
   	}
	
	else {
		if (l.size() >= maxSize){
			Node last = l.back();
			l.pop_back();
			m.erase(last.key);
		}

		Node add = Node(key, value);
		l.push_front(add);
		m[key] = l.begin();
	}
}

int* LRUCache::getValue(string key){
    // Your implementation here

	if (m.find(key) == m.end()) {
		return nullptr;
	}
	else {
		list<Node>::iterator iter = m[key];
		l.splice(l.begin(), l, iter);
		return &(iter->value);
	}

}

string LRUCache::mostRecentKey(){
    // Your implementation here
	if (l.empty()) {
		return "";
	}
	
	else {
		return l.begin()->key;
	}
}

#endif
