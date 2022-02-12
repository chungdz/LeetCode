class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

'''
655 Print Binary Tree

Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:

The height of the tree is height and the number of rows m should be equal to height + 1.
The number of columns n should be equal to 2height+1 - 1.
Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
For each node that has been placed in the matrix at position res[r][c], place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
Continue this process until all the nodes in the tree have been placed.
Any empty cells should contain the empty string "".
Return the constructed matrix res.

 

Example 1:


Input: root = [1,2]
Output: 
[["","1",""],
 ["2","",""]]
Example 2:


Input: root = [1,2,3,null,4]
Output: 
[["","","","1","","",""],
 ["","2","","","","3",""],
 ["","","4","","","",""]]
 

Constraints:

The number of nodes in the tree is in the range [1, 2^10].
-99 <= Node.val <= 99
The depth of the tree will be in the range [1, 10].

基本思想：
二叉树的层次遍历，需要额外记录所在层次，父节点指针，用于计算在矩阵中的行列
'''

class Solution:
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        q = [root]
        root.row = 0
        cidx = 0
        while len(q) > cidx:
            curn = q[cidx]
            clevel = q[cidx].row
            cidx += 1
            if not curn.left is None:
                curn.left.parent = curn
                curn.left.row = clevel + 1
                curn.left.p = 'l'
                q.append(curn.left)
            if not curn.right is None:
                curn.right.parent = curn
                curn.right.row = clevel + 1
                curn.right.p = 'r'
                q.append(curn.right)

        height = q[-1].row
        m = height + 1
        n = 2 ** (height + 1) - 1
        res = [[''] * n for _ in range(m)]

        q[0].col = (n - 1) // 2
        res[q[0].row][q[0].col] = str(q[0].val)
        q.pop(0)
        for node in q:
            if node.p == 'l':
                node.col = node.parent.col - 2 ** (height - node.parent.row - 1)
            else:
                node.col = node.parent.col + 2 ** (height - node.parent.row - 1)
            
            res[node.row][node.col] = str(node.val)
        
        return res

