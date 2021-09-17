#include<vector>
#include<algorithm>
using namespace std;

/*

5

Given a string s, return the longest palindromic substring in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"
Example 3:

Input: s = "a"
Output: "a"
Example 4:

Input: s = "ac"
Output: "a"
 

Constraints:

1 <= s.length <= 1000
s consist of only digits and English letters.




基本思想

动态规划
if(s[i] == s[j])
    dp[i][j] = dp[i + 1][j - 1]
else
    dp[i][j] = false

注意处理边界i = j, i + 1 = j不需要转移，i = j的所有请况都是true，i + 1 = j只要两边相等就是true

**/

class Solution {
    bool dp[1000][1000];
public:
    string longestPalindrome(string s) {
        int cur_size = s.size();
        int max_len = 0;
        int start = -1;

        for(int i = 0;i < cur_size;++i){
            if(max_len < 1){
                max_len = 1;
                start = i;
            }
            dp[i][i] = true;
        }

        if(cur_size < 2){return s.substr(start, max_len);}

        for(int i = 0;i < cur_size - 1;++i){
            if(s[i] == s[i + 1]){
                dp[i][i + 1] = true;
                if(max_len < 2){
                    max_len = 2;
                    start = i;
                }
            }
            else{
                dp[i][i + 1] = false;
            }
        }

        if(cur_size < 3){return s.substr(start, max_len);}

        for(int step = 2;step < cur_size;step++){
            int cur_len = step + 1;
            int tail = cur_size - step;
            for(int i = 0;i < tail;++i){
                if(s[i] == s[i + step]){
                    dp[i][i + step] = dp[i + 1][i + step - 1];
                    if(dp[i][i + step] && max_len < cur_len){
                        max_len = cur_len;
                        start = i;
                    }
                }
                else{
                    dp[i][i + step] = false;
                }
            }
        }

        return s.substr(start, max_len);
    }
};

/*

优化代码，增加易读性

**/


class Solution {
    bool dp[1000][1000];
public:
    string longestPalindrome(string s) {
        int cur_size = s.size();
        int max_len = 0;
        int start = -1;

        for(int step = 0;step < cur_size;step++){
            int cur_len = step + 1;
            int tail = cur_size - step;
            for(int i = 0;i < tail;++i){
                int left = i;
                int right = i + step;
                int inner_left = left + 1;
                int inner_right = right - 1;

                if(s[left] == s[right]){
                    if(inner_left > inner_right){
                        dp[left][right] = true;
                    }
                    else{
                        dp[left][right] = dp[inner_left][inner_right];
                    }
                    
                    if(dp[left][right] && max_len < cur_len){
                        max_len = cur_len;
                        start = i;
                    }
                }
                else{
                    dp[i][i + step] = false;
                }
            }
        }

        return s.substr(start, max_len);
    }
};