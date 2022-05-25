#include<vector>
#include<algorithm>
using namespace std;

/**
324 wiggle sort II

Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

You may assume the input array always has a valid answer.

 

Example 1:

Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: [1,4,1,5,1,6] is also accepted.
Example 2:

Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]
 

Constraints:

1 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 5000
It is guaranteed that there will be an answer for the given input nums.

寻找中位数（快速排序），然后分割数组成两部分，然后将两部分都逆序，然后把右半部分插入左半部分

或者是直接快排，然后倒序做，快排效率很高
 
 */

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int len = nums.size();
        quickSelect(nums, 0, len, len / 2);
        auto midptr = nums.begin() + len / 2;
        int mid = *midptr;
        
        // 3-way-partition
        int i = 0, j = 0, k = nums.size() - 1;
        while(j < k){
            if(nums[j] > mid){
                swap(nums[j], nums[k]);
                --k;
            }
            else if(nums[j] < mid){
                swap(nums[j], nums[i]);
                ++i;
                ++j;
            }
            else{
                ++j;
            }
        }
        
        if(nums.size() % 2) ++midptr;
        vector<int> tmp1(nums.begin(), midptr);
        vector<int> tmp2(midptr, nums.end());
        for(int i = 0; i < tmp1.size(); ++i){
            nums[2 * i] = tmp1[tmp1.size() - 1 - i];
        }
        for(int i = 0; i < tmp2.size(); ++i){
            nums[2 * i + 1] = tmp2[tmp2.size() - 1 - i];
        }
    }
    
private:
    void quickSelect(vector<int> &nums, int begin, int end, int n){
        int t = nums[end - 1];
        int i = begin, j = begin;
        while(j < end){
            if(nums[j] <= t){
                swap(nums[i++], nums[j++]);
            }
            else{
                ++j;
            }
        }
        if(i - 1 > n){
            quickSelect(nums, begin, i - 1, n);
        }
        else if(i <= n){
            quickSelect(nums, i, end, n);
        }
    }
};
