'''
117 Populating Next Right Pointers in Each Node II

Solution
Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

Example 1:


Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
Example 2:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 6000].
-100 <= Node.val <= 100
 

Follow-up:

You may only use constant extra space.
The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.

基本思想

116题目基础上需要分四种情况讨论每个节点子分支情况，根据情况赋值
'''

class Solution:
    def connect(self, root: 'Node') -> 'Node':
        if root is None:
            return None
        
        next_level_head = root
        while not next_level_head is None:
            curp = next_level_head
            next_level_head = None
            pre_node = None
            while not curp is None:
                if next_level_head is None:
                    if not curp.left is None and curp.right is None:
                        next_level_head = curp.left
                        pre_node = next_level_head
                    elif curp.left is None and not curp.right is None:
                        next_level_head = curp.right
                        pre_node = next_level_head
                    elif not curp.left is None and not curp.right is None:
                        next_level_head = curp.left
                        curp.left.next = curp.right
                        pre_node = curp.right
                else:
                    if not curp.left is None and curp.right is None:
                        pre_node.next = curp.left
                        pre_node = curp.left
                    elif curp.left is None and not curp.right is None:
                        pre_node.next = curp.right
                        pre_node = curp.right
                    elif not curp.left is None and not curp.right is None:
                        pre_node.next = curp.left
                        curp.left.next = curp.right
                        pre_node = curp.right
                
                curp = curp.next

        
        return root