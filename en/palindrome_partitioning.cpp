#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*
131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]
 

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.

基本思想

动态规划找到所有的回文串
dp[i][j] = true if i >= j
dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]) if i < j (j >= i + 1)

回溯
*/

class Solution {
    bool dp[16][16];
    vector<vector<string>> res;
    vector<string> cur_res;
    int ss;
    string mys;
public:
    vector<vector<string>> partition(string s) {
        ss = s.size();
        mys = s;
        for(int i = 0;i < ss;++i)
            for(int j = i;j >= 0;--j)
                dp[i][j] = true;

        for(int i = ss - 1;i >= 0;--i)
            for(int j = i + 1;j < ss;++j)
                dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
                
        dfs(0);
        return res; 
    }

    void dfs(int start){
        if(start == ss){
            res.push_back(cur_res);
            return;
        }

        for(int end = start;end < ss;end++){
            if(dp[start][end]){
                cur_res.push_back(mys.substr(start, end - start + 1));
                dfs(end + 1);
                cur_res.pop_back();
            }
        }
    }
};