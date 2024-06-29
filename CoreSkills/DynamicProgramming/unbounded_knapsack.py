class Solution:
    def maximumProfit(self, profit: list[int], weight: list[int], capacity: int) -> int:
        """
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
        """

        # setup dp
        prev_cache = [0] * (capacity + 1)

        # execute dp
        for item in range(len(profit)):
            # for each item, calculate the max profit for each capacity
            curr_cache = [0] * (capacity + 1)
            for cap in range(capacity + 1): 
                # max profit if we don't include the item
                skip_profit = prev_cache[cap]
                
                include_profit = 0
                # profit if we can include item
                if weight[item] <= cap:
                    # profit of including is profit of this item and the profit from trying to include it again
                    include_profit = profit[item] + curr_cache[cap - weight[item]]
                
                curr_cache[cap] = max(skip_profit, include_profit)
            
            prev_cache = curr_cache
        
        return prev_cache[-1] # end of prev_cache contains max profit for max capacity






