#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
/*
98
Validate Binary Search Tree

Solution
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-2^31 <= Node.val <= 2^31 - 1

基本思想

每个root返回当前树的最大值和最小值，每个root和自己子树的左最大值，右最小值比较
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
    bool res = true;
public:
    bool isValidBST(TreeNode* root) {
        max_min(root);
        return res;
    }

    pair<int, int> max_min(TreeNode* root){
        if(root->left != nullptr){
            pair<int, int> left_max_min = max_min(root->left);
            if(root->right != nullptr){
                pair<int, int> right_max_min = max_min(root->right);

                if(left_max_min.first >= root->val || right_max_min.second <= root->val){
                    res = false;
                }

                pair<int, int> cur_res(right_max_min.first, left_max_min.second);
                // cout << root->val << " " << cur_res.first << " " << cur_res.second << endl;
                return cur_res;
            }
            else{
                if(left_max_min.first >= root->val){
                    res = false;
                }
                return pair<int, int>(root->val, left_max_min.second);
            }
        }
        else if(root->right != nullptr){
            pair<int, int> right_max_min = max_min(root->right);

            if(right_max_min.second <= root->val){
                res = false;
            }

            return pair<int, int>(right_max_min.first, root->val);
        }
        else{
            return pair<int, int>(root->val, root->val);
        }
    }
};