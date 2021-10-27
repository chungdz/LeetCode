def knows(a: int, b: int) -> bool:
    return True

'''
277 Find the Celebrity

Suppose you are at a party with n people (labeled from 0 to n - 1), and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know him/her, but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n). There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.

 

Example 1:


Input: graph = [[1,1,0],[0,1,0],[1,1,1]]
Output: 1
Explanation: There are three persons labeled with 0, 1 and 2. graph[i][j] = 1 means person i knows person j, otherwise graph[i][j] = 0 means person i does not know person j. The celebrity is the person labeled as 1 because both 0 and 2 know him but 1 does not know anybody.
Example 2:


Input: graph = [[1,0,1],[1,1,0],[0,1,1]]
Output: -1
Explanation: There is no celebrity.
 

Constraints:

n == graph.length
n == graph[i].length
2 <= n <= 100
graph[i][j] is 0 or 1.
graph[i][i] == 1
 

Follow up: If the maximum number of allowed calls to the API knows is 3 * n, could you find a solution without exceeding the maximum number of calls?

基本思想：

visited = 0：不知道是不是celebrity
visited = 1：一定不是celebrity

第一轮遍历尽量保证对visited = 0之间的节点进行询问，能得到最多的信息
遍历方式：
    i in range(0, n)
    如果visited[i] == 0，让i去和所有visited[0]的非i进行询问
    一旦出现knows(i, k)是True，那么visited[i] = 1，并且之前knows(i, k)为False的visited[k]全部为1
    如果全为False，保存i和i的False数组在first_round里面

    在之后如果发现visited[l]=1 而且l在first_round里面，同样全部讲数组设置为1

第二轮 暴力搜索
    对所有还未知的点进行暴力搜索，先看它是不是未知所有人，出现一次已知就更新所有visited信息
    再看它是不是所有人都知道，出现一次未知就更新所有visited信息
    返回两项都满足的
'''

class Solution:
    def findCelebrity(self, n: int) -> int:
        self.visited = [0] * n
        self.first_round = {}
        beknown = {}
        for i in range(n):
            if self.visited[i] == 0:
                unknown = []
                for j in range(0, n):
                    if self.visited[j] == 1 or j == i:
                        continue
                    if knows(i, j):
                        self.visited[i] = 1
                        if j not in beknown:
                            beknown[j] = set()
                        beknown[j].add(i)
                        break
                    else:
                        unknown.append(j)
                
                if self.visited[i] == 1:
                    for unknown_people in unknown:
                        self.visited[unknown_people] = 1
                        if unknown_people in self.first_round:
                            self.resign(unknown_people)
                    continue
                else:
                    self.first_round[i] = unknown
        
        for curp, unklist in self.first_round.items():
            if self.visited[curp] == 1:
                continue
            
            unkset = set(unklist)
            for i in range(n):
                if i not in unkset and i != curp:
                    if knows(curp, i):
                        self.visited[curp] = 1

                        if i not in beknown:
                            beknown[i] = set()
                        beknown[i].add(curp)

                        self.resign(curp)
                    else:
                        unkset.add(i)
            
            if self.visited[curp] == 1:
                continue
            if curp not in beknown:
                beknown[curp] = set()
            for i in range(n):
                if i not in beknown[curp] and i != curp:
                    if knows(i, curp):
                        beknown[curp].add(i)
                    else:
                        self.visited[curp] = 1
                        self.resign(curp)

            if self.visited[curp] == 0:
                return curp
            
        return -1
    
    def resign(self, cur_index):
        cur_list = self.first_round[cur_index]

        while len(cur_list) > 0:
            nxtp = cur_list[0]
            cur_list.pop(0)
            if self.visited[nxtp] == 0:
                self.visited[nxtp] = 1
                if nxtp in self.first_round:
                    self.resign(nxtp)
        
        # self.first_round.pop(cur_index)


                    