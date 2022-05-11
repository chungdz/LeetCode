'''
1278. Palindrome Partitioning III

You are given a string s containing lowercase letters and an integer k. You need to :

First, change some characters of s to other lowercase English letters.
Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
Return the minimal number of characters that you need to change to divide the string.

 

Example 1:

Input: s = "abc", k = 2
Output: 1
Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
Example 2:

Input: s = "aabbc", k = 3
Output: 0
Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
Example 3:

Input: s = "leetcode", k = 8
Output: 0
 

Constraints:

1 <= k <= s.length <= 100.
s only contains lowercase English letters.

基本思想
一定范围内计算需要更换的字符：双指针

动态规划：
dp[i][j]表示以i结尾的子串，如果要切割j份，需要的最小次数
dp[i][j] = min(dp[k][j - 1] + cost(k + 1, i))
k >= j - 2, k < i

当j == 1时，dp[i][j] = cost(0, i)
'''

class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        self.s = s
        self.dp = [[-1] * (k + 1) for _ in range(len(s))]
        return self.dfs(len(s) - 1, k)
    
    def dfs(self, index, split_num):
        if self.dp[index][split_num] != -1:
            return self.dp[index][split_num]
        
        if split_num == 1:
            self.dp[index][split_num] = self.changeToPalindrome(0, index)
        else:
            minstep = index
            for i in range(split_num - 2, index):
                minstep = min(minstep, self.dfs(i, split_num - 1) + self.changeToPalindrome(i + 1, index))
            self.dp[index][split_num] = minstep
        
        return self.dp[index][split_num]
    
    def changeToPalindrome(self, l, r):
        lp = l
        rp = r
        res = 0
        while rp > lp:
            if self.s[lp] != self.s[rp]:
                res += 1
            lp += 1
            rp -= 1
        
        return res