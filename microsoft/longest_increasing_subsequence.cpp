#include<algorithm>
#include<vector>
#include<map>
using namespace std;

/*
300 Longest Increasing Subsequence

Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].

 

Example 1:

Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
Example 2:

Input: nums = [0,1,0,3,2,3]
Output: 4
Example 3:

Input: nums = [7,7,7,7,7,7,7]
Output: 1
 

Constraints:

1 <= nums.length <= 2500
-10^4 <= nums[i] <= 10^4
 

Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?

基本思想

从尾往头遍历，nums[i] = 1 + max(nums[j]) (j > i && nums[j] > nums[i])

本题length小，nums[i]大，所以用map来保存每个数的结尾值，如果反过来length大nums[i]小，可以用线段树（BIT树）来求最大值
这时候从头往尾遍历，nums[i] = 1 + segment_tree.search_max(0, nums[i] - 1) 

*/

class Solution1 {
    map<int, int> sequence; 
public:
    int lengthOfLIS(vector<int>& nums) {
        int ns = nums.size();
        int max_sub = 1;
        for(int i = ns - 1;i >= 0;--i){
            map<int, int>::iterator it = sequence.upper_bound(nums[i]);
            int cur_len = 1;
            if(it != sequence.end()){
                while(it != sequence.end()){
                    cur_len = max(cur_len, 1 + it->second);
                    it++;
                }
            }
            sequence[nums[i]] = cur_len;
            max_sub = max(max_sub, cur_len);
        }
        return max_sub;
    }
};

/*
dp[i]表示长度为i + 1的序列的结尾最小数字
初始化
cur_len = 1
dp[0] = nums[0]
更新
如果nums[i] > dp[cur_len - 1], dp[cur_len] = nums[i], cur_len += 1
否则找到二分找到lower bound的位置k，更新dp[k] = nums[i]

更新的意义：
只更新结尾最靠近nums[i]的子序列dp[k]的长度，使得dp[k + 1]结尾为nums[i]，由于dp[i]必定单调递增，更新k之前的序列没有意义
不会使得k之前的序列更长于k之后的

必定单调递增的证明

如果dp[j] >= dp[i]，且j < i，那么由于序列i比j长，子序列i必定存在子序列长度等于j，并且结尾的数字小于dp[i]，也就是小于dp[j]，与
dp记录长度为k的序列的结尾最小数字冲突
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int ns = nums.size();
        vector<int> dp(ns, 0);
        int cur_len = 1;
        dp[0] = nums[0];
        for(int i = 1;i < ns;++i){
            if(nums[i] > dp[cur_len - 1]){
                dp[cur_len] = nums[i];
                cur_len += 1;
            }
            else{
                vector<int>::iterator it = lower_bound(dp.begin(), dp.begin() + cur_len, nums[i]);
                *it = nums[i];
            }
        }
        return cur_len;
    }
};