#include<vector>
#include<algorithm>
using namespace std;

/*
238
Product of Array Except Self

Solution
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
 

Constraints:

2 <= nums.length <= 105
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

基本思想

双指针保存左右两边的product，由于遍历关系，只用保存右半边的product就行
*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> right_sum;
        int ns = nums.size();
        int right_pre = 1;
        for(int i = ns - 1;i >= 0;--i){
            right_pre *= nums[i];
            right_sum.push_back(right_pre);
        }
        reverse(right_sum.begin(), right_sum.end());
        int left_pre = 1;
        vector<int> ans;
        for(int i = 0;i < ns;++i){
            int cur_right;
            if(i == ns - 1){cur_right = 1;}
            else{cur_right = right_sum[i + 1];}
            ans.push_back(left_pre * cur_right);
            left_pre *= nums[i];
        }

        return ans;
    }
};