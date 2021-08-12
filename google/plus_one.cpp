#include<vector>
#include<map>
#include <algorithm>
using namespace std;

/***
 * 66
 * 
 * Given a non-empty array of decimal digits representing a non-negative integer, increment one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contains a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

 

Example 1:

Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Example 3:

Input: digits = [0]
Output: [1]
 

Constraints:

1 <= digits.length <= 100
0 <= digits[i] <= 9
 * 
 * 思想类似于string add，但是更简单
 * 
 * 
*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int low_n, high_n = 1;
        int total_size = digits.size();
        
        for(int i = total_size - 1;i >= 0;--i){
            int cur_n = digits[i] + high_n;
            if(cur_n > 9){
                high_n = 1;
                low_n = 0;
            }
            else{
                high_n = 0;
                low_n = cur_n;
            }
            res.insert(res.begin(), low_n);
        }

        if(high_n > 0){res.insert(res.begin(), 1);}
        return res;
    }
    
};