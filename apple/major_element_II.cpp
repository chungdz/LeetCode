#include<vector>
#include<algorithm>
using namespace std;

/*
229 major element II

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 10^4
-10^9 <= nums[i] <= 10^9
 

Follow up: Could you solve the problem in linear time and in O(1) space?

基本思想

和major element 1 类似
维持两个变量 两个counter

1 两个变量初始化为NONE， counter初始化为0
对于每个遍历的n
如果n == n1 or n2，那么c1 or c2 += 1
如果c1 or c2 == 0，那么n1 or n2 = n
如果c1 and c2都不等于0，而且n1 or n2 都不等于n，那么c1 and c2都减一
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n1, n2, c1 = 0, c2 = 0;
        int ns = nums.size();
        int lb = ns / 3;

        for(int n: nums){
            if(c1 != 0 && n1 == n)
                c1 += 1;
            else if (c2 != 0 && n2 == n)
                c2 += 1;
            else if(c1 == 0){
                n1 = n;
                c1 = 1;
            }
            else if(c2 == 0){
                n2 = n;
                c2 = 1;
            }
            else{
                c1 -= 1;
                c2 -= 1;
            }
        }
        vector<int> res;
        int rc1 = 0, rc2 = 0;
        for(int n: nums){
            if(c1 > 0 && n == n1)
                rc1 += 1;
            else if(c2 > 0 && n == n2)
                rc2 += 1;
        }
        if(rc1 > lb)
            res.push_back(n1);  
        if(rc2 > lb)
            res.push_back(n2);
        
        return res;
    }
};