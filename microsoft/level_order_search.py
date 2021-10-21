'''
102 Binary Tree Level Order Traversal

Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
'''

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return root
        res = []
        cur_level = [root]
        cur_res = []
        nxt_level = []
        while len(cur_level) > 0:
            cur_n = cur_level[0]
            cur_level.pop(0)
            cur_res.append(cur_n.val)
            if not cur_n.left is None:
                nxt_level.append(cur_n.left)
            if not cur_n.right is None:
                nxt_level.append(cur_n.right)
            if len(cur_level) == 0:
                res.append(cur_res)
                cur_res = []
                cur_level = nxt_level
                nxt_level = []

        return res