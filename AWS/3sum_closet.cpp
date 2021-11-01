#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

/*
16 3Sum Closest

Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
 

Constraints:

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-10^4 <= target <= 10^4

基本思想
S1是暴力搜索
S2 排序 + 双指针

排序保证遍历的不重复性，以及双指针的基础
对每个i，pb = i + 1, pc = ns - 1
如果3 sum （nums[i] + nums[pb] + nums[pc]）大于target， pb + 1，因为数字比target小，得大一些
如果3 sum 小于target，pc - 1，因为数字比target大，得小一些
等于的话直接返回
*/

class Solution1 {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ns = nums.size();
        int closet, min_dis = 100000;
        for(int i = 0;i < ns - 2;++i){
            for(int j = i + 1;j < ns - 1;++j){
                for(int k = j + 1;k < ns;++k){
                    int cur_sum = nums[i] + nums[j] + nums[k];
                    int cur_dis = abs(cur_sum - target);
                    if(cur_dis < min_dis){
                        min_dis = cur_dis;
                        closet = cur_sum;
                    }
                }
            }
        }
        return closet;
    }
};

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ns = nums.size();
        sort(nums.begin(), nums.end());
        int closet, min_dis = 100000;
        for(int i = 0;i < ns - 2;++i){
            int pb = i + 1;
            int pc = ns - 1;
            while(pb < pc){
                int cur_sum = nums[pb] + nums[pc] + nums[i];
                int cur_dis;
                if(cur_sum < target){
                    pb += 1;
                    cur_dis = target - cur_sum;
                }
                else if(cur_sum > target){
                    pc -= 1;
                    cur_dis = cur_sum - target;
                }
                else{
                    return target;
                }
                if(cur_dis < min_dis){
                    min_dis = cur_dis;
                    closet = cur_sum;
                }
            }
        }
        return closet;
    }
};

