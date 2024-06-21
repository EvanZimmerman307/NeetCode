"""
Implement Quick Sort.

Quick Sort is a divide-and-conquer sorting algorithm that works by partitioning an array into two smaller sub-arrays based on a pivot element. The elements less than the pivot go to the left sub-array and those greater go to the right sub-array. The algorithm then recursively sorts the sub-arrays.

Objective:

Given a list of key-value pairs, sort the list by key using Quick Sort. For each partitioning step:

Use the right-most element as the pivot.
Elements less than the pivot should be placed to the left of the pivot, and elements greater than or equal to the pivot should be placed to the right of the pivot.
The correctness of your solution will be determined based on these requirements.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
"""

# Definition for a pair.
class Pair:
     def __init__(self, key: int, value: str):
         self.key = key
         self.value = value
class Solution:
    def quickSort(self, pairs: list[Pair]) -> list[Pair]: # O(n^2) worst case O(nlogn) average case
        # Quicksort is done in place, we will recursively call a helper function that takes indices as arguments to accomplish this
        self.quickSortHelper(pairs, 0, len(pairs) - 1)
        return pairs
    
    def quickSortHelper(self, pairs: list[Pair], start: int, end: int) -> None:
        if start >= end: # base case: split down to one element
            return
        
        # partition array
        pivot = pairs[end].key
        swapInd = start # index we are swapping with
        for i in range (start, end + 1):
            if pairs[i].key < pivot: # swap
                temp = pairs[swapInd]
                pairs[swapInd] = pairs[i]
                pairs[i] = temp
                swapInd += 1
            
            if i >= end: #swap pivot, pivot is at swapInd
                temp = pairs[swapInd]
                pairs[swapInd] = pairs[i]
                pairs[i] = temp
        
        # quicksort the left and right partitions
        self.quickSortHelper(pairs, start, swapInd - 1)
        self.quickSortHelper(pairs, swapInd + 1, end)

        return
        
"""
Input:
pairs = [(3, "cat"), (2, "dog"), (3, "bird")]

Output:
[(2, "dog"), (3, "bird"), (3, "cat")]

Input:
pairs = [(5, "apple"), (9, "banana"), (9, "cherry"), (1, "date"), (9, "elderberry")]

Output:
[(1, "date"), (5, "apple"), (9, "elderberry"), (9, "cherry"), (9, "banana")]

"""
            
            

        