class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

'''
272 Closest Binary Search Tree Value

Given the root of a binary search tree, a target value, and an integer k, return the k values in the BST that are closest to the target. You may return the answer in any order.

You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

 

Example 1:


Input: root = [4,2,5,1,3], target = 3.714286, k = 2
Output: [4,3]
Example 2:

Input: root = [1], target = 0.000000, k = 1
Output: [1]
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 10^4.
0 <= Node.val <= 10^9
-10^9 <= target <= 10^9
 

Follow up: Assume that the BST is balanced. Could you solve it in less than O(n) runtime (where n = total nodes)?

基本思路

遍历二叉树，重构从小到大的数组，找到target的临界位置，使用双指针找到closest

优化：
在找到第一个比target大的数字的时候，就开始双指针搜索了，每次把更接近的数字加入直到当前寻找到的数字也加入结果序列，再去往前找其他数字
理论上如果最大数字不在结果内，查询时间就是小于O(n)的

'''

class Solution:
    def closestKValues(self, root: Optional[TreeNode], target: float, k: int) -> List[int]:
        self.nlist = []
        self.res = []
        self.k = k
        self.target = target
        self.p = -1
        self.get_val(root)
        
        if len(self.res) < k:
            if self.p == -1:
                self.p = len(self.nlist) - 1
            while len(self.res) < self.k and self.p >= 0:
                self.res.append(self.nlist[self.p])
                self.p -= 1
        
        return self.res
        
        
    def get_val(self, root):
        if root is None:
            return
        if len(self.res) >= self.k:
            return
        
        self.get_val(root.left)
        if root.val <= self.target:
            self.nlist.append(root.val)
            self.p += 1
        else:
            self.nlist.append(root.val)
            dif = root.val - self.target
            while len(self.res) < self.k and self.p >= 0 and self.target - self.nlist[self.p] < dif:
                self.res.append(self.nlist[self.p])
                self.p -= 1
            if len(self.res) < self.k:
                self.res.append(root.val)
        
        self.get_val(root.right)