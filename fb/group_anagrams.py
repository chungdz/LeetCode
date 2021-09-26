'''
49
Group Anagrams

Solution
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.

基本思想

前缀树

把每个字符重新排序之后在前缀树中查询，查得到就放入同一个集合中
'''

class Trie:

    def __init__(self) -> None:
        self.has_word = False
        self.children = {}
    
    def insert_w(self, cw, ow, ch_record):
        curt = self
        for ch in cw:
            if ch not in curt.children:
                curt.children[ch] = Trie()
            curt = curt.children[ch]
        
        if curt.has_word:
            ch_record[curt.word].append(ow)
        else:
            curt.has_word = True
            curt.word = cw
            ch_record[cw] = [ow]


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        tr = Trie()
        ch_record = {}
        for cstr in strs:
            sstr = "".join(sorted(cstr))
            tr.insert_w(sstr, cstr, ch_record)
        
        return list(ch_record.values())
