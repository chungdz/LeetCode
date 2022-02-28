'''
741
You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through,
1 means the cell contains a cherry that you can pick up and pass through, or
-1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
 

Example 1:


Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
Example 2:

Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] is -1, 0, or 1.
grid[0][0] != -1
grid[n - 1][n - 1] != -1

基本思想
三维动态规划
将折返看成两个人同时出发，每次两人移动一格，因为步调一致所以dp[x1][y1][x2]就能代表所有case，y2可以计算出来
暴力搜索即可

不能用numpy，得自己写list，不然TLE
不需要修改self.g的数字，第一个人抵达的位置如果第二个人没抵达的话就一定无法抵达了
'''

class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        self.n = len(grid)
        self.dp = [[[-1] * self.n for _1 in range(self.n)] for _2 in range(self.n)]
        self.g = grid
        self.directions = [[1, 0, 1, 0], [1, 0, 0, 1], [0, 1, 1, 0], [0, 1, 0, 1]]
        # if no path, dfs return -2, so use max function
        return max(self.dfs(0, 0, 0), 0)
    
    def isValid(self, r, c):
        if r < self.n and c < self.n and self.g[r][c] != -1:
            return True
        return False
    
    def dfs(self, x1, y1, x2):
        if self.dp[x1][y1][x2] != -1:
            return self.dp[x1][y1][x2]
        y2 = x1 + y1 - x2
        if x1 == self.n - 1 and y1 == self.n - 1:
            self.dp[x1][y1][x2] = self.g[x1][y1]
            return self.dp[x1][y1][x2]
        
        cur_pick = 0
        # r1 = self.g[x1][y1]
        # r2 = self.g[x2][y2]
        if x1 == x2 and y1 == y2:
            cur_pick = self.g[x1][y1]
            # self.g[x1][y1] = 0
        else:
            cur_pick += self.g[x1][y1]
            # self.g[x1][y1] = 0
            cur_pick += self.g[x2][y2]
            # self.g[x2][y2] = 0
        
        find_path = False
        max_cherry = 0
        for ax1, ay1, ax2, ay2 in self.directions:
            nx1 = x1 + ax1
            ny1 = y1 + ay1
            nx2 = x2 + ax2
            ny2 = y2 + ay2
            if self.isValid(nx1, ny1) and self.isValid(nx2, ny2):
                pick_num = self.dfs(nx1, ny1, nx2)
                if pick_num != -2:
                    find_path = True
                    max_cherry = max(max_cherry, pick_num)
        
        # reconstruct
        # self.g[x1][y1] = r1
        # self.g[x2][y2] = r2
        
        if not find_path:
            self.dp[x1][y1][x2] = -2
            return -2
        
        self.dp[x1][y1][x2] = cur_pick + max_cherry

        return self.dp[x1][y1][x2]

