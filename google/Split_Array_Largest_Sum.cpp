#include<vector>
#include<algorithm>
#include<limits.h>
#include<memory.h>
#include <numeric>
using namespace std;

/*
410

Split Array Largest Sum

Solution
Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.

 

Example 1:

Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
Example 2:

Input: nums = [1,2,3,4,5], m = 2
Output: 9
Example 3:

Input: nums = [1,4,4], m = 3
Output: 4
 

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 106
1 <= m <= min(50, nums.length)



基本思想

动态规划

dp[i][j]表示将前k个分成j组时的最大值

dp[i][1] 初始化为以i结尾的数组和

dp[i][j] = min{max(dp[k - 1][j - 1], sum(nums[k], nums[i]))} k >= j - 1 以保证至少存在j - 1个分割，每个分割数量为1

**/

/**

贪心法（过不了所有样例）

每次找数组中两和最小的相加，缩小数组和直到等于m

 * 
 */

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        vector<int> pre = nums;
        int pre_size = pre.size();
        while(pre_size != m){
            int min_sum = INT32_MAX;
            int min_index;
            for(int i = 0;i < pre_size - 1;++i){
                int cur_sum = pre[i] + pre[i + 1];
                if(cur_sum < min_sum){
                    min_index = i;
                    min_sum = cur_sum;
                }
            }
            pre[min_index] += pre[min_index + 1];
            pre.erase(pre.begin() + min_index + 1);
            pre_size -= 1;
        }
        return *max_element(pre.begin(), pre.end());
    }
};

/*

动态规划

dp[i][j]表示将前k个分成j组时的最大值


**/

class Solution {
    int dp[1000][51];
public:
    int splitArray(vector<int>& nums, int m) {
        memset(dp, -1, sizeof(int) * 1000 * 51);
        int ss = nums.size();
        int nsum = 0;
        for(int i = 0;i < ss;++i){
            nsum += nums[i];
            dp[i][1] = nsum;
        }

        return search_dp(ss - 1, m, nums);
    }

    int search_dp(int index, int remain, vector<int>& nums){
        if(dp[index][remain] != -1){
            return dp[index][remain];
        }

        int sum_reverse = 0;
        int min_sum = INT32_MAX;
        for(int i = index;i >= remain - 1;--i){
            sum_reverse += nums[i];
            int nxt_dp = search_dp(i - 1, remain - 1, nums);
            int cur_max = max(nxt_dp, sum_reverse);
            min_sum = min(min_sum, cur_max);
        }
        dp[index][remain] = min_sum;
        return min_sum;
    }
};
