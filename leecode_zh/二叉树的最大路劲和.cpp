/*
给定一个非空二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。

示例 1:

输入: [1,2,3]

       1
      / \
     2   3

输出: 6
示例 2:

输入: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

输出: 42
*/
#include <algorithm>
#include <limits.h>
#include <map>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
最大值要么在左子树，要么在右子树，要么是左加右加中，要么在返回上一级的值中

返回上一级的值要么是左加中，要么是右加中，要么是中，选其中最大值
*/
class Solution {
    int max_result = INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        tree_max(root);
        return max_result;
    }

    int tree_max(TreeNode* root){
        int left_max, right_max;
        int max_return = root->val;

        if(root->left){
            left_max = tree_max(root->left);
            max_result = max(max_result, left_max);
            max_return = max(max_return, root->val + left_max);
        }
        if(root->right){
            right_max = tree_max(root->right);
            max_result = max(max_result, right_max);
            max_return = max(max_return, root->val + right_max);
        }
        if(root->left && root->right){
            max_result = max(max_result, root->val + right_max + left_max);
        }

        max_result = max(max_result, max_return);
        return max_return;
    }
};