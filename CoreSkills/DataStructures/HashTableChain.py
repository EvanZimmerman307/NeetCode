"""
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

This implementation handles collisions with Chaining. When there is a collision on an insert, this implementation appends the new k,v pair to the list at the hash index. 
"""

class Pair: # Key,val object that goes in the underlying array
    def __init__(self, key: int, value: int): # O(1)
        self.key = key
        self.val = value

class HashTable:
    
    def __init__(self, capacity: int): # O(1)
        self.cap = capacity # size of underlying array
        self.size = 0
        self.map = [[]] * capacity

    def hash(self, key: int) -> int: # hash the key to find the corresponding index using mod O(1)
        return key % self.cap

    def insert(self, key: int, value: int) -> None: # insert k,v pair into hash table O(1)
        pair = Pair(key, value)
        ind = self.hash(key)

        for p in self.map[ind]: # iterate through the chain
            if p.key == key: # the key already exists, replace the value
                print("The key exists: ", key)
                p.val = value
                return
        # We did not find that the key exists
        self.map[ind].append(pair)       
        self.size += 1
        if self.size >= self.cap / 2: # automatically resize when the load factor reaches or exceeds 0.5.
            self.resize()
        return

    def get(self, key: int) -> int: # return the value associated with the key O(1)
        ind = self.hash(key)
        
        for p in self.map[ind]:
            if p.key == key:
                return p.val

        return -1 # key is not present, reached index with None
            
    def remove(self, key: int) -> bool: # remove the k,v pair with the given key O(1)
        ind = self.hash(key)
        # first find the key
        for p in self.map[ind]:
            if p.key == key:
                self.map[ind].remove(p)
                print("Removed: ", key)
                self.size -= 1
                return True
        
        return False # key is not present

    def getSize(self) -> int: # O(1)
        return self.size

    def getCapacity(self) -> int: # O(1)
        return self.cap

    def resize(self) -> None: # double capacity of the hashtable O(n) because we call insert n times
        self.cap *= 2
        # rehash keys from old table to table with new capacity

        oldMap = self.map
        self.map = [[]] * self.cap
        self.size = 0
        for chain in oldMap: # iterating through list of chains
            if len(chain) > 0: # don't care about empty lists
                for pair in chain: 
                    self.insert(pair.key, pair.val)
        return

"""
Input:
["HashTable", 4, "insert", 1, 2, "get", 1, "insert", 1, 3, "get", 1, "remove", 1, "get", 1]

Output:
[null, null, 2, 3, true, -1]

Input:
["HashTable", 2, "getCapacity", insert, 6, 7, "getCapacity", "insert", 1, 2, "getCapacity", "insert", 3, 4, "getCapacity", "getSize"]

Output:
[null, 2, null, 4, null, 8, null, 8, 3]
"""