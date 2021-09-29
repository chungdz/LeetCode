'''
199
Binary Tree Right Side View

Solution
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:


Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
Example 2:

Input: root = [1,null,3]
Output: [1,3]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

基本思想

树的层次遍历，将每一层的最后一个（最右边）的数值放入结果
'''

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left         
        self.right = right

class Solution:
    def rightSideView(self, root: 'TreeNode'):
        if root is None:
            return None
        res = []
        cur_queue = []
        nxt_queue = []
        cur_queue.append(root)
        while len(cur_queue) > 0:

            curn = cur_queue[0]
            
            if not curn.left is None:
                nxt_queue.append(curn.left)
            if not curn.right is None:
                nxt_queue.append(curn.right)
            
            if len(cur_queue) == 1:
                res.append(curn.val)
                cur_queue = nxt_queue
                nxt_queue = []
            else:
                cur_queue.pop(0)
        
        return res
