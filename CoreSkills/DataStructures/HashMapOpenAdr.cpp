/*
Design a Hash Table class.

Your HashTable class should support the following operations:

HashTable(int capacity) will initialize an empty hash table with a capacity of capacity, where capacity > 1.
int get(int key) will return the value associated with the key. If the key is not present in the hash table, return -1.
void insert(int key, int value) will insert the key-value pair into the hash table. If the key is already present in the hash table, the original value should be replaced with the new value.
bool remove(int key) will remove the key-value pair with the given key. If the key is not present, return false, otherwise return true
int getSize() will return the number of keys in the hash table.
int getCapacity() will return the capacity of the hash table.
void resize() will double the capacity of the hash table. This method should be called automatically when the load factor reaches or exceeds 0.5. Your insert method should automatically call resize() when necessary.
Note: You can choose how to handle collisions.

This implementation handles collisions with Open Addressing. When there is a collision on an insert, this implementation iterates through the underlying array, 
checking for the next open index. 
*/

#include <utility>
#include <memory>
#include <vector>
#include <iostream>

class Pair {

public:
    int key;
    int val;

    Pair(int k, int v) {
        key = k;
        val = v;
    }
};

class HashTable {

public:
    int cap;
    int size;
    std::vector<std::unique_ptr<Pair>> map;

    HashTable(int capacity) {
        cap = capacity;
        size = 0;
        map = std::vector<std::unique_ptr<Pair>>(capacity);
    }

    int hash(int key) {
        return key % cap;
    }
    
    void insert(int key, int value) { // insert k,v pair to hashtable O(1)
        int ind = hash(key);
        while (map[ind]) {
            if (map[ind]->key == key) { // the key already exists, overwrite the value
                map[ind]->val = value;
                return;
            }
            ind++;
            if (ind >= cap) {
                ind = ind % cap; // go back to the beginning of the array
            }
        }

        // found an empty spot
        map[ind] = std::make_unique<Pair>(key, value); // create a pair at the empty spot
        std::cout << "inserted: " << key << std::endl;
        size++;
        if (size >= cap / 2) { // resize if load factor reaches or exceeds 0.5.
            std::cout << "Resizing, size: " << size << " capacity: " << cap << std::endl; 
            resize();
        }
        return;
    }

    int get(int key) { // return the value associated with the key O(1)
        int ind = hash(key);
        while (map[ind]) {
            if (map[ind]->key == key) { //found the key
                return map[ind]->val;
            }
            // keep looking for the key
            ind++;
            if (ind >= cap) {
                ind = ind % cap; // go back to the beginning of the array
            }
        }
        return -1; // key is not present
    }

    bool remove(int key) { // remove the k,v pair if present // O(1)
        int ind = hash(key);
        while (map[ind]) {
            if (map[ind]->key == key) { // found the key to remove
                map[ind] = nullptr; // memory is automatically deallocated - pair is deleted
                size--;
                return true;
            }
            // keep looking
            ind++;
            if (ind >= cap) {
                ind = ind % cap; // go back to the beginning of the array
            }
        }
        return false; // reached NULL, key not present
    }

    int getSize() const { // O(1)
        return size;
    }

    int getCapacity() const { // O(1)
        return cap;
    }

    void resize() { // double the capacity, create new map, rehash k,v from old map O(n)
        cap = cap * 2;

        std::vector<std::unique_ptr<Pair>> oldTable = std::move(map);
        map = std::vector<std::unique_ptr<Pair>>(cap);
        size = 0;
        for (int i = 0; i < oldTable.size(); i++) {
            if (oldTable[i]) { // only rehash pairs that exist
                insert(oldTable[i]->key, oldTable[i]->val);
            }
        }

         // oldTable goes out of scope here and its destructor is called,
         // which in turn calls the destructors of the unique_ptrs it contains,
         // freeing the memory of the old elements.
        std::cout << "new cap: " << cap << std::endl;
        return;  
    }
};

/*
Input:
["HashTable", 4, "insert", 1, 2, "get", 1, "insert", 1, 3, "get", 1, "remove", 1, "get", 1]

Output:
[null, null, 2, 3, true, -1]

Input:
["HashTable", 2, "getCapacity", insert, 6, 7, "getCapacity", "insert", 1, 2, "getCapacity", "insert", 3, 4, "getCapacity", "getSize"]

Output:
[null, 2, null, 4, null, 8, null, 8, 3]
*/

