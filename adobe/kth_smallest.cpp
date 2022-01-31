struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
230 Kth Smallest Element in a BST

Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

 

Example 1:


Input: root = [3,1,4,null,2], k = 1
Output: 1
Example 2:


Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 104
0 <= Node.val <= 104
 

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?

基本思想

二叉树中序遍历，需要注意传入rank

*/

class Solution {
    int res;
    int target;
public:
    int kthSmallest(TreeNode* root, int k) {
        res = -1;
        target = k;
        midOrder(root, 0);
        return res;
    }

    int midOrder(TreeNode *root, int pnum){
        if(root == nullptr)
            return pnum;
        
        int rank = midOrder(root->left, pnum) + 1;
        if(rank == target){
            res = root->val;
            return rank;
        }
        int num = midOrder(root->right, rank);

        return num;
    }
};