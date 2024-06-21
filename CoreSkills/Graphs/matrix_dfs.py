"""
You are given a binary matrix Grid where 0s represent land and 1s represent rocks that can not be traversed.

Return the number of unique paths from the top-left corner of Grid to the bottom-right corner such that all traversed cells are land cells. 
You may only move vertically or horizontally through land cells. For an individual unique path you cannot visit the same cell twice.

Input: grid = [
  [0, 0, 0, 0],
  [1, 1, 0, 0],
  [0, 0, 0, 1],
  [0, 1, 0, 0]
]

Output:
2

"""

class Solution:
    def countPaths(self, grid: list[list[int]]) -> int:
        # 0's CAN be traversed, 1's can NOT
        # number of unique paths from top left to bottom right
        # only move vertically or horizontally
        # can not visit the same cell twice on a path
        # unique paths is a depth first search problem

        if grid[0][0] == 1: # edge case - start at a cell you can't traverse
            return 0
        else:
            visited = set()
            visited.add((0,0))
            return self.countPathsDFS(grid, 0, 0, visited)
    
    def countPathsDFS(self, grid: list[list[int]], row: int, col: int, visited: set[(int,int)]) -> int:
        # base case: we reached the bottom right
        print("visiting: " + str(row) + str(col))

        if row == len(grid) - 1 and col == len(grid[0]) - 1:
            return 1
        
        paths = 0
        
        # we can move left, right, up, down
        directions = [[0, -1], [0, 1], [-1, 0], [1, 0]] 
        for dr,dc in directions:
            newrow = row + dr
            newcol = col + dc
            # we can only move in bounds, to a 0, and to an unvisited cell
            if (newrow >= 0 and newrow < len(grid) 
            and newcol >= 0 and newcol < len(grid[0])
            and grid[newrow][newcol] == 0 and (newrow, newcol) not in visited):
                visited.add((newrow, newcol))
                paths = paths + self.countPathsDFS(grid, newrow, newcol, visited)
                visited.remove((newrow, newcol)) # remove a cell from visited so we can visit on another path
        
        return paths






        

