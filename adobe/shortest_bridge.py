
'''
934 Shortest Bridge
You are given an n x n binary matrix grid where 1 represents land and 0 represents water.

An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.

You may change 0's to 1's to connect the two islands to form one island.

Return the smallest number of 0's you must flip to connect the two islands.

 

Example 1:

Input: grid = [[0,1],[1,0]]
Output: 1
Example 2:

Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:

Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 

Constraints:

n == grid.length == grid[i].length
2 <= n <= 100
grid[i][j] is either 0 or 1.
There are exactly two islands in grid.

基本思想

宽搜，把第一个岛屿所有的点全部加入队列
'''
class Solution:
    def shortestBridge(self, grid: List[List[int]]) -> int:
        self.m = len(grid)
        self.n = self.m
        self.nlist = [[1, 0], [0, 1], [-1, 0], [0, -1]]
        self.q = []
        self.g = grid
        self.visited = [[False] * self.n for _ in range(self.m)]

        self.find_first_island()
        
        while len(self.q) > 0:
            cx, cy, cstep = self.q[0]
            self.q.pop(0)
            if grid[cx][cy] == 1 and cstep > 0:
                return cstep - 1
            
            for addx, addy in self.nlist:
                nx = cx + addx
                ny = cy + addy
                if self.isValid(nx, ny) and not self.visited[nx][ny]:
                    self.q.append((nx, ny, cstep + 1))
                    self.visited[nx][ny] = True

        return -1
    
    def find_first_island(self):
        for i in range(self.m):
            for j in range(self.n):
                if self.g[i][j] == 1:
                    self.dfs_island(i, j)
                    return

    def dfs_island(self, x, y):
        self.visited[x][y] = True
        self.q.append((x, y, 0))
        
        for addx, addy in self.nlist:
            nx = x + addx
            ny = y + addy
            if self.isValid(nx, ny) and self.g[nx][ny] == 1 and not self.visited[nx][ny]:
                self.dfs_island(nx, ny)
            
    def isValid(self, r, c):
        if r >= 0 and r < self.m and c >= 0 and c < self.n:
            return True
        return False
