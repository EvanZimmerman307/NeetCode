"""
Design a Binary Search Tree class.

You will design a Tree Map, which maps an integer key to an integer value. Your Tree class should support the following operations:

TreeMap() will initialize an binary search tree map.
void insert(int key, int val) will map the key to the value and insert it into the tree.
int get(int key) will return the value mapped with the key. If the key is not present in the tree, return -1.
int getMin() will return the value mapped to the smallest key in the tree. If the tree is empty, return -1.
int getMax() will return the value mapped to the largest key in the tree. If the tree is empty, return -1.
void remove(int key) will remove the key-value pair with the given key from the tree.
int[] getInorderKeys() will return an array of the keys in the tree in ascending order.
Note:

The tree should be ordered by the keys.
The tree should not contain duplicate keys. If the key is already present in the tree, the original key-value pair should be overridden with the new key-value pair.

Note: Most operations are O(logn) but O(n) in the worst case when the tree is just a straight line of nodes.
Insert, get, getMin, getMax, remove are all average case O(logn) and worst case O(n).
Only In-order traversal is consistently O(n) because we have to reach each node.
"""

class TreeNode:

    def __init__(self, k, v, l = None, r = None):
        self.key = k
        self.val = v
        self.left = l
        self.right = r

class TreeMap:
    
    def __init__(self):
        self.root = None
        self.InOrderKeys = []

    def insert(self, key: int, val: int) -> None: # O(logn) could be linear in one case
        self.InOrderKeys = []
        node = TreeNode(key, val)
        if self.root == None: # if the tree is empty
            self.root = node
            return
        else:
            # traverse the tree until we reach the point of insertion
            current = self.root
            while current:
                if key == current.key: # the key already exists
                    current.val = val
                    return
                elif key > current.key:
                    if current.right == None:
                        current.right = node
                        return
                    current = current.right
                else: # key < current.key
                    if current.left == None:
                        current.left = node
                        return
                    current = current.left
                   
    def get(self, key: int) -> int: # return val of the key O(logn) could be linear in one case
        current = self.root
        while current:
            if key == current.key:
                return current.val
            elif key > current.key: 
                current = current.right
            else: # key < current.key
                current = current.left
        return -1 # no key found

    def getMin(self) -> int: # return val of min key O(logn)
        if not self.root: # tree is empty
            return -1 
        # traverse to the left until we can't
        current = self.root
        while current.left: 
            current = current.left
        return current.val

    def getMax(self) -> int: # return val of max key O(logn)
        if not self.root: # tree is empty
            return -1 
        # traverse to the right until we can't
        current = self.root
        while current.right: 
            current = current.right
        return current.val

    def remove(self, key: int) -> None: #O(logn) to find O(logn) to remove
        self.InOrderKeys = []
        self.removeHelper(self.root, key, True)
        return
    
    def removeHelper(self, current, key, root): #O(logn)
        if current == None: # We did not find the key to remove
            return current
        if key == current.key: # We found the key
            if current.left == None:
                current = current.right
                if root:
                    self.root = current
            elif current.right == None:
                current = current.left
                if root:
                    self.root = current
            else: # two children
                current.key, current.val = self.maxLeftSubTree(current.left) # Replace the removed node with max of left subtree
                current.left = self.removeHelper(current.left, current.key, False) # Delete the copy of the node that replaced the removed node
            return current
        
        elif key > current.key:
            current.right = self.removeHelper(current.right, key, False)
        else: # key < current.key
            current.left = self.removeHelper(current.left, key, False)

    def maxLeftSubTree(self, leftRoot): # O(logn)
        # traverse to the right until we can't
        maxLeft = leftRoot
        while maxLeft.right: 
            maxLeft = maxLeft.right
        return maxLeft.key, maxLeft.val

    def getInorderKeys(self) -> list[int]: #O(n)
        current = self.root
        self.InOrderHelper(current)
        return self.InOrderKeys
        
    def InOrderHelper(self, current): # O(n) since we hit every node
        if not current: 
            return
        if current.left:
            self.InOrderHelper(current.left)
        self.InOrderKeys.append(current.key)
        self.InOrderHelper(current.right)


"""
Some of the functions (insert, get, getMin, getMax) can be accomplished through a simple while loop (or recursively).
However, removal and in-order traversal is best accomplished through recursion. 
Most of these functions are some version of DFS.


Input:
["insert", 1, 2, "get", 1, "insert", 4, 0, "getMin", "getMax"]

Output:
[null, 2, null, 2, 0]

Input:
["insert", 1, 2, "insert", 4, 2, "insert", 3, 7, "insert", 2, 1, "getInorderKeys", "remove", 1, "getInorderKeys"]

Output:
[null, null, null, null, [1, 2, 3, 4], null, [2, 3, 4]]
"""

