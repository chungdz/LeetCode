#include<algorithm>
#include<vector>
using namespace std;

/*
108 Convert Sorted Array to Binary Search Tree

Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every node never differs by more than one.

 

Example 1:


Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:


Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.
 

Constraints:

1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in a strictly increasing order.

基本思想

递归分裂
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int ns = nums.size();
        return iterSplit(0, ns - 1, nums);
    }

    TreeNode* iterSplit(int start, int end, vector<int>& nums){
        if(start > end){
            return nullptr;
        }

        TreeNode* res;

        if(start == end){
            res = new TreeNode(nums[start]);
            return res;
        }
        int mid = (start + end) / 2;
        res = new TreeNode(nums[mid]);
        res->left = iterSplit(start, mid - 1, nums);
        res->right = iterSplit(mid + 1, end, nums);
        return res;
    }
};