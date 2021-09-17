#include<vector>
#include<algorithm>
#include<limits.h>
using namespace std;

/*
53

Maximum Subarray

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Example 2:

Input: nums = [1]
Output: 1
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
 

Constraints:

1 <= nums.length <= 3 * 10^4
-10^5 <= nums[i] <= 10^5
 

Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.



基本思想

动态规划经典题

int dp[i]表示以i结尾的最大子串和
if(dp[i] > 0)
    dp[i + 1] = dp[i] + nums[i + 1]
else
    dp[i + 1] = nums[i + 1]

存储可以优化，因为每个dp只用一次

**/

class Solution {
    int dp[31000];
public:
    int maxSubArray(vector<int>& nums) {
        int ss = nums.size();
        int max_re = nums[0];
        dp[0] = nums[0];
        for(int i = 1;i < ss;++i){
            if(dp[i - 1] > 0){
                dp[i] = nums[i] + dp[i - 1];
            }
            else{
                dp[i] = nums[i];
            }
            max_re = max(max_re, dp[i]);
        }
        return max_re;
    }
};