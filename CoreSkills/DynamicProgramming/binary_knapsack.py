class Solution:
    def maximumProfit(self, profit: list[int], weight: list[int], capacity: int) -> int:
        """
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
        """

        # make a grid to store answers of subproblems 
        num_items = len(profit)
        # grid is size num_times x capacity + 1
        prev_cache = [0] * (capacity + 1) 
        
        # begin filling up the grid 
        for n in range(num_items):
            curr_cache = [0] * (capacity + 1)
            # for each item, calculate the max profit from including that item or not including it for each capacity
            for c in range(capacity + 1):
                skip = 0 # profit from not including the item
                include = 0 # profit from including the item
                skip = prev_cache[c]
                
                if weight[n] <= c: # if the weight of the item does not exceed the capacity
                    include = profit[n] + prev_cache[c - weight[n]] # profit of this item plus max profit we can achieve with remaining capacity and items

                curr_cache[c] = max(skip, include)
        
            prev_cache = curr_cache
        
        print(prev_cache)
        return prev_cache[capacity] # bottom right of cache contains max profit for max capacity considering all items




 


        
