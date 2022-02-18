'''
COEN 379 并查集python实现
'''

class Node:
    def __init__(self, v) -> None:
        self.v = v
        self.rank = 0
        self.parent = self

class DisjointSet:
    def __init__(self) -> None:
        self.nodes = {}

    def make_set(self, v):
        assert(v not in self.nodes)
        self.nodes[v] = Node(v)
    
    def find_set(self, v):
        assert(v in self.nodes)
        cn = self.nodes[v]
        if cn.parent == cn:
            return cn
        
        cn.parent = self.find_set(cn.parent.v)
        return cn.parent
    
    def union(self, x, y):
        nx = self.find_set(x)
        ny = self.find_set(y)

        if nx == ny:
            return False
        if nx.rank > ny.rank:
            ny.parent = nx
        elif ny.rank > nx.rank:
            nx.parent = ny
        else:
            ny.parent = nx
            nx.rank += 1
        return True
    
    def prints(self):
        for v, nv in self.nodes.items():
            print(v, nv.parent.v)