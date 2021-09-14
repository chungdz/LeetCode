/*
543

 二叉树的直径
给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

 

示例 :
给定二叉树

          1
         / \
        2   3
       / \     
      4   5    
返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。

 

注意：两结点之间的路径长度是以它们之间边的数目表示。
*/
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
最大路径要么在左子树，要么在右子树，要么是左加右加中，要么在返回上一级的值中

返回上一级的值要么是左加中，要么是右加中，要么是中，选其中最大值
*/
class Solution {
    int max_result = 0;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(root){tree_max(root);}
        return max_result;
    }

    int tree_max(TreeNode* root){
        int left_max, right_max;
        int max_return = 0;

        if(root->left){
            left_max = tree_max(root->left);
            max_result = max(max_result, 1 + left_max);
            max_return = 1 + left_max;
        }
        if(root->right){
            right_max = tree_max(root->right);
            max_result = max(max_result, 1 + right_max);
            max_return = 1 + right_max;
        }
        if(root->left && root->right){
            max_return = max(1 + left_max, 1 + right_max);
            max_result = max(max_result, 2 + right_max + left_max);
        }

        return max_return;
    }
};