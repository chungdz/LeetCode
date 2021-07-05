/*
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:

输入: "race a car"
输出: false
*/
#include<string>
#include<cctype>
using namespace std;

/*
前后扫描
重点是判断是否是字母或者是数字
*/
class Solution {
public:
    bool isPalindrome(string s) {
        int lenth = s.length();
        int headp = 0;
        int tailp = lenth - 1;
        while(headp < lenth && tailp >= 0){
            //find head valid
            while(!isalnum(s[headp])){
                headp++;
                if(headp >= lenth){return true;}
            }
            //find tail valid
            while(!isalnum(s[tailp])){
                tailp--;
                if(headp < 0){return true;}
            }
            //cmp
            if(tolower(s[headp]) != tolower(s[tailp])){return false;}
            headp++;
            tailp--;
        }

        return true;
    }
};