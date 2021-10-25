#include<algorithm>
#include<vector>
using namespace std;

/*
75 Sort Colors

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

 

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]
Example 3:

Input: nums = [0]
Output: [0]
Example 4:

Input: nums = [1]
Output: [1]
 

Constraints:

n == nums.length
1 <= n <= 300
nums[i] is 0, 1, or 2.

基本思想
桶排序
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int cnum[3] = {0};
        for(int n: nums)
            cnum[n] += 1;
        int ns = nums.size();
        for(int i = 0;i < ns;++i){
            if(i < cnum[0])
                nums[i] = 0;
            else if(i < cnum[0] + cnum[1])
                nums[i] = 1;
            else
                nums[i] = 2;
        }
    }
};