#include<algorithm>
#include<unordered_set>
#include<vector>
using namespace std;

/*

47
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

 

Example 1:

Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
Example 2:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

Constraints:

1 <= nums.length <= 8
-10 <= nums[i] <= 10

基本思想

把每个独特的数字放在最前，然后和n - 1的全permutation组合
用set记录访问过的数字
**/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
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
        unordered_set<int> visited;
        for(int i = cur_ta;i >= 0;--i){
            if(visited.find(nums[i]) != visited.end()){
                continue;
            }
            visited.insert(nums[i]);
            swap(nums[cur_ta], nums[i]);
            search_p(cur_ta, nums);
            swap(nums[cur_ta], nums[i]);
        }
    }
};