'''
564 Find the Closest Palindrome
Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.

The closest is defined as the absolute difference minimized between two integers.

 

Example 1:

Input: n = "123"
Output: "121"
Example 2:

Input: n = "1"
Output: "0"
Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
 

Constraints:

1 <= n.length <= 18
n consists of only digits.
n does not have leading zeros.
n is representing an integer in the range [1, 10^18 - 1].

10^18可以用unsigned long long 来表示，python可以不用管
所以回文串可以直接遍历几个情况，回文串由前半部分定义，因为后半部分的更改会让数字的变化更小

所有参考数字

前半部分
前半部分 + 1
前半部分 - 1
总长减一的全9
总长加一的1000001
'''

class Solution:
    def nearestPalindromic(self, n: str) -> str:
        nlen = len(n)
        if nlen < 2:
            return str(int(n) - 1)
        
        candidate = [10 ** (nlen - 1) - 1, 10 ** nlen + 1]
        half = (nlen + 1) // 2
        remain = nlen - half
        selfPrefix = int(n[:half])
        for curpre in range(selfPrefix - 1, selfPrefix + 2):
            cur_prefix = str(curpre)
            cur_len = len(cur_prefix)
            if cur_len > remain:
                suffix = cur_prefix[-2::-1]
            else:
                suffix = cur_prefix[::-1]
            whole = cur_prefix + suffix
            candidate.append(int(whole))
        
        cur_num = int(n)
        ans = -1
        min_dif = -1
        for c in candidate:
            if c != cur_num:
                dif = abs(cur_num - c)
                if ans == -1 or ((dif < min_dif) or (dif == min_dif and c < ans)):
                    ans = c
                    min_dif = dif
        return str(ans)

