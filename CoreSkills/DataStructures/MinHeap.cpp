/*
"""
Design a Minimum Heap (aka a Priority Queue) class.

Your MinHeap class should support the following operations:

MinHeap() will initialize an empty minimum heap.
void push(int val) will add val to the heap.
int pop() will remove and return the smallest element in the heap. If the heap is empty, return -1.
int top() will return the smallest element in the heap without removing it. If the heap is empty, return -1.
void heapify(int[] nums) will build a minimum heap from nums.
Note: push and pop should be implemented in O(logn) time complexity, while top should be implemented in 
O(1), and heapify should be implemented in 
O(n) time complexity

Heaps have two properties:
1. Structure: Heaps are modeled as a complete binary tree (no holes in the binary tree).
Basically means we insert at the bottom level of the tree from left to right. 
2. Order: The descendants for each node are greater than that node (or less in the case of a max heap).
*/

#include <vector>
#include <iostream>

class MinHeap {
public:
    std::vector<int> heap;

    MinHeap() {
        heap.push_back(0);
    }

    void push(int val) {
        heap.push_back(val);
        if (heap.size() >= 2) { // only need to percolate up if we have more than the root
            percolateUp();
        }
        return;
    }

    void percolateUp() {
        int current = heap.size() - 1;
        while (current > 1 && heap[current/2] > heap[current]) { // integer division rounds down
            int parent = heap[current/2];
            heap[current/2] = heap[current];
            heap[current] = parent;
            current = current / 2;
        } 
        return;
    }

    int pop() {
        if (heap.size() < 2) { // empty heap
            return -1;
        }
        int smallest = top();
        heap[1] = heap[heap.size()-1]; // move last element to the top
        heap.pop_back(); // delete leaf copy of element
        percolateDown(1);
        return smallest;
    }

    void percolateDown(int index) {
        int current = index;

        while (current * 2 <= heap.size() -1) { // while left child exists
            if (current * 2 + 1 <= heap.size() -1 && heap[current * 2 + 1] < heap[current * 2]
                && heap[current * 2 + 1] < heap[current]) {
                    // if we have a right child & right less than left & right is less than parent
                    int parent = heap[current];
                    heap[current] = heap[current * 2 + 1];
                    heap[current * 2 + 1] = parent;
                    current = current * 2 + 1;
            }
            else if (heap[current * 2] < heap[current]) { // left less than parent
                int parent = heap[current];
                heap[current] = heap[current * 2];
                heap[current * 2] = parent;
                current = current * 2;
            }
            else{
                break; // not replacing with left or right, parent is less than both
            }
        }
        return;
    }

    int top() {
        if (heap.size() < 2) { // empty heap
            return -1;
        }
        return heap[1];
    }

    void heapify(const std::vector<int>& arr) {
        heap = {0};
        heap.insert(heap.end(), arr.begin(), arr.end());
        for (int i = 0; i < heap.size(); i++) {
            std::cout << heap[i];
        }
        
        //percolate down starting from the nodes that have children
        for (int startingPoint = (heap.size() - 1) / 2; startingPoint > 0; startingPoint--){
            std::cout << "startingPoint: " << startingPoint << std::endl;
            percolateDown(startingPoint);

            for (int i = 0; i < heap.size(); i++) {
                std::cout << heap[i];
            }
            std::cout << std::endl;
        }

        

        return;
    }
};

/*
Input:
["top", "push", 1, "top", "pop", "pop"]

Output:
[-1, null, 1, 1, -1]

Input:
["heapify", [1 2 3 4 5], "pop", "pop", "pop", "pop", "pop"]

Output:
[null, 1, 2, 3, 4, 5]
*/
