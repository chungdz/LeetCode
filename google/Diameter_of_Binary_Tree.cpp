#include<algorithm>
using namespace std;

/*
543

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

 

Example 1:


Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
Example 2:

Input: root = [1,2]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100

基本思路

树的遍历

**/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int lpath = 0;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        search_path(root);
        return lpath;
    }

    int search_path(TreeNode* root){
        int return_max = 0;
        
        int left = 0, right = 0, mid = 0;
        if(root->left != nullptr){
            left = 1 + search_path(root->left);
        }
        if(root->right != nullptr){
            right = 1 + search_path(root->right);
        }
        return_max = max(left, right);
        mid = left + right;
        lpath = max(lpath, mid);
        return return_max; 
    }
};