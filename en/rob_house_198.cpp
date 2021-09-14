#include<vector>
#include<algorithm>
using namespace std;

/***
 * 198
 * 
 * 
 * You are a professional robber planning to rob houses along a street. 
 * Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is 
 * that adjacent houses have security systems connected 
 * and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, 
 * return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Constraints:
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 400
 * 
 * 最大子序列变种
 * 基本思路就是暴力搜索
 * 优化：动态规划，把每个位置最高能偷的钱记下来，由于不能偷相邻的钱，转移方程是
 * max_income[i] = nums[i] + max(max_income[i - 2], max_income[i - 3])
 * 
 * **/

class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> max_income;
        int length = nums.size();

        if(length == 1){return nums[0];}
        else if(length == 2){return max(nums[0], nums[1]);}

        max_income.push_back(nums[0]);
        max_income.push_back(nums[1]);
        max_income.push_back(nums[0] + nums[2]);

        if(length == 3){return max(max_income[1], max_income[2]);}

        for(int i = 3;i < length;i++){
            // 要么加i - 2的位置，要么加i - 3的位置
            max_income.push_back(nums[i] + max(max_income[i - 2], max_income[i - 3]));
        }

        return max(max_income[length - 1], max_income[length - 2]);
    }
};