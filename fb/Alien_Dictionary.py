'''
269
Alien Dictionary

Solution
There is a new alien language that uses the English alphabet. However, the order among the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary, where the strings in words are sorted lexicographically by the rules of this new language.

Return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there is no solution, return "". If there are multiple solutions, return any of them.

A string s is lexicographically smaller than a string t if at the first letter where they differ, the letter in s comes before the letter in t in the alien language. If the first min(s.length, t.length) letters are the same, then s is smaller if and only if s.length < t.length.

 

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
'''

class Solution:
    def alienOrder(self, words):
        g = {}
        ws = len(words)
        for w in words:
            for ch in w:
                if ch not in g:
                    g[ch] = {
                        'in_degree': 0,
                        'out': set()
                    }
        
        total_ch = len(g)

        for i in range(1, ws):
            pre_w = words[i - 1]
            cur_w = words[i]
            slen = min(len(pre_w), len(cur_w))
            find_diff = False
            for j in range(slen):
                if pre_w[j] != cur_w[j]:
                    if cur_w[j] not in g[pre_w[j]]['out']:
                        g[pre_w[j]]['out'].add(cur_w[j])
                        g[cur_w[j]]['in_degree'] += 1
                    
                    find_diff = True
                    break
            
            if not find_diff and len(pre_w) > len(cur_w):
                return ""
        
        queue = []
        for k, v in g.items():
            if v['in_degree'] == 0:
                queue.append(k)
        
        res = []
        while len(queue) > 0:

            curc = queue[0]
            queue.pop(0)
            res.append(curc)

            for son in g[curc]['out']:
                g[son]['in_degree'] -= 1
                if g[son]['in_degree'] == 0:
                    queue.append(son)
            
            del g[curc]
        
        if len(res) == total_ch:
            return "".join(res)
        else:
            return ""
            