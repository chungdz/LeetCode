#include<string>
#include<algorithm>
#include<map>
using namespace std;

/**
 * 
 * 76
 * 
 * 
 * 
 * Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 

Constraints:

m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.
 * 
 * 
 * 基本思路：
 * 
 * map判断+双指针
 * 
 * 如何判断是否是合规的substring：用map记录t串的每个char的数量，遍历s串时，
 * 每次遇到记录的char就把数量减一，然后把counter（初始值为t的长度）减一，如果char数量已经小于等于零，
 * 就只数量减一，counter不变。直到counter变成零，表示找到第一个字串
 * 
 * 如何寻找最小字串：
 * 从当前右索引开始，先找到最近的左边索引，判断依据是每次左索引移动时，map中的相应char数量加一，
 * 但是map中的char数量不能大于零，一旦遇到左索引再移动一格，char数量有大于零的情况，就跳出循环
 * 
 * 找到最近左索引后更新最小字串，然后右索引加一，更新map信息（char数量减一）。在这里新的右索引在寻找左索引时，从上一次的位置往下找。
 * 一个是保证map信息的匹配度，一个是如果左索引还在更前面的位置，字串不会更短。
 * 
 * 
 */

class Solution {
    map<char, int> record;
public:
    string minWindow(string s, string t) {
        int size_ss = s.size();
        int size_ts = t.size();
        int min_size, min_lp;
        // construct character record
        for(char c: t){
            if(record.find(c) != record.end()){record[c] += 1;}
            else{record[c] = 1;}
        }

        // find first substring
        int lp = 0, rp = 0;
        int counter = size_ts;
        while(rp < size_ss){
            if(record.find(s[rp]) != record.end()){
                if(record[s[rp]] > 0){
                    record[s[rp]] -= 1;
                    counter -= 1;
                    if(counter <= 0){
                        break;
                    }
                }
                else{record[s[rp]] -= 1;}
            }

            ++rp;
        }
        // no substring
        if(rp >= size_ss){return "";}
        // find min string
        min_size = rp - lp + 1;
        min_lp = lp;
        while(rp < size_ss){
            // find nearest left pointer
            while(lp <= rp){
                if(record.find(s[lp]) != record.end()){
                    if(record[s[lp]] < 0){
                        record[s[lp]] += 1;
                    }
                    else if(record[s[lp]] == 0){
                        break;
                    }
                }

                ++lp;
            }
            // update min substring
            int new_size = rp - lp + 1;
            if(new_size < min_size){
                min_size = new_size;
                min_lp = lp;
            }
            // update right pointer
            ++rp;
            if(record.find(s[rp]) != record.end()){
                record[s[rp]] -= 1;
            }
        }

        return s.substr(min_lp, min_size);
    }
};