"""
You are given a binary matrix Grid where 0s represent land and 1s represent rocks that can not be traversed.

Return the length of the shortest path from the top-left corner of Grid to the bottom-right corner such that all traversed cells are land cells. You may only move vertically or horizontally through land cells.

Note:

If there is no such path, return -1.
The length of a path is the number of moves from the starting cell to the ending cell.

Input: grid = [
  [0, 0, 0, 0],
  [1, 1, 0, 0],
  [0, 0, 0, 1],
  [0, 1, 0, 0]
]

Output:
6
"""

from collections import deque

class Solution:
    def shortestPath(self, grid: list[list[int]]) -> int:
        """
        - can only traverse 0's
        - return the length of the shortest path from top left to bottom right
        - only move vertically or horizontally
        - return -1 if no path

        This a bfs problem. We will use bfs because we want to process all possible cells we can reach move by move.
        i.e. process all cells one move away, now two moves away, etc...
        BFS is iterative and uses a queue to manage what cells to process.
        """

        moves = 0
        
        # initialize queue
        q = deque()
        q.append((0,0))

        # initialize visited set
        visited = set()
        visited.add((0,0))

        # left, right, up, down
        directions = [[0, -1], [0, 1], [-1, 0], [1, 0]]

        # BFS
        while q: # while the queue is not empty
            for i in range(len(q)): # process cells in groups based on how many moves away
                cell = q.popleft()
                row = cell[0]
                col = cell[1]

                if row == len(grid) - 1 and col == len(grid[0]) - 1: # reached bottom right
                    return moves

                # consider possible moves
                for dr,dc in directions:
                    newrow = dr + row
                    newcol = dc + col
                    coord = (newrow, newcol)

                    # only add a cell to the queue if it is in bounds, not a 1, and unvisited
                    if (newrow >= 0 and newrow < len(grid) and newcol >= 0 and newcol < len(grid[0])
                    and grid[newrow][newcol] == 0 and coord not in visited):
                        visited.add(coord)
                        q.append(coord)
            
            moves += 1
        
        return -1









        