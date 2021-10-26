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

class Solution {
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