"""
Implement Merge Sort.

Merge Sort is a divide-and-conquer algorithm for sorting an array or list of elements. It works by recursively dividing the unsorted list into n sub-lists, each containing one element. Then, it repeatedly merges sub-lists to produce new sorted sub-lists until there is only one sub-list remaining.

Objective:

Given a list of key-value pairs, sort the list by key using Merge Sort. If two key-value pairs have the same key, maintain their relative order in the sorted list.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
"""

# Definition for a pair.
class Pair:
    def __init__(self, key: int, value: str):
        self.key = key
        self.value = value

class Solution:
    def mergeSort(self, pairs: list[Pair]) -> list[Pair]: # O(nlogn)
        self.mergeSortHelper(pairs, 0, len(pairs) - 1)
        return pairs
    
    def mergeSortHelper(self, pairs: list[Pair], start: int, end: int) -> None:
        # recursively divide the input into n sublists
        # base case sublist contains one element
        if start >= end:
            return
        
        # otherwise divide the input list in half and mergesort each half
        midIndex = (start + end) // 2
        self.mergeSortHelper(pairs, start, midIndex)
        self.mergeSortHelper(pairs, midIndex + 1, end)

        # now merge the sorted subarrays
        self.merge(pairs, start, midIndex, end)

    def merge(self, pairs: list[Pair], start: int, mid: int, end: int) -> None:
        leftArr = pairs[start:mid+1]
        rightArr = pairs[mid+1:end+1]
        #if left, less than right append from the left, otherwise append from the right
        #don't go out of bounds in either case
        leftInd = 0
        rightInd = 0
        insertAt = start

        # append from smallest element from left or right sub list
        while leftInd < len(leftArr) and rightInd < len(rightArr):
            if leftArr[leftInd].key <= rightArr[rightInd].key:
                pairs[insertAt] = leftArr[leftInd]
                leftInd += 1
                insertAt += 1
            else:
                pairs[insertAt] = rightArr[rightInd]
                rightInd += 1
                insertAt += 1
        
        # once we append an entire sublist, just append the other sublist
        while leftInd < len(leftArr):
            pairs[insertAt] = leftArr[leftInd]
            leftInd += 1
            insertAt += 1
        
        while rightInd < len(rightArr):
            pairs[insertAt] = rightArr[rightInd]
            rightInd += 1
            insertAt += 1

        return



"""
Input:
pairs = [(5, "apple"), (2, "banana"), (9, "cherry"), (1, "date"), (9, "elderberry")]

Output:
[(1, "date"), (2, "banana"), (5, "apple"), (9, "cherry"), (9, "elderberry")]

Input:
pairs = [(3, "cat"), (2, "dog"), (3, "bird")]

Output:
[(2, "dog"), (3, "cat"), (3, "bird")]
"""