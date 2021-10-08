class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left         
        self.right = right

'''
314 Binary Tree Vertical Order Traversal

Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Example 2:


Input: root = [3,9,8,4,0,1,7]
Output: [[4],[9],[3,0,1],[8],[7]]
Example 3:


Input: root = [3,9,8,4,0,1,7,null,null,null,2,5]
Output: [[4],[9,5],[3,0,1],[8,2],[7]]
Example 4:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

基本思想：

BFS
'''

class Solution:
    def verticalOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        self.node_d = {}
        self.minn = 0
        self.maxn = 0
    
        cur_q = [(root, 0)]
        nxt_q = []
        while len(cur_q) > 0:
            cur_n, cur_v = cur_q[0]
            cur_q.pop(0)

            if cur_v not in self.node_d:
                self.node_d[cur_v] = []
                self.minn = min(self.minn, cur_v)
                self.maxn = max(self.maxn, cur_v)
            self.node_d[cur_v].append(cur_n.val)
            
            if not cur_n.left is None:
                nxt_q.append((cur_n.left, cur_v - 1))
            if not cur_n.right is None:
                nxt_q.append((cur_n.right, cur_v + 1))
            
            if len(cur_q) == 0:
                cur_q = nxt_q
                nxt_q = []

        res = []
        for i in range(self.minn, self.maxn + 1):
            res.append(self.node_d[i])
        return res
