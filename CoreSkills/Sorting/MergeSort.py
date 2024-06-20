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
        # recursively divide the input into n sublists
        # basecase sublist contains one element
        if len(pairs) <= 1:
            return pairs
        
        # otherwise divide the input list in half and mergesort each half
        midIndex = ((len(pairs))  - 1) // 2
        #print(midIndex)
        left_subarray = self.mergeSort(pairs[:midIndex + 1])
        right_subarray = self.mergeSort(pairs[midIndex+1:])

        # now merge the sorted subarrays
        return self.merge(left_subarray, right_subarray)

    def merge(self, leftList: list[Pair], rightList: list[Pair]) -> list[Pair]:
        sortedList = []
        #if left, less than right append from the left, otherwise append from the right
        #don't go out of bounds in either case
        leftInd = 0
        rightInd = 0

        # append from smallest element from left or right sub list
        while leftInd < len(leftList) and rightInd < len(rightList):
            print(leftList[leftInd].key)
            print(rightList[rightInd].key)
            if leftList[leftInd].key <= rightList[rightInd].key:
                sortedList.append(leftList[leftInd])
                leftInd += 1
            else:
                sortedList.append(rightList[rightInd])
                rightInd += 1
                print("here")
        
        # once we append an entire sublist, just append the other sublist
        if leftInd == len(leftList):
            sortedList = sortedList + rightList[rightInd:]
        else:
            sortedList = sortedList + leftList[leftInd:]

        return sortedList

"""
Input:
pairs = [(5, "apple"), (2, "banana"), (9, "cherry"), (1, "date"), (9, "elderberry")]

Output:
[(1, "date"), (2, "banana"), (5, "apple"), (9, "cherry"), (9, "elderberry")]
"""