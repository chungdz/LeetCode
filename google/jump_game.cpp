#include<vector>
#include<map>
#include <algorithm>
using namespace std;

/***
 * 55
 * 
 * 
 * You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 10^4
0 <= nums[i] <= 10^5
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

/***
 * 
 * 
 * 
 * 
 * 方案一
 * 动态规划
 * bool数组记录每个数字的true false
 * 
 * 
 * 
 * 
*/

class Solution {
    bool record[10000] = {0};
public:
    bool canJump(vector<int>& nums) {
        int length = nums.size();
        record[length - 1] = true;
        for(int i = length - 2;i >= 0;--i){
            int cur_number = nums[i];
            for(int j = cur_number;j >= 1;--j){
                if(i + j < length && record[i + j]){
                    record[i] = true;
                    break;
                }
            }
        }
        return record[0];
    }
};


/***
 * 
 * 
 * 
 * 方案二
 * 
 * 优化时间和空间
 * 
 * 只记录最近的有效跳跃点，如果当前number能跳过去，就更新跳跃点
 * 
 * 
 * 
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int length = nums.size();
        int nearest_jump = length - 1;
        
        for(int i = length - 2;i >= 0;--i){
            int distance = nearest_jump - i;
            if(nums[i] >= distance){
                nearest_jump = i;
            }
        }
        return nums[0] >= (nearest_jump - 0);
    }
};