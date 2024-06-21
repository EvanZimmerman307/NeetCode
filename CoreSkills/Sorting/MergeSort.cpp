/*
Implement Merge Sort.

Merge Sort is a divide-and-conquer algorithm for sorting an array or list of elements. It works by recursively dividing the unsorted list into n sub-lists, each containing one element. Then, it repeatedly merges sub-lists to produce new sorted sub-lists until there is only one sub-list remaining.

Objective:

Given a list of key-value pairs, sort the list by key using Merge Sort. If two key-value pairs have the same key, maintain their relative order in the sorted list.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
*/

// Definition for a Pair
class Pair {
public:
    int key;
    std::string value;

     Pair(int key, std::string value) : key(key), value(value) {}
};
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

class Solution {
public:
    std::vector<Pair> mergeSort(std::vector<Pair>& pairs) { // O(nlogn)
        mergeSortHelper(pairs, 0, pairs.size() - 1);
        return pairs;
    }

    void mergeSortHelper(std::vector<Pair>& pairs, int start, int end) {
        if (start >= end) { // basecase: sorting one element
            return;
        }

        // otherwise mergeSort the left and right sub vector
        int midIndex = (start + end) / 2;
        mergeSortHelper(pairs, start, midIndex);
        mergeSortHelper(pairs, midIndex + 1, end);
        // merge the sorted left and right sub vectors
        merge(pairs, start, midIndex, end);
        return;
    }

    void merge(std::vector<Pair>& pairs, int s, int m, int e) {
        // Need to make copies of left and right subarrays for inserting
        std::vector<Pair> leftVec(pairs.begin() + s, pairs.begin() + m + 1);
        std::vector<Pair> rightVec(pairs.begin() + m + 1, pairs.begin() + e + 1);

        int leftInd = 0;
        int rightInd = 0;
        int insert = s;

        while(leftInd < leftVec.size() && rightInd < rightVec.size()) { // merge smallest element from left and right
            if (leftVec[leftInd].key <= rightVec[rightInd].key) { // <= maintains stable ordering
                pairs[insert] = leftVec[leftInd];
                leftInd++;
                insert++;
            }
            else {
                pairs[insert] = rightVec[rightInd];
                rightInd++;
                insert++;
            }
        }

        while (rightInd < rightVec.size()) { // merge the rest of the right if necessary
            pairs[insert] = rightVec[rightInd];
            rightInd++;
            insert++;
        }

        while (leftInd < leftVec.size()) { // merge the rest of the left if necessary
            pairs[insert] = leftVec[leftInd];
            leftInd++;
            insert++;
        }

        return;
    }
};

/*
Input:
pairs = [(5, "apple"), (2, "banana"), (9, "cherry"), (1, "date"), (9, "elderberry")]

Output:
[(1, "date"), (2, "banana"), (5, "apple"), (9, "cherry"), (9, "elderberry")]

Input:
pairs = [(3, "cat"), (2, "dog"), (3, "bird")]

Output:
[(2, "dog"), (3, "cat"), (3, "bird")]

*/