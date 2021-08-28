#include<map>
#include<algorithm>
using namespace std;

/*

124

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any path.

 

Example 1:


Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
Example 2:


Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 10^4].
-1000 <= Node.val <= 1000


基本思想

深度搜索树，因为每个节点只会遍历一遍，所以不用记录每个节点的路径值

对每个节点，以他为树中最高节点的路径值有：

value + left_value
value + right_value
value
value + left_value + right_value

其中前三个可以和更高的节点结合，所以返回前三个的max值作为这一个节点子路径的最大值

最后一个只能在当前节点判断，所以max所有四个值作为以当前节点为树中最高节点的最大路径值

返回最大的路径值

**/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#define MIN_INF -2000

class Solution {
    int max_sum;
public:
    int maxPathSum(TreeNode* root) {
        max_sum = MIN_INF;
        search_max(root);
        return max_sum;
    }

    int search_max(TreeNode *r){
        if(r == nullptr){return MIN_INF;}
        int left_c = search_max(r->left);
        int right_c = search_max(r->right);

        int midp = left_c + right_c + r->val;
        int leftp = left_c + r->val;
        int rightp = right_c + r->val;

        int return_value = max(max(leftp, rightp), r->val);
        int cur_max_path = max(midp, return_value);
        max_sum = max(cur_max_path, max_sum);

        return return_value;
    }
};