#include<string>
#include<ctype.h>
#include<algorithm>
using namespace std;

/*
680

Valid Palindrome II

Given a string s, return true if the s can be palindrome after deleting at most one character from it.

 

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 10^5
s consists of lowercase English letters.

基本思想：

扫描，如果出现不相同，记录当前位置，移动前指针，继续检测，再次出现不相同，回溯

移动右指针，再次检测，如果还有错，就返回false，不然就返回true
**/

class Solution {
public:
    bool validPalindrome(string s) {
        int front = 0;
        int back = s.size() - 1;
        bool not_problem = true;
        int delete_op = 0;
        int pre_front, pre_back;
        while(back > front){

            if(tolower(s[front]) != tolower(s[back])){
                delete_op += 1;
                if(delete_op > 1){
                    if(not_problem){
                        not_problem = false;
                        front = pre_front;
                        back = pre_back - 1;
                        delete_op = 1;
                        continue;
                    }
                    else{
                        return false;
                    }
                }
                pre_front = front;
                pre_back = back;
                ++front;
                continue;
            }

            ++front;
            --back;
        }
        
        return true;
    }
};