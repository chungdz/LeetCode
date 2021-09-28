"""
161
One Edit Distance
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:

Insert exactly one character into s to get t.
Delete exactly one character from s to get t.
Replace exactly one character of s with a different character to get t.
 

Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.
Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.
Example 3:

Input: s = "a", t = ""
Output: true
Example 4:

Input: s = "", t = "A"
Output: true
 

Constraints:

0 <= s.length <= 10^4
0 <= t.length <= 10^4
s and t consist of lower-case letters, upper-case letters and/or digits.

基本思想

分情况为长度相等和长度不等

相等检查替换，不等检查删除
"""

class Solution:
    def isOneEditDistance(self, s: str, t: str) -> bool:
        slen = len(s)
        tlen = len(t)

        if slen > tlen:
            if slen != tlen + 1:
                return False

            long = s
            short = t
            longlen = slen
            shortlen = tlen
        else:
            if tlen > slen + 1:
                return False
            long = t
            short = s
            longlen = tlen
            shortlen = slen
        
        sindex = 0
        lindex = 0

        ops = 0
        while sindex < shortlen:
            if short[sindex] != long[lindex]:
                if slen == tlen:
                    ops += 1
                    if ops > 1:
                        return False
                else:
                    lindex += 1
                    ops += 1
                    if ops > 1:
                        return False
                    continue
                
            sindex += 1
            lindex += 1
        
        if slen == tlen:
            if ops == 1:
                return True
            else:
                return False
        else:
            if ops == 1 and lindex >= longlen:
                return True
            elif ops == 0 and lindex < longlen:
                return True
            else:
                return False
            