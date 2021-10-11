'''
32 Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 3 * 10^4
s[i] is '(', or ')'.
'''

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        slen = len(s)
        dp = [0] * slen
        max_len = 0
        for i in range(1, slen):
            if s[i] == ')':
                if s[i - 1] == '(':
                    dp[i] = 2
                    if i - 2 >= 0:
                        dp[i] += dp[i - 2]
                if s[i - 1]  == ')':
                    if dp[i - 1] > 0:
                        pre_start = i - dp[i - 1] - 1
                        if pre_start >= 0 and s[pre_start] == '(':
                            dp[i] = 2 + dp[i - 1]
                            if pre_start - 1 >= 0:
                                dp[i] += dp[pre_start - 1]
                max_len = max(max_len, dp[i])
        return max_len
