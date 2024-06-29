#include <vector>
#include <algorithm>

class Solution {
public:
    int maximumProfit(std::vector<int>& profit, std::vector<int>& weight, int capacity) {
        /*
        - list of items, each item has weight and profit
        - goal is to maximize profit given a capacity
        - select items such that the total weight does not exceed the capacity
        - can only select an item once
        - profit: array where profit[i] is the profit of ith item
        - weight: array where weight[i] is the weight of ith item
        - capacity: max weight the backpack can hold
        - have a total of n items

        Input:
        profit = [4, 4, 7, 1]
        weight = [5, 2, 3, 1]
        capacity = 8

        Output:
        12


        How to choose items? we can break it down into sub-problems. If we pick an item,
        what is the maximum profit we can achieve with the remaining capacity. 
        If we don't pick an item, capacity is unchanged, but what is the max profit we can 
        achieve from the selection of other items. We will use memoization to store the results 
        of subproblems (like a cache) because we will frequently compute the same subproblem.
        */

        // setup bottom-up approach with dummy cache
        std::vector<int> prev_cache(capacity + 1, 0);

        // execute bottom-up dp with memoization
        for (int item = 0; item < profit.size(); item++) {
            // for each item calculate the max profit for each possible capacity
            std::vector<int> curr_cache(capacity + 1, 0);
            for (int cap = 0; cap < capacity + 1; cap++) {
                // for a given item and cap, we can either include the item or not
                int skip_profit = prev_cache[cap];
                int include_profit = 0;

                if (weight[item] <= cap) {
                    // include profit is the profit of this item + max profit we can get from 
                    // including previous items for remaining capacity
                    include_profit = profit[item] + prev_cache[cap - weight[item]];
                }
                curr_cache[cap] = std::max(skip_profit, include_profit);
            }

            prev_cache = curr_cache;
        }
        return prev_cache.back(); // return profit for max capacity
    }
};
