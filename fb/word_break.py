'''
139 Word Break
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

基本思想

Trie + dp

Trie用作判断以dp[i]为起始点的词语是否存在
dp[i]表示以dp[i]起始的子后缀是否可以完成分割
'''

class Trie:
    def __init__(self):
        self.has_word = False
        self.children = {}
    
    def insert(self, word):
        curt = self
        for w in word:
            if w not in curt.children:
                curt.children[w] = Trie()
            curt = curt.children[w]
        curt.has_word = True
    
    def search_prefix(self, prefix):
        curt = self
        for w in prefix:
            if w in curt.children:
                curt = curt.children[w]
            else:
                return None
        return curt
    
    def has_word(self, word):
        if self.search_prefix(word) is not None:
            return True
    
    def find_child(self, c):
        if c in self.children:
            return self.children[c]
        else:
            return None

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        trie = Trie()
        for word in wordDict:
            trie.insert(word)
        self.slen = len(s)
        self.s = s
        self.root = trie
        self.dp = [-1] * self.slen
        return self.search_dp(0)

    def search_dp(self, index):

        if index >= self.slen:
            return True
        if self.dp[index] != -1:
            return self.dp[index]
        
        self.dp[index] = False

        curp = self.root
        tmp_index = index
        while tmp_index < self.slen:
            nxt = curp.find_child(self.s[tmp_index])
            if nxt is not None:
                if nxt.has_word == True:
                    self.dp[index] |= self.search_dp(tmp_index + 1)
                curp = nxt
                tmp_index += 1
            else:
                break
        
        return self.dp[index]