#include<vector>
#include<algorithm>
using namespace std;

/*

34

Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 105
-10^9 <= nums[i] <= 10^9
nums is a non-decreasing array.
-10^9 <= target <= 10^9

基本思想

二分搜索，使用STL标准库

**/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        vector<int>::iterator itl = lower_bound(nums.begin(), nums.end(), target);
        if(itl == nums.end() || *itl != target){
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        res.push_back(itl - nums.begin());
        vector<int>::iterator itu = upper_bound(itl, nums.end(), target);
        res.push_back(itu - nums.begin() - 1);

        return res;
    }
};