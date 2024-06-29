#include <vector>
#include <algorithm>

class Solution {
public:
    int maximumProfit(std::vector<int>& profit, std::vector<int>& weight, int capacity) {
        /*
        - items have a weight and profit, backpack has a capacity
        - calculate max profit for the given capacity (the total weight of the items selected
        can not exceed the capacity)
        - each item can be selected an unlimited number of times.
        - profit is a list where profit[i] is the profit of item i
        - weight is a list where weight[i] is the weight of item i
        - capacity is the backpacks maximum capacity

        Input:
        profit = [4, 4, 7, 1]
        weight = [5, 2, 3, 1]
        capacity = 8

        Output:
        18

        How do we go about picking items? We can ask ourselves for each item, should we include,
        should we not, and if we do include it, how many times should we include the item? Basically,
        we need to ask "if we pick up an item, what is the maximum profit we can achieve 
        given the remaining capacity?"
        
        Bottom-up dynamic programming approach that uses memoization.
        Time complexity: O(n*m), where n is num items and m is capacity
        Space complexity: O(m)
        */
        
        // setup the bottom-up approach with dummy cache for no item
        std::vector<int> prev_cache(capacity + 1, 0);

        // execute bottom-up dp
        for (int item = 0; item < profit.size(); item++) {
            std::vector<int> curr_cache(capacity + 1, 0);
            // calculate max profit for each capacity
            for (int cap = 0; cap < capacity + 1; cap++) {
                // do we include the item at this capacity or skip?
                int skip_profit = prev_cache[cap];
                int include_profit = 0;

                // profit if we can include the item
                if (weight[item] <= cap) {
                    // profit of including the item plus profit of including it again with remaining capacity
                    include_profit = profit[item] + curr_cache[cap - weight[item]];
                }

                curr_cache[cap] = std::max(skip_profit, include_profit);
            }

            prev_cache = curr_cache;
        }
        return prev_cache[capacity]; // end of prev_cache will contain max profit for max capacity
    }
};
