#include<string>
#include<map>
#include<algorithm>
using namespace std;

/***
 * 3
 * 
 * Longest Substring Without Repeating Characters

Solution
Given a string s, find the length of the longest substring without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
Example 4:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
 * 
 * 
 * 
 * 动态规划
 * 
 * 用map记录前一个字串的character和对应的index，对每个新的character，检查是否在map中出现过
 * 
 * 如果不重复，加入map中，并且长度+1
 * 如果重复，找到重复元素的index，从index + 1的位置开始重新计算长度，并且删除map里在index之前的character
 * 需要有一个head指向之前的字串的起始位置
 * 
 * 
 * 
 * 
*/

class Solution {
    map<char, int> char_index;
    int record[50000];
public:
    int lengthOfLongestSubstring(string s) {
        int length = s.size();
        if(length < 1){return 0;}

        record[0] = 1;
        int max_sublen = 1;
        char_index[s[0]] = 0;
        int head = 0;

        for(int tail = 1;tail < length;++tail){
            char cur_char = s[tail];
            int cur_len;
            map<char, int>::iterator cur_it = char_index.find(cur_char);
            // find repeat
            if(cur_it != char_index.end()){
                int new_head = cur_it->second + 1;
                cur_len = tail - new_head + 1;
                for(int del_index = head;del_index < new_head;++del_index){
                    char del_key = s[del_index];
                    char_index.erase(del_key);
                }
                head = new_head;
            }
            else{
                cur_len = record[tail - 1] + 1;
            }
            char_index[cur_char] = tail;
            record[tail] = cur_len;
            max_sublen = max(cur_len, max_sublen);
        }

        return max_sublen;
    }
};