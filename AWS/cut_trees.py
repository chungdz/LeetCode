'''
675 Cut Off Trees for Golf Event
You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:

0 means the cell cannot be walked through.
1 represents an empty cell that can be walked through.
A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.

You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).

Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.

You are guaranteed that no two trees have the same height, and there is at least one tree needs to be cut off.

 

Example 1:


Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
Output: 6
Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
Example 2:


Input: forest = [[1,2,3],[0,0,0],[7,6,5]]
Output: -1
Explanation: The trees in the bottom row cannot be accessed as the middle row is blocked.
Example 3:

Input: forest = [[2,3,4],[0,0,5],[8,7,6]]
Output: 6
Explanation: You can follow the same path as Example 1 to cut off all the trees.
Note that you can cut off the first tree at (0, 0) before making any steps.
 

Constraints:

m == forest.length
n == forest[i].length
1 <= m, n <= 50
0 <= forest[i][j] <= 10^9

排序 记录 宽搜 / A*
'''
import heapq

class Solution:
    def cutOffTree(self, forest: List[List[int]]) -> int:
        nlist = []
        ndict = {}
        m = len(forest)
        n = len(forest[0])
        for i in range(m):
            for j in range(n):
                if forest[i][j] > 1:
                    nlist.append(forest[i][j])
                    ndict[forest[i][j]] = {
                        "x": i,
                        "y": j,
                        "min_dis": {}
                    }
        
        nlist = sorted(nlist)

        if forest[0][0] <= 1: 
            ndict[forest[0][0]] = {
                "x": 0,
                "y": 0,
                "min_dis": {}
            }

        self.ndict = ndict
        self.forest = forest
        self.direction = [[-1, 0], [1, 0], [0, 1], [0, -1]]
        self.m = m
        self.n = n

        step = 0
        pre = forest[0][0]
        for i in range(len(nlist)):
            cur_dis = self.astar(self.ndict[pre]["x"], self.ndict[pre]["y"], self.ndict[nlist[i]]["x"], self.ndict[nlist[i]]["y"])
            if cur_dis == -1:
                return -1
            step += cur_dis
            pre = nlist[i]
        
        return step
                
    
    def bfs(self, xfrom, yfrom, xto, yto):
        
        visited = set()
        visited.add((xfrom, yfrom))
        nqueue = [(xfrom, yfrom, 0)]

        while len(nqueue) > 0:
            curx, cury, curdis = nqueue[0]
            if curx == xto and cury == yto:
                return curdis
            nqueue.pop(0)

            for dx, dy in self.direction:
                nxtx = curx + dx
                nxty = cury + dy
                if(self.valid_point(nxtx, nxty, visited)):
                    nqueue.append((nxtx, nxty, 1 + curdis))
                    visited.add((nxtx, nxty))

        return -1
    
    def astar(self, sr, sc, tr, tc):
        R, C = len(self.forest), len(self.forest[0])
        heap = [(0, 0, sr, sc)]
        cost = {(sr, sc): 0}
        while heap:
            f, g, r, c = heapq.heappop(heap)
            if r == tr and c == tc: return g
            for nr, nc in ((r-1,c), (r+1,c), (r,c-1), (r,c+1)):
                if 0 <= nr < R and 0 <= nc < C and self.forest[nr][nc]:
                    ncost = g + 1 + abs(nr - tr) + abs(nc - tc)
                    if ncost < cost.get((nr, nc), 9999):
                        cost[nr, nc] = ncost
                        heapq.heappush(heap, (ncost, g + 1, nr, nc))
        return -1
    
    def valid_point(self, x, y, visited):
        if x < 0:
            return False
        if x >= self.m:
            return False
        if y < 0:
            return False
        if y >= self.n:
            return False
        if self.forest[x][y] == 0:
            return False
        if (x, y) in visited:
            return False
        return True