'''
44 Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input: s = "adceb", p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input: s = "acdcb", p = "a*c?b"
Output: false
 

Constraints:

0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'.

基本思想

暴力搜索 + 剪枝 + DP
'''

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        s = list(s)
        p = list(p)
        self.slen = len(s)

        index = 0
        while index < len(p) - 1:
            if p[index] == '*' and p[index + 1] == '*':
                p.pop(index + 1)
            else:
                index += 1

        self.plen = len(p)

        self.dp = [[-1] * (self.plen + 1) for j in range(self.slen + 1)]

        self.s = s
        self.p = p
        self.res = False
        self.dfs(0, 0)
        return self.res

    def dfs(self, sp, pp):

        if self.res:
            return False
        
        if self.dp[sp][pp] != -1:
            return self.dp[sp][pp]

        if sp == self.slen:
            if pp == self.plen:
                self.res = True
                self.dp[sp][pp] = True
                return self.dp[sp][pp]
            elif self.p[pp] == '*':
                self.dp[sp][pp] = self.dfs(sp, pp + 1)
                return self.dp[sp][pp]
            self.dp[sp][pp] = False
            return self.dp[sp][pp]
        if pp == self.plen:
            self.dp[sp][pp] = False
            return self.dp[sp][pp]
        
        res = False
        if self.p[pp] == '*':
            res |= self.dfs(sp + 1, pp + 1)
            res |= self.dfs(sp + 1, pp)
            res |= self.dfs(sp, pp + 1)
        elif self.p[pp] == '?':
            res |= self.dfs(sp + 1, pp + 1)
        elif self.s[sp] == self.p[pp]:
            res |= self.dfs(sp + 1, pp + 1)
        self.dp[sp][pp] = res
        return self.dp[sp][pp]

