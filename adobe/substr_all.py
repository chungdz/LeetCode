import re

'''
30 Substring with Concatenation of All Words

You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that is a concatenation of each word in words exactly once, in any order, and without any intervening characters.

You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
 

Constraints:

1 <= s.length <= 10^4
s consists of lower-case English letters.
1 <= words.length <= 5000
1 <= words[i].length <= 30
words[i] consists of lower-case English letters.

基本思想

字符串匹配 + 滑动窗口

第一步，找到每个word在s中出现的位置，因为每个词长度一致，所以不会出现同一个位置开始有不同词语的可能性，得到start_info[index] = word
第二步，统计每个词语出现的次数wdict，因为可能有重复词汇

因为每个单词长度一致，只需要做len(word)这么多次的滑动窗口遍历就可以了，每次滑动窗口左边开始的位置是range(len(word))
对每次滑动窗口遍历，初始化一个dict记录窗口中词汇出现的次数，初始化一个cnt=0，滑动窗口指针移动的步长为len(word)：
    确定左指针，一定是有效的词汇开头
    往右扩展右指针，每次都往dict中加入合规词汇，如果右指针c_end存在与start_info中且合规(指次数不大于wdict)，cnt加一
        如果此时正好cnt=len(words)，那么将左指针位置加入答案中，并且滑动窗口整体往右移步一格
    如果遇见重复过多的word，就收缩左指针直到word合规
    如果遇见非法开头，直接初始化所有变量，将左右指针全部右移到下一个合法开头

本题非常类似之前做的数字类型的滑动窗口，不同的是需要做多组，并且需要确定步长
'''

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        if len(s) < len(words[0]):
            return []
        
        wdict = {}
        for word in words:
            if word not in wdict:
                wdict[word] = 1
            else:
                wdict[word] += 1
            
        
        start_info = {}
        for word, winfo in wdict.items():
            # result = [_.start() for _ in re.finditer(word, s)]
            result = [i for i in range(len(s)) if s.startswith(word, i)]
            for sindex in result:
                start_info[sindex] = word

        slen = len(s)
        wlen = len(words)
        sinlen = len(words[0])
        res = []
        for window_start in range(sinlen):
            c_start = window_start
            c_end = c_start
            window_cnt = 0
            inwindow = {}
            while c_end < slen:

                if c_end in start_info:
                    new_w = start_info[c_end]
                    if new_w not in inwindow or wdict[new_w] > inwindow[new_w]:
                        self.dict_add(inwindow, new_w)
                        window_cnt += 1
                        if window_cnt == wlen:
                            res.append(c_start)
                            self.dict_remove(inwindow, start_info[c_start])
                            window_cnt -= 1
                            c_start += sinlen
                        c_end += sinlen
                    else:
                        while new_w in inwindow and wdict[new_w] == inwindow[new_w]:
                            self.dict_remove(inwindow, start_info[c_start])
                            window_cnt -= 1
                            c_start += sinlen
                        
                        self.dict_add(inwindow, new_w)
                        window_cnt += 1
                        c_end += sinlen
                else:
                    while c_end not in start_info and c_end < slen:
                        inwindow.clear()
                        window_cnt = 0
                        c_end += sinlen
                        c_start = c_end
        return res
    
    def dict_add(self, cdict, ckey):

        if ckey in cdict:
            cdict[ckey] += 1
        else:
            cdict[ckey] = 1
    
    def dict_remove(self,cdict, ckey):

        if cdict[ckey] > 1:
            cdict[ckey] -= 1
        else:
            cdict.pop(ckey)
