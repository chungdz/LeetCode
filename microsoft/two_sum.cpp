#include<algorithm>
#include<unordered_map>
#include<vector>
using namespace std;

/*
1 Two Sum

Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
Only one valid answer exists.
 

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

基本思想

利用dict
**/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int>> num_record;
        int ns = nums.size();
        for(int i = 0;i < ns;++i){
            int n = nums[i];
            if(num_record.find(n) == num_record.end())
                num_record[n] = vector<int>(1, i);
            else
                num_record[n].push_back(i);
        }
        vector<int> res;
        for(int i = 0;i < ns;++i){
            int se = target - nums[i];
            if(num_record.find(se) != num_record.end()){
                for(int index: num_record[se]){
                    if(index != i){
                        res = vector<int>({i, index});
                    }
                }
            }
        }
        return res;
    }
};