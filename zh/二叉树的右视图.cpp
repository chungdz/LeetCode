/*
 二叉树的右视图
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例:

输入: [1,2,3,null,5,null,4]
输出: [1, 3, 4]
解释:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
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
宽度遍历树

返回每一层最后一位
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<pair<TreeNode*, int>> q;
        if(root){q.push(make_pair(root, 0));}
        vector<int> result;

        while(!q.empty()){
            TreeNode *cur_node = q.front().first;
            int cur_level = q.front().second;
            q.pop();

            if(cur_node->left){q.push(make_pair(cur_node->left, cur_level + 1));}
            if(cur_node->right){q.push(make_pair(cur_node->right, cur_level + 1));}

            if(!q.empty()){
                int nxt_level = q.front().second;
                if(nxt_level > cur_level){
                    result.push_back(cur_node->val);
                }
            }
            else{
                result.push_back(cur_node->val);
            }
        }

        return result;
    }
};

/*
深度优先，先访问右边的节点

使用栈

只有当前深度大于最大深度，才加入新的值
*/