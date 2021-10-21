'''
103 Binary Tree Zigzag Level Order Traversal
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
'''
class Solution:
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return root
        res = []
        cur_level = [root]
        cur_res = []
        nxt_level = []
        zigzag = 1
        while len(cur_level) > 0:
            cur_n = cur_level[0]
            cur_level.pop(0)
            cur_res.append(cur_n.val)
            if zigzag == 1:
                if not cur_n.left is None:
                    nxt_level.append(cur_n.left)
                if not cur_n.right is None:
                    nxt_level.append(cur_n.right)
            else:
                if not cur_n.right is None:
                    nxt_level.append(cur_n.right)
                if not cur_n.left is None:
                    nxt_level.append(cur_n.left)
            
            if len(cur_level) == 0:
                res.append(cur_res)
                cur_res = []
                cur_level = nxt_level
                nxt_level = []
                cur_level.reverse()
                zigzag = zigzag ^ 1
        return res