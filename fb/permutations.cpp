#include<algorithm>
#include<vector>
using namespace std;

/*
46
Permutations
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.

**/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int ns = nums.size();
        search_p(ns, nums);
        return res;
    }

    void search_p(int clen, vector<int>& nums){
        if(clen == 1){
            res.push_back(nums);
            return;
        }
        int cur_ta = clen - 1;
        for(int i = cur_ta;i >= 0;--i){
            swap(nums[cur_ta], nums[i]);
            search_p(cur_ta, nums);
            swap(nums[cur_ta], nums[i]);
        }
    }
};