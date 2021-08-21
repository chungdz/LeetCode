#include<string>
#include<algorithm>
#include<stack>
using namespace std;

/***
 * 20
 * 
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
Example 4:

Input: s = "([)]"
Output: false
Example 5:

Input: s = "{[]}"
Output: true
 

Constraints:

1 <= s.length <= 10^4
s consists of parentheses only '()[]{}'
 * 
 * 
 * 基本思想
 * 
 * 栈的经典题型
 * 
 * 
 * 
 * 
*/

class Solution {
    stack<char> record;

    bool check_match(char left, char right){
        if(right == ')'){return left == '(';}
        else if(right == '}'){return left == '{';}
        else if(right == ']'){return left == '[';}

        return false;
    }

    bool is_left(char c){
        return c == '(' || c == '{' || c == '[';
    }
public:
    bool isValid(string s) {
        for(char cc: s){
            if(is_left(cc)){
                record.push(cc);
            }
            else{
                if(record.empty()){return false;}
                char topc = record.top();
                if(!check_match(topc, cc)){return false;}
                record.pop();
            }
        }

        if(!record.empty()){return false;}
        return true;
    }
};