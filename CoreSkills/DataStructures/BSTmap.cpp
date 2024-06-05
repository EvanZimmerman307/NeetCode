/*
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
*/

#include <utility>
#include <vector>
#include <iostream>

class TreeNode {

public:
    int key;
    int val;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
    
    TreeNode(int k, int v) {
        key = k;
        val = v;
    }
};

class TreeMap {

public:
    TreeNode* root; // the root tells us where the tree starts

    TreeMap() {
        std::cout << "New TREE" << std::endl;
        root = NULL;
    }

    void insert(int key, int val) {
        TreeNode* n = new TreeNode(key, val);
        if (root == NULL) { // if the tree is empty, this node is the root
            root = n;
            std::cout << "Inserted: " << key << std::endl;
            return;
        }
        // find where to insert
        TreeNode* current = root;
        while (current != NULL) {
            std::cout << "At Node: " << current->key << std::endl;
            // 1. Find the key already exists, update value
            if (key == current->key) {
                current->val = val;
                return;
            }
            // 2. Insert the key
            else if (key > current->key) {
                if (current->right == NULL){
                    current->right = n;
                    std::cout << "Inserted: " << key << std::endl;
                    return;
                }
                current = current->right;
            }
            else { // key < current->key
                if (current->left == NULL){
                    current->left = n;
                    std::cout << "Inserted: " << key << std::endl;
                    return;
                }
                current = current->left;
            }
        }
    }

    int get(int key) { // return the value mapped with the key
        TreeNode* current = root;
        while (current != NULL) {
            if (key == current->key) { // we found the key
                return current->val;
            }
            else if (key > current->key) {
                current = current->right;
            }
            else { //key < current->key
                current = current->left;
            }
        }
        // return -1 if key is not present
        return -1;
    }

    int getMin() { //return the value mapped to the smallest key in the tree
        // if the tree is empty, return -1
        if (root == NULL) {
            return -1;
        }
        // traverse left until we reach the left most leaf
        TreeNode* current = root;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->val;
    }

    int getMax() { //return the value mapped to the largest key in the tree
        // if the tree is empty, return -1
        if (root == NULL) {
            return -1;
        }
        // traverse right until we reach the right most leaf
        TreeNode* current = root;
        while (current->right != NULL) {
            current = current->right;
        }
        return current->val;
    }

    void remove(int key) {
        removeHelper(root, key);
        return;
    }

    TreeNode* removeHelper(TreeNode*& current, int key) { //recursive implementation with pointer to a node as argument makes things easier, 
    //since this is recursive we want to pass the pointer by reference, that way we are modifying the value of the originial pointer through the recursive calls
        while (current != NULL){
            if (key == current->key) { // we found the key to remove
                // 0 or 1 child case
                std::cout << "Removing key : " << key << std::endl; 
                if (current->left == NULL) {
                    std::cout << "Removing key : " << key << std::endl;
                    std::cout << "The key to the right of the root is: " << root->right->key << std::endl;
                    TreeNode* removed = current;
                    current = current->right;
                    delete removed;
                    std::cout << "Root key should be 4 but is: " << root->key << std::endl;
                }
                else if (current->right == NULL) {
                    TreeNode* removed = current;
                    current = current->left;
                    delete removed;
                }
                else { // 2 child case
                    // replace the node with the node from the max of the left subtree
                    std::pair<int,int> maxLeft = getMaxLeft(current->left);
                    current->key = maxLeft.first;
                    current->val = maxLeft.second;
                    // delete the node that we used to replce the current node.
                    current->left = removeHelper(current->left, current->key);
                }
                return current;
            }
            else if (key > current->key) {
                current->right = removeHelper(current->right, key);
            }
            else { //key < current->key
                current->left = removeHelper(current->left, key);
            }
        }
        return current;

    }

    std::pair<int,int> getMaxLeft(TreeNode* leftRoot) {
        // traverse right until we reach the right most leaf
        TreeNode* left_ptr = leftRoot;
        while (left_ptr->right != NULL) {
            left_ptr = left_ptr->right;
        }
        return std::make_pair(left_ptr->key, left_ptr->val);
    }


    std::vector<int> getInorderKeys() {
        std::vector<int> InOrderKeys;
        if (root == NULL) {
            return InOrderKeys;
        }
        return inOrderKeysHelper(root, InOrderKeys); //use the helper function, pass in the root
    }

    std::vector<int> inOrderKeysHelper(TreeNode* start, std::vector<int> &keyVector){ // pass in the vector by reference so we are pushing_back on the originial vector in the recursive calls
        TreeNode* current = start;
        if (current->left) { // go left while we can
            inOrderKeysHelper(current->left, keyVector);
        }
        keyVector.push_back(current->key); // process the root
        std::cout << "Appended: " << current->key << std::endl;
        if (current->right) { // start processing the right child
            inOrderKeysHelper(current->right, keyVector);
        }
        return keyVector;

    } 
};

int main() {
    TreeMap treemap = TreeMap();
    treemap.insert(1,2);
    treemap.insert(4,2);
    treemap.insert(3,7);
    treemap.insert(2,1);
    std::vector<int> inOrder = treemap.getInorderKeys();
    for (const int& value : inOrder) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    treemap.remove(1);

    std::vector<int> inOrder2 = treemap.getInorderKeys();
    for (const int& value : inOrder2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;

}

/*
Some of the functions (insert, get, getMin, getMax) can be accomplished through a simple while loop (or recursively).
However, removal and in-order traversal is best accomplished through recursion. 
Most of these functions are some version of DFS. For the recursive functions it is important to pass in some of the arguments by reference
since we want to modify the original variable through the recursive calls.


Input:
["insert", 1, 2, "get", 1, "insert", 4, 0, "getMin", "getMax"]

Output:
[null, 2, null, 2, 0]

Input:
["insert", 1, 2, "insert", 4, 2, "insert", 3, 7, "insert", 2, 1, "getInorderKeys", "remove", 1, "getInorderKeys"]

Output:
[null, null, null, null, [1, 2, 3, 4], null, [2, 3, 4]]
*/
