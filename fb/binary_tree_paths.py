import copy

'''
257
Binary Tree Paths

Solution
Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.

 

Example 1:


Input: root = [1,2,3,null,5]
Output: ["1->2->5","1->3"]
Example 2:

Input: root = [1]
Output: ["1"]
 

Constraints:

The number of nodes in the tree is in the range [1, 100].
-100 <= Node.val <= 100

基本思想

先序遍历变种，需要记录所有的路径
'''

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left         
        self.right = right

class Solution:
    def binaryTreePaths(self, root: TreeNode):
        self.res = []
        self.cur_path = []
        self.pre_order_path(root)
        
        str_res = []
        for ilist in self.res:
            str_res.append('->'.join(list(map(str, ilist))))
        
        return str_res

    def pre_order_path(self, root: TreeNode):

        self.cur_path.append(root.val)

        if not root.left is None:
            self.pre_order_path(root.left)
        if not root.right is None:
            self.pre_order_path(root.right)

        if root.left is None and root.right is None:
            self.res.append(copy.copy(self.cur_path))
        
        self.cur_path.pop(-1)
        