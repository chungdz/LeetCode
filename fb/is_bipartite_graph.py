'''
785 Is Graph Bipartite?
There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:

There are no self-edges (graph[u] does not contain u).
There are no parallel edges (graph[u] does not contain duplicate values).
If v is in graph[u], then u is in graph[v] (the graph is undirected).
The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.

Return true if and only if it is bipartite.

基本思想

染色法 + DFS
给边两端的点染不同颜色，有冲突返回False，注意有可能不是连通图所有要遍历所有点保证全访问
'''

class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        nn = len(graph)
        self.ncolor = [-1] * nn
        self.conflict = False
        self.graph = graph
        for i in range(nn):
            if self.ncolor[i] == -1:
                self.dfs(i, 0)
        return not self.conflict
        
    def dfs(self, nindex, color):

        if self.ncolor[nindex] != -1:
            if self.ncolor[nindex] != color:
                self.conflict = True
            return
        self.ncolor[nindex] = color
        nxt_color = (color + 1) % 2
        for neighbor in self.graph[nindex]:
            self.dfs(neighbor, nxt_color)
