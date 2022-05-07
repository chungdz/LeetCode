'''
130 Surrounded Regions

Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

 

Example 1:


Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Surrounded regions should not be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
Example 2:

Input: board = [["X"]]
Output: [["X"]]
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] is 'X' or 'O'.

基本思想

并查集，同一个region的话放在一个set，然后如果出现靠边的node，就将父节点标注为不可翻
'''

class DisjointS:
    def __init__(self) -> None:
        self.nodes = {}

    def make_set(self, v):
        assert(v not in self.nodes)
        self.nodes[v] = v
    
    def find_set(self, v):
        assert(v in self.nodes)
        cp = self.nodes[v]
        if cp == v:
            return v
        
        self.nodes[v] = self.find_set(cp)
        return self.nodes[v]
    
    def union(self, x, y):
        nx = self.find_set(x)
        ny = self.find_set(y)

        if nx == ny:
            return False
        else:
            self.nodes[ny] = nx
        return True

class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.b = board
        self.m = len(board)
        self.n = len(board[0])
        self.visited = [[False] * self.n for _ in range(self.m)]
        self.us = DisjointS()
        self.notIsolated = set()
        self.dir = [[1, 0], [-1, 0], [0, 1], [0, -1]]

        for i in range(self.m):
            for j in range(self.n):
                if self.visited[i][j] or self.b[i][j] == "X":
                    continue
                self.us.make_set((i, j))
                self.visited[i][j] = True
                self.dfs(i, j)

        for i in range(self.m):
            for j in range(self.n):
                if self.b[i][j] == "X":
                    continue
                pr, pc = self.us.find_set((i, j))
                if not (pr, pc) in self.notIsolated:
                    self.b[i][j] = "X"
    
    def isValid(self, r, c):
        if r < 0 or c < 0 or r > self.m - 1 or c > self.n - 1:
            return False
        return True
    
    def dfs(self, r, c):
        if r == self.m - 1 or c == self.n - 1 or r == 0 or c == 0:
            pr, pc = self.us.find_set((r, c))
            self.notIsolated.add((pr, pc))
        
        for ar, ac in self.dir:
            newr = r + ar
            newc = c + ac
            if self.isValid(newr, newc) and not self.visited[newr][newc] and self.b[newr][newc] == 'O':
                self.visited[newr][newc] = True
                self.us.make_set((newr, newc))
                self.us.union((r, c), (newr, newc))
                self.dfs(newr, newc)
        



