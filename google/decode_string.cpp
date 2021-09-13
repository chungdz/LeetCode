#include<algorithm>
#include<string>
#include<ctype.h>
using namespace std;

/*
394

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

 

Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"
Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
Example 4:

Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"
 

Constraints:

1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].




基本思想

字符串处理，递归，括号搜寻


**/


class Solution {
public:
    string decodeString(string s) {
        string res = "";
        int slen = s.size();
        int sindex = 0;
        while(sindex < slen){
            if(isalpha(s[sindex])){
                res.push_back(s[sindex]);
                ++sindex;
            }
            else{
                // get repeat number
                int digit_len = 1;
                int dight_index = sindex + 1;
                while(isdigit(s[dight_index])){
                    digit_len += 1;
                    dight_index += 1;
                }
                int repeat_num = stoi(s.substr(sindex, digit_len));
                // get substring
                sindex = dight_index + 1;
                int substr_index = sindex;
                int substr_len = 0;
                int flag = 1;
                while(true){
                    if(s[substr_index] == '['){
                        flag += 1;
                    }
                    else if(s[substr_index] == ']'){
                        flag -= 1;
                        if(flag == 0){break;}
                    }
                    substr_len += 1;
                    substr_index += 1;
                }
                string substr = decodeString(s.substr(sindex, substr_len));
                // add to result
                while(repeat_num--){
                    res += substr;
                }
                sindex = substr_index + 1;
            }
        }

        return res;
    }
};