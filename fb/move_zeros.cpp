#include<vector>
#include<algorithm>
using namespace std;

/*
283
Move Zeroes

Solution
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

 

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?

基本思想

双指针，每次都把数字移动到最前面的零那边

**/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int leftest_zero = 0, right_num, ns = nums.size();
        while(leftest_zero < ns && nums[leftest_zero] != 0){
            leftest_zero++;
        }
        right_num = leftest_zero + 1;
        while(right_num < ns){
            if(nums[right_num] != 0){
                swap(nums[leftest_zero], nums[right_num]);
                while(nums[leftest_zero] != 0){
                    leftest_zero++;
                }
                right_num = max(leftest_zero + 1, right_num + 1);
            }
            else{
                ++right_num;
            }
        }
    }
};