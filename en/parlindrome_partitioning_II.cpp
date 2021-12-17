#include<vector>
#include<string>
#include<algorithm>
#include<memory.h>
using namespace std;

/*
132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1
 

Constraints:

1 <= s.length <= 2000
s consists of lower-case English letters only.

基本思想

动态规划找到所有的回文串
dp[i][j] = true if i >= j
dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]) if i < j (j >= i + 1)

回溯 + 动态规划
*/

class Solution {
    bool isPalindrome[2000][2000];
    int minRecord[2000];
    int ss;
    string mys;
public:
    int minCut(string s) {
        ss = s.size();
        mys = s;
        for(int i = 0;i < ss;++i)
            for(int j = i;j >= 0;--j)
                isPalindrome[i][j] = true;

        for(int i = ss - 1;i >= 0;--i)
            for(int j = i + 1;j < ss;++j)
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && (s[i] == s[j]);
        
        memset(minRecord, -1, sizeof(minRecord));
        return dfs(0); 
    }

    int dfs(int start){
        if(start == ss)
            return -1;
        if(minRecord[start] != -1)
            return minRecord[start];

        int curMin = 2000;
        for(int end = start;end < ss;end++){
            if(isPalindrome[start][end]){
                int curCut = 1 + dfs(end + 1);
                curMin = min(curMin, curCut);
            }
        }
        minRecord[start] = curMin;
        return curMin;
    }
};