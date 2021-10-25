#include<algorithm>
#include<vector>
using namespace std;

/*
154 Find Minimum in Rotated Sorted Array II

Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

[4,5,6,7,0,1,4] if it was rotated 4 times.
[0,1,4,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

You must decrease the overall operation steps as much as possible.

 

Example 1:

Input: nums = [1,3,5]
Output: 1
Example 2:

Input: nums = [2,2,2,0,1]
Output: 0
 

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums is sorted and rotated between 1 and n times.

基本思想

和153相比，二分时，多一个讨论，如果当前位置等于最左边，那么两边都要搜索
 
*/

class Solution {
    int k = -1;
    int max_r;
public:
    int findMin(vector<int>& nums) {
        int ns = nums.size();
        if(nums[ns - 1] <= nums[0]){
            max_r = nums[0];
            find_k(0, ns - 1, nums);
            if(k == -1){
                return nums[0];
            }
            return nums[k];
        }
        else{
            return nums[0];
        }
    }

    void find_k(int left, int right, vector<int>& nums){
        if(left > right){return;}

        int mid = (left + right) / 2;
        if(nums[mid] > max_r){
            find_k(mid + 1, right, nums);
        }
        else if (nums[mid] < max_r){
            if(nums[mid - 1] >= max_r){
                k = mid;
            }
            else{
                find_k(left, mid - 1, nums);
            }
        }
        else{
            find_k(mid + 1, right, nums);
            find_k(left, mid - 1, nums);
        }
    }
};