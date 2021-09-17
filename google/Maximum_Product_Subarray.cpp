#include<vector>
#include<algorithm>
using namespace std;

/*

152

Maximum Product Subarray

Solution
Given an integer array nums, find a contiguous non-empty subarray within the array that has the largest product, and return the product.

It is guaranteed that the answer will fit in a 32-bit integer.

A subarray is a contiguous subsequence of the array.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 

Constraints:

1 <= nums.length <= 2 * 10^4
-10 <= nums[i] <= 10
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

基本思想

类似于53最大子序列和，

只不过维持两个信息，dp[i][0]表示以i结尾的最大正乘积，dp[i][1]表示以i结尾最小负乘积

每次更新的时候，需要根据nums[i]的正负来计算dp[i][0]，dp[i][1]，如果不存在最大正乘积或者最小负乘积，就用零表示

这样需要对零做特殊判断处理

dp存储可以优化成O(1)
**/

class Solution {
    // first is for max positive
    // second is for min negative
    int max_product[30000][2];
public:
    int maxProduct(vector<int>& nums) {
        int ss = nums.size();
        if(nums[0] >= 0){
            max_product[0][0] = nums[0];
            max_product[0][1] = 0;
        }
        else{
            max_product[0][0] = 0;
            max_product[0][1] = nums[0];
        }
        int max_integer = nums[0];

        for(int i = 1;i < ss;++i){
            if(nums[i] >= 0){
                if(max_product[i - 1][0] != 0){
                    max_product[i][0] = nums[i] * max_product[i - 1][0];
                }
                else{
                    max_product[i][0] = nums[i];
                }
                max_integer = max(max_product[i][0], max_integer);

                max_product[i][1] = nums[i] * max_product[i - 1][1];
            }
            else{
                if(max_product[i - 1][0] != 0){
                    max_product[i][1] = nums[i] * max_product[i - 1][0];
                }
                else{
                    max_product[i][1] = nums[i];
                }

                max_integer = max(max_product[i][1], max_integer);

                if(max_product[i - 1][1] != 0){
                    max_product[i][0] = nums[i] * max_product[i - 1][1];
                    max_integer = max(max_product[i][0], max_integer);
                }
                else{
                    max_product[i][0] = 0;
                }
            }
        }

        return max_integer;
    }
};