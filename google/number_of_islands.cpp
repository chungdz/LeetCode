#include<vector>
using namespace std;

/*
200

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.


基本思想

二维深度搜索

每次遇到新的岛就遍历整个岛，修改状态，然后岛屿数量加一



**/

class Solution {
    int row, col;
    int total_island = 0;

    void search_island(int m, int n, vector<vector<char>>& grid){
        if(m < 0 || n < 0 || m >= row || n >= col){
            return;
        }
        if(grid[m][n] == '0' || grid[m][n] == '2'){return;}
        // grid[m][n] must equal 1
        grid[m][n] = '2';

        search_island(m + 1, n, grid);
        search_island(m - 1, n, grid);
        search_island(m, n + 1, grid);
        search_island(m, n - 1, grid);
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        row = grid.size();
        col = grid[0].size();

        for(int i = 0;i < row;++i){
            for(int j = 0;j < col;++j){
                if(grid[i][j] == '1'){
                    total_island += 1;
                    search_island(i, j, grid);
                }
            }
        }

        return total_island;
    }
};