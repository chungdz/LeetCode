'''
72 Edit Distance

Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.

基本思想
动态规划题
dp[i][j]表示消除word1[0: i]和word2[0: j]需要的最小方式
当i或者j变成-1的时候，到达边界条件，返回剩余的字符数量

如果当前字符相等，那么dp[i][j] == dp[i - 1][j - 1]
如果不等，那么因为有六种方式消除不同，而因为对称性，给出三种转移方式，找到最小值
dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])
'''

class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        len1 = len(word1)
        len2 = len(word2)
        self.dp = [[-1] * len2 for _ in range(len1)]
        self.w1 = word1
        self.w2 = word2
        return self.dfs(len1 - 1, len2 - 1)
    
    def dfs(self, index1, index2):
        if index1 == -1 or index2 == -1:
            return max(index1, index2) + 1
        
        if self.dp[index1][index2] != -1:
            return self.dp[index1][index2]
        
        if self.w1[index1] == self.w2[index2]:
            return self.dfs(index1 - 1, index2 - 1)
        
        c1 = 1 + self.dfs(index1 - 1, index2)
        c2 = 1 + self.dfs(index1, index2 - 1)
        c3 = 1 + self.dfs(index1 - 1, index2 - 1)
        
        self.dp[index1][index2] = min(c1, c2, c3)
        
        return self.dp[index1][index2]