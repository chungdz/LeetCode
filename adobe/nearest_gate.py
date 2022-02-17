'''
286 Walls and Gates

You are given an m x n grid rooms initialized with these three possible values.

-1 A wall or an obstacle.
0 A gate.
INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

 

Example 1:


Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
Example 2:

Input: rooms = [[-1]]
Output: [[-1]]
 

Constraints:

m == rooms.length
n == rooms[i].length
1 <= m, n <= 250
rooms[i][j] is -1, 0, or 2^31 - 1.

基本思想

多点BFS，如果遇到其他点BFS过的路径就不再重复遍历
'''

class Solution:
    def wallsAndGates(self, rooms: List[List[int]]) -> None:
        """
        Do not return anything, modify rooms in-place instead.
        """
        m = len(rooms)
        n = len(rooms[0])
        self.m, self.n = m, n
        self.nlist = [[1, 0], [0, 1], [-1, 0], [0, -1]]
        self.rooms = rooms
        gate_dict = {}
        for i in range(m):
            for j in range(n):
                if rooms[i][j] == 0:
                    gate_dict[(i, j)] = self.find_neighbor_room(i, j, 1)
        
        while len(gate_dict) > 0:
            to_del = []
            for point, nlist in gate_dict.items():
                if len(nlist) == 0:
                    to_del.append(point)
                    continue

                nxt_n = []
                for r, c, level in nlist:
                    if level >= rooms[r][c]:
                        continue
                    rooms[r][c] = level
                    nxt_n += self.find_neighbor_room(r, c, level + 1)
                gate_dict[point] = nxt_n
            
            for k in to_del:
                gate_dict.pop(k)
        
    
    def isValid(self, r, c):
        if r >= 0 and r < self.m and c >= 0 and c < self.n:
            return True
        return False
    
    def isRoom(self, r, c):
        if self.rooms[r][c] == 0 or self.rooms[r][c] == -1:
            return False
        return True
    
    def find_neighbor_room(self, r, c, level):
        rlist = []
        for addx, addy in self.nlist:
            nr = r + addx
            nc = c + addy
            if self.isValid(nr, nc) and self.isRoom(nr, nc):
                rlist.append([nr, nc, level])
        return rlist
