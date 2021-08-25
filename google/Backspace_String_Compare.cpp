#include<string>
#include<stack>
#include<algorithm>
using namespace std;

/**
 * 844
 * 
Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

 

Example 1:

Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
Example 2:

Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".
Example 3:

Input: s = "a##c", t = "#a#c"
Output: true
Explanation: Both s and t become "c".
Example 4:

Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".
 

Constraints:

1 <= s.length, t.length <= 200
s and t only contain lowercase letters and '#' characters.
 

Follow up: Can you solve it in O(n) time and O(1) space?
 * 
 * 
 * 基本思路
 * 
 * 栈的应用
 * 
 * 
 * 
 * 
 * 
 */

class Solution {
    string get_s(string origin){
        stack<char> ss;
        for(char c: origin){
            if(c == '#'){
                if(!ss.empty()){ss.pop();}
            }
            else{
                ss.push(c);
            }
        }

        string res = "";
        while(!ss.empty()){
            res.push_back(ss.top());
            ss.pop();
        }

        return res;
    }
public:
    bool backspaceCompare(string s, string t) {
        return get_s(s) == get_s(t);
    }
};