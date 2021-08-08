#include<vector>
#include<algorithm>
using namespace std;

/***
 * 31
 * 
 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).

The replacement must be in place and use only constant extra memory.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
Example 4:

Input: nums = [1]
Output: [1]
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
 * 
 * 
 * 解题思路
 * 
 * next permutation是找到字典序更大的下一个排列组合
 * 
 * 字典序最大的排列组合是大到小
 * 
 * 从尾部往前扫描，找到第一个字典序不是最大的字串（也就是第一个i，使得nums[i]小于最大的nums[j], j > i）
 * 
 * 把i + 1到进行排序，找到nums[i]的upper bound，交换位置，就是下一个字典序了
 * 
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int total_size = nums.size();
        int max_num = nums[total_size - 1];
        for(int cur_index = total_size - 2;cur_index >= 0;--cur_index){
            int cur_number = nums[cur_index];
            if(cur_number >= max_num){max_num = cur_number;}
            else{
                // sort array that greater than current index
                vector<int>::iterator array_begin = nums.begin() + cur_index + 1;
                sort(array_begin, nums.end());
                vector<int>::iterator ub = upper_bound(array_begin, nums.end(), cur_number);
                iter_swap(nums.begin() + cur_index, ub);
                return;
            }
        }
        sort(nums.begin(), nums.end());
        return;
    }
};