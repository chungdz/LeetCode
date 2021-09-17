#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

/*

242

Given two strings s and t, return true if t is an anagram of s, and false otherwise.

 

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
 

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
 

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

基本思想

map的应用


**/

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()){return false;}

        unordered_map<char, int> sm;
        for(char ch: s){
            if(sm.find(ch) == sm.end()){
                sm[ch] = 0;
            }
            sm[ch] += 1;
        }

        for(char ch: t){
            if(sm.find(ch) == sm.end()){
                return false;
            }
            if(sm[ch] <= 0){return false;}
            sm[ch] -= 1;
        }

        return true;
    }
};