/*
Implement Merge Sort.

Merge Sort is a divide-and-conquer algorithm for sorting an array or list of elements. It works by recursively dividing the unsorted list into n sub-lists, each containing one element. Then, it repeatedly merges sub-lists to produce new sorted sub-lists until there is only one sub-list remaining.

Objective:

Given a list of key-value pairs, sort the list by key using Merge Sort. If two key-value pairs have the same key, maintain their relative order in the sorted list.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
*/

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
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
    std::vector<Pair> mergeSort(std::vector<Pair>& pairs) {
        if (pairs.size() <= 1) { // basecase: sorting one element
            //std::cout << pairs[0].key;
            return pairs;
        }

        // otherwise mergeSort the left and right sub vector
        int midIndex = (pairs.size() - 1) / 2;
        std::vector<Pair> leftVec;
        std::copy(pairs.begin(), pairs.begin() + midIndex + 1, std::back_inserter(leftVec));
        leftVec = mergeSort(leftVec);

        std::vector<Pair> rightVec;
        std::copy(pairs.begin() + midIndex + 1, pairs.end(), std::back_inserter(rightVec));
        rightVec = mergeSort(rightVec);

        // merge the sorted left and right sub vectors
        return merge(leftVec, rightVec);
    }

    std::vector<Pair> merge(std::vector<Pair> leftVec, std::vector<Pair> rightVec) {
        std::vector<Pair> mergedVec;
        int leftInd = 0;
        int rightInd = 0;

        while(leftInd < leftVec.size() && rightInd < rightVec.size()) {
            if (leftVec[leftInd].key <= rightVec[rightInd].key) { // <= maintains stable ordering
                mergedVec.push_back(leftVec[leftInd]);
                leftInd++;
            }
            else {
                mergedVec.push_back(rightVec[rightInd]);
                rightInd++;
            }
        }

        if (leftInd >= leftVec.size()) {
            std::copy(rightVec.begin() + rightInd, rightVec.end(), std::back_inserter(mergedVec));
        }
        else {
            std::copy(leftVec.begin() + leftInd, leftVec.end(), std::back_inserter(mergedVec));
        }

        return mergedVec;
    }
};
