'''
695 Max Area of Island


You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.

 

Example 1:


Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.
Example 2:

Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0 or 1.

基本思想 搜索
'''

class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        self.m = len(grid)
        self.n = len(grid[0])
        self.nlist = [[1, 0], [0, 1], [-1, 0], [0, -1]]
        self.grid = grid
        res = 0
        for i in range(self.m):
            for j in range(self.n):
                if self.isEmptyIsland(i, j):
                    res = max(res, self.dfs(i, j))
        return res
    
    def dfs(self, x, y):
        self.grid[x][y] = 2
        res = 1
        for addx, addy in self.nlist:
            nx = x + addx
            ny = y + addy
            if self.isValid(nx, ny) and self.isEmptyIsland(nx, ny):
                res += self.dfs(nx, ny)
        return res
    
    def isValid(self, r, c):
        if r >= 0 and r < self.m and c >= 0 and c < self.n:
            return True
        return False
    
    def isEmptyIsland(self, r, c):
        if self.grid[r][c] == 1:
            return True
        return False
