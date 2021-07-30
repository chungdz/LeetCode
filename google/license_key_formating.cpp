#include<string>
#include<algorithm>
using namespace std;

/***
 * 482
 * 
 *  License Key Formatting
You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.

We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

 

Example 1:

Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.
Example 2:

Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
 

Constraints:

1 <= s.length <= 105
s consists of English letters, digits, and dashes '-'.
1 <= k <= 104
 * 
 * 
 * 
 * 
 * 字符串处理，涉及字符串去除符号，插入符号，转换大小写
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/

class Solution {

    string sub_char(string s, string chars){
        for (char c: chars){
            s.erase(std::remove(s.begin(), s.end(), c), s.end());
        }
        return s;
    }

public:
    string licenseKeyFormatting(string s, int k) {
        s = sub_char(s, "-");
        int total_length = s.length();
        int dash_count = 0;
        for(int i = total_length - 1;i >= 0;i--){
            s[i] = toupper(s[i]);
            dash_count++;
            if(dash_count == k && i != 0){
                s.insert(i, "-");
                dash_count = 0;
            }
        }
        return s;
    }
};