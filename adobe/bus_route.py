import collections
'''
815 Bus Routes

You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

 

Example 1:

Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
Example 2:

Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1
 

Constraints:

1 <= routes.length <= 500.
1 <= routes[i].length <= 10^5
All the values of routes[i] are unique.
sum(routes[i].length) <= 10^5
0 <= routes[i][j] < 10^6
0 <= source, target < 10^6

基本思想

图的宽搜，但是区别是需要先根据bus stop来构建bus之间的图，再进行搜索
'''

'''
DFS 可行，但是会TLE
'''
class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        self.bdict = collections.defaultdict(list)
        for i, broutes in enumerate(routes):
            for stop_idx in broutes:
                self.bdict[stop_idx].append(i)
        self.visited = [False] * len(routes)
        self.minb = -1
        self.r = routes
        self.dfs(source, target, 0)
        return self.minb

    def dfs(self, source, target, bn):
        if source == target:
            if self.minb == -1:
                self.minb = bn
            else:
                self.minb = min(bn, self.minb)
            return
        
        valid_bus = []
        for bidx in self.bdict[source]:
            if not self.visited[bidx]:
                valid_bus.append(bidx)
        
        for bidx in valid_bus:
            rl = self.r[bidx]
            self.visited[bidx] = True
            for next_stop in rl:
                if next_stop == source:
                    continue
                self.dfs(next_stop, target, bn + 1)
            self.visited[bidx] = False

'''
DFS,用DP记录到source的最短换乘,TLE
'''
class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        self.bdict = collections.defaultdict(list)
        for i, broutes in enumerate(routes):
            for stop_idx in broutes:
                self.bdict[stop_idx].append(i)
        if target not in self.bdict:
            return -1
        self.minb = {}
        for bidx in self.bdict:
            self.minb[bidx] = 600
        self.r = routes
        self.dfs(source, target, 0)
        if self.minb[target] == 600:
            return -1
        return self.minb[target]

    def dfs(self, source, target, bn):
        if source == target:
            self.minb[target] = min(bn, self.minb[target])
            return
        if bn >= self.minb[source]:
            return
        self.minb[source] = bn

        for bidx in self.bdict[source]:
            rl = self.r[bidx]
            for next_stop in rl:
                if next_stop == source:
                    continue
                self.dfs(next_stop, target, bn + 1)

'''
转换成图，然后宽搜
'''
class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        self.bdict = collections.defaultdict(list)
        for i, broutes in enumerate(routes):
            for stop_idx in broutes:
                self.bdict[stop_idx].append(i)
        if target not in self.bdict:
            return -1
        if source == target:
            return 0
        self.graph = collections.defaultdict(set)
        for stop_idx, stop_buses in self.bdict.items():
            slen = len(stop_buses)
            if slen < 2:
                continue
            for i in range(slen - 1):
                for j in range(i + 1, slen):
                    self.graph[stop_buses[i]].add(stop_buses[j])
                    self.graph[stop_buses[j]].add(stop_buses[i])
        # add start node into the graph
        self.graph[-1] = set(self.bdict[source])
        visited = [False] * len(routes)
        gtarget = set(self.bdict[target])
        q = [(-1, 0)]
        while len(q) > 0:
            cidx, cstep = q[0]
            q.pop(0)
            if cidx in gtarget:
                return cstep
            if cidx not in self.graph:
                continue
            for nxtbus in self.graph[cidx]:
                if visited[nxtbus]:
                    continue
                q.append((nxtbus, cstep + 1))
                visited[nxtbus] = True
        
        return -1


