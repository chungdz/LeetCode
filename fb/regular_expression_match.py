
'''
10

Regular Expression Matching

Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input: s = "mississippi", p = "mis*is*p*."
Output: false
 

Constraints:

1 <= s.length <= 20
1 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.

基本思想：
动态规划 + 递归讨论

visited[sindex][pindex] 表示匹配到这个程度的结果，如果不为-1表示已经访问过直接返回结果

剪枝：
如果已经有成功匹配全部返回不再遍历

边际判断：
sindex == slen and pindex == rlen 表示匹配成功
sindex < slen and pindex == rlen 表示模式匹配完了主串都没遍历完，返回False
sindex == slen and pindex < rlen 表示模式还没匹配完，如果模式后面的字符都可以消除掉，那么就有可能成功，所以
    if self.rep[pindex]:
        res = res or self.recur_match(sindex, pindex + 1)
主线推进:
如果相等：
    sindex + 1, pindex + 1
    如果p可以重复：
        sindex + 1, pindex
        sindex, pindex + 1
如果不等：
    如果p可以重复：
        sindex, pindex + 1

'''

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        self.visited = [[-1] * 22 for i in range(32)]
        plen = len(p)
        self.p = ""
        self.s = s
        self.rep = []
        pindex = 0
        while pindex < plen:
            self.p += p[pindex]
            if pindex + 1 < plen and p[pindex + 1] == '*':
                self.rep.append(True)
                pindex += 2
            else:
                self.rep.append(False)
                pindex += 1
        self.rlen = len(self.p)
        self.slen = len(s)
        self.match = False

        self.recur_match(0, 0)
        return self.match

    def recur_match(self, sindex, pindex):

        if self.match:
            return False

        if sindex == self.slen and pindex == self.rlen:
            self.match = True
            return True
        
        if sindex < self.slen and pindex == self.rlen:
            return False

        if self.visited[sindex][pindex] != -1:
            return self.visited[sindex][pindex]
        
        res = False

        if sindex == self.slen and pindex < self.rlen:
            if self.rep[pindex]:
                res = res or self.recur_match(sindex, pindex + 1)
            self.visited[sindex][pindex] = res
            return res
        
        if self.s[sindex] == self.p[pindex] or self.p[pindex] == '.':
            # opt 1
            res = res or self.recur_match(sindex + 1, pindex + 1)
            if self.rep[pindex]:
                # opt 2 repeat pindex one time
                res = res or self.recur_match(sindex + 1, pindex)
                # opt 3 repeat pindex 0 time
                res = res or self.recur_match(sindex, pindex + 1)
        else:
            if self.rep[pindex]:
                # repeat pindex 0 time
                res = res or self.recur_match(sindex, pindex + 1)
        
        self.visited[sindex][pindex] = res
        return res
