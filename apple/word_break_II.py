'''
140 Word Break II

Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
 

Constraints:

1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.

基本思想：
用Trie处理好所有word

self.dp[i]表示以i开头的字串有多少个合规的分割点
分割点的判断是如果s[i: j + 1]是一个单词，并且self.dp[j]含有分割点
为了方便判断，初始化self.dp[slen] = [-1]

根据self.dp[i]保存的分割点递归输出结果
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
    def wordBreak(self, s: str, wordDict):
        self.t = Trie()
        for word in wordDict:
            self.t.insert(word)
        self.s = s
        self.slen = len(s)
        self.dp = [[] for _ in range(self.slen)]
        # for easier judgement
        self.dp.append([-1])
        # search split point
        for i in range(self.slen - 1, -1, -1):
            self.search_valid(i)
        
        self.results = []
        self.dfs("", 0)
        return self.results
        
    def search_valid(self, index):
        curn = self.t
        curidx = index
        while curidx < self.slen:
            next_n = curn.find_child(self.s[curidx])
            if next_n is None:
                break
            else:
                if next_n.has_word and len(self.dp[curidx + 1]) > 0:
                    self.dp[index].append(curidx)
                curidx += 1
                curn = next_n
    
    def dfs(self, cur_string, index):
        if index >= self.slen:
            self.results.append(cur_string)
            return 
        
        for split_point in self.dp[index]:
            new_string = cur_string + " " + self.s[index: split_point + 1]
            self.dfs(new_string, split_point + 1)

