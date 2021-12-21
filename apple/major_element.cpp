#include<vector>
#include<algorithm>
using namespace std;

/*
169. Majority Element

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-231 <= nums[i] <= 231 - 1
 

Follow-up: Could you solve the problem in linear time and in O(1) space?

基本思想

因为major数字一定存在，且major数字总是多余其他数字

可以用一个变量cur_num和counter来记录

遍历数组，如果counter等于0，cur_num = n
         else   如果cur_num != n，counter -= 1
         else   如果cur_num == n，counter += 1
*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int counter = 0;
        int cur_num = 0;
        int ns = nums.size();
        for(int n: nums){
            if(counter == 0){
                cur_num = n;
                counter = 1;
            }
            else if(n == cur_num)
                counter += 1;
            else
                counter -= 1; 
        }

        return cur_num;
    }
};