'''
14 Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lower-case English letters.

基本思想
暴力搜索
'''

class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        pattern = strs[0]
        slen = len(strs)
        for i in range(1, slen):
            if pattern == "":
                break
            pattern = self.common_prefix(pattern, strs[i])

        return pattern
    
    def common_prefix(self, s1, s2):
        s1len = len(s1)
        s2len = len(s2)
        i = 0
        for j in range(s2len):
            if i >= s1len:
                break
            if s1[i] != s2[j]:
                break
            i += 1
        
        return s1[:i]