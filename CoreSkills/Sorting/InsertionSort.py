"""
Implement Insertion Sort and return intermediate states.

Insertion Sort is a simple sorting algorithm that builds the sorted list one element at a time, from left to right. It works by repeatedly taking an element from the unsorted portion and inserting it into its correct position in the sorted portion of the list.

Objective:

Given a list of key-value pairs, sort the list by key using Insertion Sort. Return a list of lists showing the state of the array after each insertion. If two key-value pairs have the same key, maintain their relative order in the sorted list.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
"""
# Definition for a pair.
# class Pair:
#     def __init__(self, key: int, value: str):
#         self.key = key
#         self.value = value
class Solution:
    def insertionSort(self, pairs: list[Pair]) -> list[list[Pair]]: # O(N^2)
        output = []

        for ind in range(0, len(pairs)):
            prev_ind = ind - 1
            while prev_ind >= 0 and pairs[prev_ind].key > pairs[ind].key: # don't swap if equal - maintain stable order
                # swap pairs
                temp = pairs[prev_ind]
                pairs[prev_ind] = pairs[ind]
                pairs[ind] = temp

                # updating indexes
                ind = prev_ind
                prev_ind -= 1 

            output.append(pairs[:])
        
        return output

"""
Input:
pairs = [(5, "apple"), (2, "banana"), (9, "cherry")]

Output:
[[(5, "apple"), (2, "banana"), (9, "cherry")], 
 [(2, "banana"), (5, "apple"), (9, "cherry")], 
 [(2, "banana"), (5, "apple"), (9, "cherry")]]

 First element in the output is the input.
 After each insertion into the sorted list, append the entire list of pairs to the output
 """