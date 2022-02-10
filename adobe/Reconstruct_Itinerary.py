import copy
import collections


'''
332 Reconstruct Itinerary

You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.

 

Example 1:


Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
Example 2:


Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.
 

Constraints:

1 <= tickets.length <= 300
tickets[i].length == 2
fromi.length == 3
toi.length == 3
fromi and toi consist of uppercase English letters.
fromi != toi

方法一 回溯
DFS + 回溯，保证找到欧拉通路（经过所有边且仅一次）
贪心：DFS从字典序最小的点开始搜索

'''

class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        
        tdict = collections.defaultdict(list)
        visited = collections.defaultdict(list)
        for f, t in tickets:
            tdict[f].append(t)
            visited[f].append(False)
            
        for f, ts in tdict.items():
            tdict[f] = sorted(ts)
        
        self.tdict = tdict
        self.visited = visited
        self.res = []
        self.tmp = ["JFK"]
        self.edges = len(tickets)
        self.search_one("JFK", self.edges)

        return self.res
    
    def search_one(self, p, left):
        if len(self.res) > 0:
            return

        if left == 0:
            self.res = self.tmp.copy()
            return
        
        if len(self.tdict[p]) < 1:
            return
        
        for idx, d in enumerate(self.tdict[p]):
            if self.visited[p][idx]:
                continue
            self.tmp.append(d)
            self.visited[p][idx] = True
            self.search_one(d, left - 1)
            self.tmp.pop()
            self.visited[p][idx] = False
        
        return

'''
方法二

因为本题保证至少存在一种合理的路径，也就告诉了我们，这张图是一个欧拉图或者半欧拉图。我们只需要输出这条欧拉通路的路径即可。

如果没有保证至少存在一种合理的路径，我们需要判别这张图是否是欧拉图或者半欧拉图，具体地：

对于无向图 G，G 是欧拉图当且仅当 G 是连通的且没有奇度顶点。

对于无向图 G，G 是半欧拉图当且仅当 G 是连通的且 G 中恰有 2 个奇度顶点。

对于有向图 G，G 是欧拉图当且仅当 G 的所有顶点属于同一个强连通分量且每个顶点的入度和出度相同。

对于有向图 G，G 是半欧拉图当且仅当 G 的所有顶点属于同一个强连通分量且

恰有一个顶点的出度与入度差为 1；

恰有一个顶点的入度与出度差为 1；

所有其他顶点的入度和出度相同。

Hierholzer 算法用于在连通图中寻找欧拉路径，其流程如下：

从起点出发，进行深度优先搜索。

每次沿着某条边从某个顶点移动到另外一个顶点的时候，都需要删除这条边。

如果没有可移动的路径，则将所在节点加入到栈中，并返回。

当我们顺序地考虑该问题时，我们也许很难解决该问题，因为我们无法判断当前节点的哪一个分支是「死胡同」分支。

不妨倒过来思考。我们注意到只有那个入度与出度差为 11 的节点会导致死胡同。而该节点必然是最后一个遍历到的节点。我们可以改变入栈的规则，当我们遍历完一个节点所连的所有节点后，我们才将该节点入栈（即逆序入栈）。

对于当前节点而言，从它的每一个非「死胡同」分支出发进行深度优先搜索，都将会搜回到当前节点。而从它的「死胡同」分支出发进行深度优先搜索将不会搜回到当前节点。也就是说当前节点的死胡同分支将会优先于其他非「死胡同」分支入栈。

这样就能保证我们可以「一笔画」地走完所有边，最终的栈中逆序地保存了「一笔画」的结果。我们只要将栈中的内容反转，即可得到答案。

既然要求字典序最小，那么我们每次应该贪心地选择当前节点所连的节点中字典序最小的那一个，并将其入栈。最后栈中就保存了我们遍历的顺序。


'''
class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        def dfs(curr: str):
            while vec[curr]:
                tmp = vec[curr].pop(0)
                dfs(tmp)
            stack.append(curr)

        vec = collections.defaultdict(list)
        for depart, arrive in tickets:
            vec[depart].append(arrive)
        for f, ts in vec.items():
            vec[f] = sorted(ts)
        
        stack = list()
        dfs("JFK")
        return stack[::-1]
