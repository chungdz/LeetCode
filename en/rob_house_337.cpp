#include<map>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


/***
 * 337
 * 
 * 
 * The thief has found himself a new place for his thievery again. 
 * There is only one entrance to this area, called root.
 * Besides the root, each house has one and only one parent house. 
 * After a tour, the smart thief realized that all houses in this place form a binary tree. 
 * It will automatically contact the police if two directly-linked houses were broken into on the same night.
 * Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.
 * 
 * The number of nodes in the tree is in the range [1, 10^4].
 * 0 <= Node.val <= 10^4
 * 
 * 基本思想：暴力搜索
 * 优化：使用map记录节点的最大抢劫值
 * 
 * 
 * **/

class Solution {
    map<TreeNode *, int> opt_price;
public:
    int rob(TreeNode* root){
        if(root == nullptr){return 0;}

        if (opt_price.find(root) == opt_price.end()){
            //if choose
            int max_price = root->val + rob_children(root->left) + rob_children(root->right);
            //if not choose
            int max_price_2 = rob(root->left) + rob(root->right);
            opt_price[root] = max(max_price, max_price_2);
        }

        return opt_price[root];
    }

    int rob_children(TreeNode* root){
        if(root == nullptr){return 0;}
        return rob(root->left) + rob(root->right);
    }
};