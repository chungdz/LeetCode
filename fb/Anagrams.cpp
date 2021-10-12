#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

/*
438 Find All Anagrams in a String

Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
 

Constraints:

1 <= s.length, p.length <= 3 * 10^4
s and p consist of lowercase English letters.

基本思想：
双指针滑动窗口 + map记录
**/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int plen = p.size(), slen = s.size();
        vector<int> res;
        if(slen < plen){return res;}
        
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
        if(target == 0){res.push_back(start);}
        
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

            if(target == 0){res.push_back(start);}
        }

        return res;
    }
};