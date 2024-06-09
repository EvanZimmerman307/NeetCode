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
"""


class MinHeap:
    
    def __init__(self):
        self.heap = [0]

    def push(self, val: int) -> None: # add a value to the heap O(logn)
        self.heap.append(val)
        self.percolateUp()
        print(self.heap)
        return
    
    def percolateUp(self) -> None: # For pushing O(logn)
        if len(self.heap) == 2: # just the root in the heap
            return
        current = len(self.heap) - 1 # index we just inserted at
        while self.heap[current] < self.heap[current // 2] and current > 1 : # while the child is less than the parent
            # swap the parent and child
            parent_val = self.heap[current // 2]
            self.heap[current // 2] = self.heap[current]
            self.heap[current] = parent_val
            current = current // 2
        return

    def pop(self) -> int: # remove and return the smallest element (top) O(logn)
        if len(self.heap) == 1: # heap is empty
            return -1
        smallest = self.top()
        print("Popping: ", smallest)
        self.heap[1] = self.heap[-1] # move the element from the end to the top.
        del(self.heap[len(self.heap) - 1]) # delete the last element
        self.percolateDown(1) # move the last element (at the root) down the heap
        return smallest
    
    def percolateDown(self, index: int) -> None:
        # We want to swap with the smallest child
        # # 3 cases: swap with left, swap with right, don't swap

        current = index # the value to percolate down is at index 1
        while current * 2 <= len(self.heap) - 1: # while we have a left child
            
            if (current * 2 + 1 <= len(self.heap) - 1 
                and self.heap[current * 2 + 1] < self.heap[current * 2] 
                and self.heap[current * 2 + 1] < self.heap[current]): # right is less than left and parent, swap right
                child_val = self.heap[current * 2 + 1]
                self.heap[current * 2 + 1] = self.heap[current]
                self.heap[current] = child_val
                current = current * 2 + 1
            
            elif self.heap[current * 2] < self.heap[current]: # left is less than parent, swap with left
                child_val = self.heap[current * 2]
                self.heap[current * 2] = self.heap[current]
                self.heap[current] = child_val
                current = current * 2
            else:
                break # stop swapping
                    
        return
                
    def top(self) -> int:
        if len(self.heap) == 1: # heap is empty
            return -1
        return self.heap[1]
        

    def heapify(self, nums: list[int]) -> None:
        # We can heapify an array by calling percolateDown on each of the elements, 
        # that will shift it down to its appropriate position. We have to iterate through the input list,
        # but we can start at the mid point and work our way up because the bottom half of the list has no elements below 

        self.heap = [0] + nums # set the underlying heap
        startingPoint = (len(self.heap) - 1) // 2 
        for i in range(startingPoint, 0, -1): # percolateDown starting halfway up and go up
            print("current percolate index for heapify: ", i)
            self.percolateDown(i)
        return

"""
Input:
["top", "push", 1, "top", "pop", "pop"]

Output:
[-1, null, 1, 1, -1]

Input:
["heapify", [1 2 3 4 5], "pop", "pop", "pop", "pop", "pop"]

Output:
[null, 1, 2, 3, 4, 5]
"""     
        