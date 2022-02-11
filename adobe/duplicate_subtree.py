import collections

'''
652 Find Duplicate Subtrees

Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:


Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:


Input: root = [2,1,1]
Output: [[1]]
Example 3:


Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
 

Constraints:

The number of the nodes in the tree will be in the range [1, 10^4]
-200 <= Node.val <= 200

基本思想

用字符串记录每个子树的形状，存在dict<str, list>里面
'''

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findDuplicateSubtrees(self, root: Optional[TreeNode]) -> List[Optional[TreeNode]]:
        self.tdict = collections.defaultdict(list)
        self.postSearch(root)
        res = []
        for k, v in self.tdict.items():
            if len(v) > 1:
                res.append(v[0])
        
        return res
    
    def postSearch(self, node: TreeNode):
        if node is None:
            return "n"
        
        if node.left is None and node.right is None:
            cstr = str(node.val)
        else:
            cstr = str(node.val) + "l" + self.postSearch(node.left) + "r" + self.postSearch(node.right)

        self.tdict[cstr].append(node)
        return cstr
