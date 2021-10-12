#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

/*
567 Permutation in String
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

 

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
 

Constraints:

1 <= s1.length, s2.length <= 10^4
s1 and s2 consist of lowercase English letters.

基本思想：
双指针滑动窗口 + map记录
**/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        string p = s2, s = s1;
        int plen = p.size(), slen = s.size();
        if(slen < plen){return false;}
        
        unordered_map<char, int> record;
        for(char c: p){
            if(record.find(c) != record.end()){
                record[c] += 1;
            }
            else{
                record[c] = 1;
            }
        }
        int target = plen;

        int start = 0, end = start + plen;
        for(int j = start;j < end;++j){
            if(record.find(s[j]) != record.end()){
                record[s[j]] -= 1;
                if(record[s[j]] >= 0){
                    target -= 1;
                }
            }
        }
        if(target == 0){return true;}
        
        while(start + 1 <= slen - plen){
            if(record.find(s[start]) != record.end()){
                record[s[start]] += 1;
                if(record[s[start]] >= 1){
                    target += 1;
                }
            }

            start += 1;
            end += 1;

            if(record.find(s[end - 1]) != record.end()){
                record[s[end - 1]] -= 1;
                if(record[s[end - 1]] >= 0){
                    target -= 1;
                }
            }

            if(target == 0){return true;}
        }

        return false;
    }
};