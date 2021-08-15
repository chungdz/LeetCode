#include<string>
#include<algorithm>
#include<map>
using namespace std;

/**
 * 159
 * 
 * 
Given a string s, return the length of the longest substring that contains at most two distinct characters.

Example 1:

Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.
Example 2:

Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.
 

Constraints:

1 <= s.length <= 10^4
s consists of English letters.
 * 
 * 
 * 基本思路
 * 
 * 双指针 + map
 * 
 * 用map来记录字符类型数量，判断是否字串合规
 * 
 */

class Solution {
    map<char, int> record;
    int max_left, max_size;
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int total_size = s.size();
        // init
        max_left = 0;
        max_size = 1;

        int lp = 0, rp = 0;
        record[s[0]] = 1;
        while(rp < total_size){
            // find max right
            while(rp + 1 < total_size){
                if(record.size() == 2 && record.find(s[rp + 1]) == record.end()){
                    break;
                }
                rp += 1;
                if(record.find(s[rp]) == record.end()){
                    record[s[rp]] = 1;
                }
                else{
                    record[s[rp]] += 1;
                }
            }
            // update results
            if(rp - lp + 1 > max_size){
                max_size = rp - lp + 1;
                max_left = lp;
            }
            // move to new substring
            if(rp == total_size - 1){break;}

            rp += 1;
            record[s[rp]] = 1;
            while(record.size() > 2){
                record[s[lp]] -= 1;
                if(record[s[lp]] == 0){
                    record.erase(s[lp]);
                }
                lp += 1;
            }
        }

        return max_size;
    }
};