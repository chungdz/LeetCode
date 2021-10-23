#include<algorithm>
#include<vector>
using namespace std;

/*
105 Construct Binary Tree from Preorder and Inorder Traversal

Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]
 

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.

基本思想：

找根节点
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int tl = preorder.size();
        return generate_nodes(0, tl - 1, 0, tl - 1, preorder, inorder);
    }

    TreeNode* generate_nodes(int pl, int pr, int il, int ir, vector<int>& preorder, vector<int>& inorder){
        if(pl > pr){return nullptr;}
        TreeNode *cur_root = new TreeNode(preorder[pl]);
        int i;
        for(i = il;i <= ir;++i){
            if(inorder[i] == preorder[pl])
                break;
        }
        int left_len = i - il;
        int right_len = ir - i;

        cur_root->left = generate_nodes(pl + 1, pl + left_len, il, i - 1, preorder, inorder);
        cur_root->right = generate_nodes(pl + left_len + 1, pr, i + 1, ir, preorder, inorder);
        return cur_root;
    }
};