#include<vector>
#include<algorithm>
using namespace std;

/*

222

Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Design an algorithm that runs in less than O(n) time complexity.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: 6
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [1]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [0, 5 * 10^4].
0 <= Node.val <= 5 * 10^4
The tree is guaranteed to be complete.



基本思想

宽度优先搜索，为了方便计算每一层的节点数，用两个vector轮流保存当前层的节点和下一层的节点

利用 二叉完全树的特性

判断是不是倒数第二行（或者是倒数第一行如果是满二叉树），根据是否子指针出现空

同时，当出现空指针的时候，倒数第一行的数目为 当前节点之前的节点数 * 2 + 当前节点的儿子数

此时不再需要遍历倒数第一行的节点就可以知道所有节点数目，因为当前节点数等于数组里所有节点的大小


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
    vector<TreeNode*> level_record[2];
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr){return 0;}

        level_record[0].push_back(root);
        return bf_search(0);
    }

    int bf_search(int cur_index){
        int cur_level;
        int next_index = 1 ^ cur_index;
        int counter = 0;
        int cur_level_num = level_record[cur_index].size();
        for(auto tp: level_record[cur_index]){
            if(tp->left == nullptr){
                cur_level = counter * 2 + cur_level_num;
                return cur_level;
            }
            else if(tp->right == nullptr){
                cur_level = counter * 2 + 1 + cur_level_num;
                return cur_level;
            }

            level_record[next_index].push_back(tp->left);
            level_record[next_index].push_back(tp->right);
            counter += 1;
        }

        cur_level = cur_level_num;
        level_record[cur_index].clear();

        cur_level += bf_search(next_index);
        return cur_level;
    }
};