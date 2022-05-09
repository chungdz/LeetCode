'''
131 Palindrome Partitioning

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

dp记录palindrome位置，然后递归遍历
'''


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        self.slen = len(s)
        self.pos = [[-1] * self.slen for _ in range(self.slen)]
        self.s = s
        self.res = []
        self.dfs(0, [])
        return self.res
        
    def dfs(self, cur_index, cur_list):
        if cur_index == self.slen:
            self.res.append(cur_list.copy())
            return
        
        for i in range(cur_index, self.slen):
            if self.isPalindrome(cur_index, i):
                cur_list.append(self.s[cur_index: i + 1])
                self.dfs(i + 1, cur_list)
                cur_list.pop()
        
    
    def isPalindrome(self, s, e):
        if s >= e:
            return True
        if self.pos[s][e] != -1:
            return self.pos[s][e]
        
        if self.s[s] == self.s[e]:
            self.pos[s][e] = self.isPalindrome(s + 1, e - 1)
        else:
            self.pos[s][e] = False
        
        return self.pos[s][e]