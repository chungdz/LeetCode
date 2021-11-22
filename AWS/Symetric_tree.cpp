struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
101 Symmetric Tree

Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

 

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
 

Follow up: Could you solve it both recursively and iteratively?

基本思想

左边优先遍历（左子树），右边优先遍历（右子树），遍历出的值相等
*/

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isSymmetric2(root->left, root->right);
    }

    bool isSymmetric2(TreeNode* root1, TreeNode* root2){
        if(root1 == nullptr){
            if(root2 == nullptr){
                return true;
            }
            else{
                return false;
            }
        }
        if(root2 == nullptr){
            return false;
        }

        bool res = true;
        res &= root1->val == root2->val;
        if(!res)
            return false;
        res &= isSymmetric2(root1->left, root2->right);
        if(!res)
            return false;
        res &= isSymmetric2(root1->right, root2->left);
        if(!res)
            return false;
        return res;
    }
};