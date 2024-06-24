/*
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
*/

#include <queue> // to order processing cells
#include <set> // to track visited cells
#include <utility> // to reprsent coordinates in the grid

class Solution {
public:
    int shortestPath(std::vector<std::vector<int>>& grid) {
        /*
        - can only traverse 0's
        - length of shortest path from top left to bottom right
        - may only move vertically or horizontally
        - return -1 if no path
        - How to calculate shortest path? BFS
        - Why? with BFS we see how many nodes are 1 move away, 2 moves, etc,
        - this will reveal the lowest number of moves to reach the bottom right
        */

        // edge case: starting on a cell that can not be traversed
        if (grid[0][0] == 1) {
            return -1;
        }

        int moves = 0;
        std::queue<std::pair<int,int>> q;
        std::set<std::pair<int,int>> visited;
        std::vector<std::vector<int>> directions = {{0,-1}, {0,1}, {-1,0}, {1,0}}; // left, right, up, down

        std::pair<int,int> start = std::make_pair(0,0);
        q.push(start);
        visited.insert(start);

        // begin bfs
        while (!q.empty()) {
            int length = q.size();
            for (int i = 0; i < length; i++) { // process all cells x moves away
                auto cell = q.front();
                q.pop();
                int row = cell.first;
                int col = cell.second;
                
                if (row == grid.size() - 1 && col == grid[0].size() - 1) { // reached bottom right
                    return moves;
                }

                // add valid adjacent cells to the queue for processing
                for (int j = 0; j < directions.size(); j++) {
                    int newrow = row + directions[j][0];
                    int newcol = col + directions[j][1];
                    auto newcoord = std::make_pair(newrow, newcol);

                    // check if moving adjacent cell is valid
                    if (newrow >= 0 && newrow < grid.size() && newcol >= 0 && newcol < grid[0].size()
                    && grid[newrow][newcol] == 0 && visited.find(newcoord) == visited.end()) {
                        // mark as visited and add to queue for processing
                        visited.insert(newcoord);
                        q.push(newcoord);
                    }
                }
            } 
            moves++;  
        }
        return -1;
    }
};
