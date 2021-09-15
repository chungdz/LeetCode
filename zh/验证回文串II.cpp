/*
680

给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。

示例 1:

输入: "aba"
输出: True
示例 2:

输入: "abca"
输出: True
解释: 你可以删除c字符。
注意:

字符串只包含从 a-z 的小写字母。字符串的最大长度是50000。
*/
#include <string>
using namespace std;

/*
验证回文串，从头往后双指针比较

如果遇到不同的，删除左边的或者删除右边的，重新验证
*/
class Solution {
    bool checked = false;
public:
    bool validPalindrome(string s) {
        int p1 = 0;
        int p2 = s.size() - 1;

        while(p2 > p1){
            if(s[p1] == s[p2]){
                p1++;
                p2--;
            }
            else{
                if(checked){
                    return false;
                }
                else{
                    string new_1 = s;
                    string new_2 = s;
                    new_1.erase(p1, 1);
                    new_2.erase(p2, 1);
                    checked = true;
                    return (validPalindrome(new_1) | validPalindrome(new_2));
                };
            }
        }

        return true;
    }
};