#include<unordered_map>
#include<string>
#include<algorithm>
using namespace std;

/*

205

Isomorphic Strings

Solution
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

 

Example 1:

Input: s = "egg", t = "add"
Output: true
Example 2:

Input: s = "foo", t = "bar"
Output: false
Example 3:

Input: s = "paper", t = "title"
Output: true
 

Constraints:

1 <= s.length <= 5 * 10^4
t.length == s.length
s and t consist of any valid ascii character.


基本思想 

map的应用


**/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int ss = s.size();
        if(ss != t.size()){return false;}

        unordered_map<char, char> rep;
        unordered_map<char, char> reverse_rep;
        for(int i = 0;i < ss;++i){
            char cur_char = s[i];
            char target_char = t[i];
            if(rep.find(cur_char) == rep.end()){
                if(reverse_rep.find(target_char) != reverse_rep.end()){
                    return false;
                }
                rep[cur_char] = target_char;
                reverse_rep[target_char] = cur_char;
            }
            else{
                if(rep[cur_char] != target_char){
                    return false;
                }
            }
        }
        return true;
    }
};