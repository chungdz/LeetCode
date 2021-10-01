'''
317 Shortest Distance from All Buildings

You are given an m x n grid grid of values 0, 1, or 2, where:

each 0 marks an empty land that you can pass by freely,
each 1 marks a building that you cannot pass through, and
each 2 marks an obstacle that you cannot pass through.
You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return -1.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:


Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
So return 7.
Example 2:

Input: grid = [[1,0]]
Output: 1
Example 3:

Input: grid = [[1]]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0, 1, or 2.
There will be at least one building in the grid.

基本思想
宽搜 以building为起点，找到所有可达的cell，比较距离

剪枝：
只探索之前的building都可以到达的cell

C++的速度比python快很多


'''          
class Solution:

    def __init__(self) -> None:
        self.buildings = []
        self.cells = {}
        self.movement = [(-1, 0), (0, -1), (1, 0), (0, 1)]

    def shortestDistance(self, grid: List[List[int]]) -> int:
        self.m = len(grid)
        self.n = len(grid[0])
        self.grid = grid

        for i in range(self.m):
            for j in range(self.n):
                if grid[i][j] == 1:
                    self.buildings.append((i, j))
                elif grid[i][j] == 0:
                    self.cells[(i, j)] = 0
        
        if len(self.cells) < 1:
            return -1
        
        building_num = 0
        for bx, by in self.buildings:
            cur_step = 1
            cur_queue = []
            
            for m in self.movement:
                nx = bx + m[0]
                ny = by + m[1]
                if nx >= 0 and nx < self.m and ny >= 0 and ny < self.n:
                    cur_queue.append((nx, ny))
         
            nxt_queue = []
            while len(cur_queue) > 0:
                curx, cury = cur_queue[0]
                cur_queue.pop(0)

                if grid[curx][cury] == building_num:
                    
                    grid[curx][cury] -= 1
                    self.cells[(curx, cury)] += cur_step

                    for m in self.movement:
                        nx = curx + m[0]
                        ny = cury + m[1]
                        if nx >= 0 and nx < self.m and ny >= 0 and ny < self.n:
                            nxt_queue.append((nx, ny))
                
                if len(cur_queue) < 1:
                    cur_queue = nxt_queue
                    nxt_queue = []
                    cur_step += 1
            
            building_num -= 1
        
        min_dis = float("inf")
        for k, v in self.cells.items():
            if grid[k[0]][k[1]] == building_num:
                min_dis = min(min_dis, v)
        
        if min_dis == float("inf"):
            return -1
        else:
            return min_dis
            
    

