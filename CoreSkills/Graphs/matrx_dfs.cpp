/*
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
*/

#include <vector>
#include <set>
// #include <tuple> needs a custom hash function for unordered sets
#include <utility> // for pair
#include <iostream>

class Solution {
public:
    int countPaths(std::vector<std::vector<int>>& grid) {
        /*
        - unique paths from top left to bottom right
        - can only traverse 0's not 1's
        - only move vertically or horizontally
        - can't visit the same cell twice on a path
        - this is a dfs problem (recursive)
        */

        if (grid[0][0] == 1) { // edge case where we start on a 1
            return 0;
        }
        else {
            std::set<std::pair<int, int>> visited;
            visited.insert(std::make_pair(0,0));
            return countPathsDFS(grid, 0, 0, visited);
        }

    }

    int countPathsDFS(std::vector<std::vector<int>>& grid, int row, int col, std::set<std::pair<int, int>>& visited) {
        int paths = 0;
        std::cout << "row: " << row << " col: " << col << std::endl;

        // base case: reached the bottom right corner
        if (row == grid.size() - 1 && col == grid[0].size() - 1) {
            return 1;
        }

        // otherwise we will traverse the grid - left, right, up, down
        std::vector<std::vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int i = 0; i < directions.size(); i++) {
            int newrow = row + directions[i][0];
            int newcol = col + directions[i][1];
            std::pair<int, int> cell_pair = std::make_pair(newrow, newcol);

            // we can only go to a cell that is in bounds, a 0, and unvisited
            if (newrow >= 0 && newrow < grid.size() && newcol >= 0 && newcol < grid[0].size()
            && grid[newrow][newcol] == 0 && visited.find(cell_pair) == visited.end()) {
                visited.insert(cell_pair);
                paths = paths + countPathsDFS(grid, newrow, newcol, visited);
                visited.erase(cell_pair);
            }
        }
        return paths;
    }
};
