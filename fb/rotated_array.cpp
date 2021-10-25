#include<algorithm>
#include<vector>
using namespace std;

/*
33 Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-10^4 <= target <= 10^4

基本思想

判断是否旋转（尾部小于头部）
如果旋转
    二分法找到旋转的地方，根据小于头部的数字就是后半段，大于的就是前半段，找到小于且前一个大于的位置，就是分割线
    二分法分别找两段
不旋转
    二分法找全局

**/

class Solution {
    int k;
    int max_r;
public:
    int search(vector<int>& nums, int target) {
        int ns = nums.size();
        if(nums[ns - 1] < nums[0]){
            max_r = nums[0];
            find_k(0, ns - 1, nums);
            vector<int>::iterator kit = nums.begin() + k;

            vector<int>::iterator it;
            if(target < nums[0]){
                it = lower_bound(kit, nums.end(), target);
                if(it != nums.end() && *it == target){
                    return it - nums.begin();
                }
            }  
            else{
                it = lower_bound(nums.begin(), kit, target);
                if(it != kit && *it == target){
                    return it - nums.begin();
                }
            }
        }
        else{
            vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), target);
            if(it != nums.end() && *it == target){
                return it - nums.begin();
            }
        }

        return -1;
    }

    void find_k(int left, int right, vector<int>& nums){
        if(left > right){return;}

        int mid = (left + right) / 2;
        if(nums[mid] >= max_r){
            find_k(mid + 1, right, nums);
        }
        else{
            if(nums[mid - 1] >= max_r){
                k = mid;
            }
            else{
                find_k(left, mid - 1, nums);
            }
        }
    }
};