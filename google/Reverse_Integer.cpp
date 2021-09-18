#include<limits.h>
#include<string>
#include<algorithm>
using namespace std;

/*

7

Reverse Integer

Solution
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

 

Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
Example 3:

Input: x = 120
Output: 21
Example 4:

Input: x = 0
Output: 0
 

Constraints:

-2^31 <= x <= 2^31 - 1

基本思想

把它转成字符串再比较

将最大的INT值也变成字符串，如果当前字符串大于INT的字符串值，就不合法


**/

class Solution {
public:
    int reverse(int x) {
        string int_max = to_string(INT32_MAX);
        string int_min = to_string(INT32_MIN);
        int_min.erase(0, 1);

        string cur_int  = to_string(x);
        if(x < 0){
            cur_int.erase(0, 1);
        }
        std::reverse(cur_int.begin(), cur_int.end());
        while(cur_int[0] == '0' && cur_int.size() > 1){
            cur_int.erase(0, 1);
        }

        // check valid
        if(x >= 0){
            if(cur_int.size() > int_max.size()){
                return 0;
            }
            else if(cur_int.size() == int_max.size() && cur_int > int_max){
                return 0;
            }
            return stoi(cur_int);
        }
        else{
            if(cur_int.size() > int_min.size()){
                return 0;
            }
            else if(cur_int.size() == int_min.size() && cur_int > int_min){
                return 0;
            }
            return -stoi(cur_int);
        }
        
    }
};