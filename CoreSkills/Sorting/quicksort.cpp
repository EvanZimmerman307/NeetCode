/*
Implement Quick Sort.

Quick Sort is a divide-and-conquer sorting algorithm that works by partitioning an array into two smaller sub-arrays based on a pivot element. The elements less than the pivot go to the left sub-array and those greater go to the right sub-array. The algorithm then recursively sorts the sub-arrays.

Objective:

Given a list of key-value pairs, sort the list by key using Quick Sort. For each partitioning step:

Use the right-most element as the pivot.
Elements less than the pivot should be placed to the left of the pivot, and elements greater than or equal to the pivot should be placed to the right of the pivot.
The correctness of your solution will be determined based on these requirements.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
*/

#include <iostream>
#include <vector>
#include <string>

// Definition for a Pair
class Pair {
    public:
        int key;
        std::string value;

        Pair(int key, std::string value) : key(key), value(value) {}
};
class Solution {
public:
    std::vector<Pair> quickSort(std::vector<Pair>& pairs) { // O(n^2) worst case; O(nlogn) average
        // quickSort is completed in-place
        if (pairs.size() <= 0) { // edge case where we sort an empty list
            return pairs;
        }
        return quickSortHelper(pairs, 0, pairs.size() - 1);
    }

    std::vector<Pair> quickSortHelper(std::vector<Pair>& pairs, int start, int end) {
        // basecase: subarray is single element
        if(start >= end) {
            return pairs;
        }

        // partition
        int pivot = pairs[end].key; // right most key
        int insert = start;
        for (int i = start; i <= end; i++) {
            if (pairs[i].key < pivot) { // swap with element at insert index
                Pair temp = pairs[insert];
                pairs[insert] = pairs[i];
                pairs[i] = temp;
                insert++;
            }

            if (i == end) { // reached the pivot, swap with pair at insert
                Pair temp = pairs[insert];
                pairs[insert] = pairs[i];
                pairs[i] = temp;
            }
        }

        // quick sort left and right partitions in-place
        quickSortHelper(pairs, start, insert - 1); // pivot is at insert index and we can ignore pivot
        quickSortHelper(pairs, insert + 1, end);

        // finished recursive sorting
        return pairs;
    }
};
