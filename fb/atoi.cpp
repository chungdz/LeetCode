#include<string>
#include<limits.h>
#include<algorithm>
using namespace std;

/*
8

Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

Read in and ignore any leading whitespace.
Check if the next character (if not already at the end of the string) is '-' or '+'. Read this character in if it is either. This determines if the final result is negative or positive respectively. Assume the result is positive if neither is present.
Read in next the characters until the next non-digit charcter or the end of the input is reached. The rest of the string is ignored.
Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then clamp the integer so that it remains in the range. Specifically, integers less than -231 should be clamped to -231, and integers greater than 231 - 1 should be clamped to 231 - 1.
Return the integer as the final result.
Note:

Only the space character ' ' is considered a whitespace character.
Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.
 

Example 1:

Input: s = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.
Example 2:

Input: s = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-231, 231 - 1], the final result is -42.
Example 3:

Input: s = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-231, 231 - 1], the final result is 4193.
Example 4:

Input: s = "words and 987"
Output: 0
Explanation:
Step 1: "words and 987" (no characters read because there is no leading whitespace)
         ^
Step 2: "words and 987" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "words and 987" (reading stops immediately because there is a non-digit 'w')
         ^
The parsed integer is 0 because no digits were read.
Since 0 is in the range [-231, 231 - 1], the final result is 0.
Example 5:

Input: s = "-91283472332"
Output: -2147483648
Explanation:
Step 1: "-91283472332" (no characters read because there is no leading whitespace)
         ^
Step 2: "-91283472332" ('-' is read, so the result should be negative)
          ^
Step 3: "-91283472332" ("91283472332" is read in)
                     ^
The parsed integer is -91283472332.
Since -91283472332 is less than the lower bound of the range [-231, 231 - 1], the final result is clamped to -231 = -2147483648.
 

Constraints:

0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.

基本思想：

1.检查头部空格
2.检查是否有符号
3.找到数字字串
4.删除头部0
6.检查是否字串长度小于一
7.检查是否超范围
8.重组数字，注意乘以10的时候倍数为long long


**/

class Solution {
    string max_int = to_string(INT32_MAX);
    string min_int = to_string(INT32_MIN).erase(0, 1);
public:
    int myAtoi(string s) {
        int res = 0;
        int starts = 0, slen = 0;
        bool is_negative = false;


        int ss = s.size();
        while(starts < ss && s[starts] == ' '){
            starts++;
        }

        if(starts >= ss){return res;}

        if(!isdigit(s[starts])){
            if(s[starts] == '-'){
                is_negative = true;
                starts += 1;
            }
            else if(s[starts] == '+'){
                starts += 1;
            }
            else{return res;}
        }

        int origin = starts;
        while(starts < ss && isdigit(s[starts])){
            starts += 1;
            slen += 1;
        }

        string int_fs = s.substr(origin, slen);
        while(int_fs[0] == '0'){
            int_fs.erase(0, 1);
        }
        if(int_fs == ""){return res;}
        slen = int_fs.size();

        if(!is_negative){
            if(slen > max_int.size() || (slen == max_int.size() && int_fs >= max_int)){
                return INT32_MAX;
            }
        }
        else{
            if(slen > min_int.size() || (slen == min_int.size() && int_fs >= min_int)){
                return INT32_MIN;
            }
        }

        int final_res = 0;
        long long cur_plus = 1;
        reverse(int_fs.begin(), int_fs.end());

        for(char ch: int_fs){
            final_res += cur_plus * (ch - '0');
            cur_plus *= 10;
        }

        if(is_negative){
            return -final_res;
        }
        return final_res;
    }
};