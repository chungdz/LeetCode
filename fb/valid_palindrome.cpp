#include<string>
#include<ctype.h>
#include<algorithm>
using namespace std;

/*
125

Valid Palindrome

Solution
Given a string s, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
 

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.

基本思想

双指针，直接判断，遇到不是alphnum的就跳过
**/

class Solution {
public:
    bool isPalindrome(string s) {
        int front = 0;
        int back = s.size() - 1;
        while(back > front){
            while(!isalnum(s[front]) && back > front){
                front++;
            }
            while(!isalnum(s[back]) && back > front){
                back--;
            }

            if(back <= front){break;}

            if(tolower(s[front]) != tolower(s[back])){
                return false;
            }

            ++front;
            --back;
        }
        return true;
    }
};