/*
Implement Insertion Sort and return intermediate states.

Insertion Sort is a simple sorting algorithm that builds the sorted list one element at a time, from left to right. It works by repeatedly taking an element from the unsorted portion and inserting it into its correct position in the sorted portion of the list.

Objective:

Given a list of key-value pairs, sort the list by key using Insertion Sort. Return a list of lists showing the state of the array after each insertion. If two key-value pairs have the same key, maintain their relative order in the sorted list.

Input:

pairs - a list of key-value pairs, where each key-value has an integer key and a string value. (0 <= pairs.length <= 100).
*/
// Definition for a Pair
// class Pair {
// public:
//     int key;
//     string value;
//
//     Pair(int key, string value) : key(key), value(value) {}
// };

#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<std::vector<Pair>> insertionSort(std::vector<Pair>& pairs) {
        std::vector<std::vector<Pair>> output;

        for (int ind = 0; ind < pairs.size(); ind++) {
            std::cout << ind << std::endl;
            // insert pairs[ind]
            int prev_ind = ind - 1;
            while (prev_ind >= 0 && pairs[prev_ind].key > pairs[prev_ind + 1].key) { //swap while prev index is greater than current index
                // swapping pairs
                Pair temp = Pair(pairs[prev_ind].key, pairs[prev_ind].value);
                pairs[prev_ind] = pairs[prev_ind + 1];
                pairs[prev_ind + 1] = temp;

                // update previous
                prev_ind--;
            }
            // add the state of the array after insertion to the output
            output.push_back(pairs);
            std::cout << "added array after insertion" << std::endl;
        }

        return output;
    }
};

/*
Input:
pairs = [(5, "apple"), (2, "banana"), (9, "cherry")]

Output:
[[(5, "apple"), (2, "banana"), (9, "cherry")], 
 [(2, "banana"), (5, "apple"), (9, "cherry")], 
 [(2, "banana"), (5, "apple"), (9, "cherry")]]

 First element in the output is the input.
 After each insertion into the sorted list, append the entire list of pairs to the output
*/