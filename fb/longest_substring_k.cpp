#include<string>
#include<algorithm>
#include<map>
using namespace std;

/*
340
Longest Substring with At Most K Distinct Characters

Solution
Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

 

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
 

Constraints:

1 <= s.length <= 5 * 10^4
0 <= k <= 50

基本思想
双指针滑动窗口


**/


class Solution {
    map<char, int> record;
    int max_left, max_size;
public:
    int lengthOfLongestSubstringKDistinct(string s, int k){
        if(k == 0){return 0;}
        int total_size = s.size();
        // init
        max_left = 0;
        max_size = 1;

        int lp = 0, rp = 0;
        record[s[0]] = 1;
        while(rp < total_size){
            // find max right
            while(rp + 1 < total_size){
                if(record.size() == k && record.find(s[rp + 1]) == record.end()){
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
            while(record.size() > k){
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