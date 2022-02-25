'''
354 Russian Doll Envelopes

You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.

 

Example 1:

Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
Example 2:

Input: envelopes = [[1,1],[1,1],[1,1]]
Output: 1
 

Constraints:

1 <= envelopes.length <= 10^5
envelopes[i].length == 2
1 <= wi, hi <= 10^5
'''
import bisect
from re import search

'''
暴力搜索 + 一点点dp 超时
'''
class Solution1:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        self.dp = {}
        for x, y in envelopes:
            self.dp[(x, y)] = -1
        
        self.xsorted = sorted(self.dp, key=lambda x: x[0])
        self.ysorted = sorted(self.dp, key=lambda x: x[1])
        
        res = 0
        for k in self.xsorted:
            res = max(res, self.search_dp(k))
        
        return res
        
    def search_dp(self, key):
        if self.dp[key] != -1:
            return self.dp[key]
        
        xsmaller = set()
        ysmaller = set()
        for x, y in self.xsorted:
            if x >= key[0]:
                break
            xsmaller.add((x, y))
        for x, y in self.ysorted:
            if y >= key[1]:
                break
            ysmaller.add((x, y))

        smaller = xsmaller & ysmaller
        curv = 1
        for sk in smaller:
            curv = max(curv, 1 + self.search_dp(sk))
        
        self.dp[key] = curv
        return self.dp[key]

'''
在microsoft problem 300 中，解决过最长上升子序列的问题
在这道题，对信封w排序，那么可以只考虑h，当w严格单调递增的时候，等价于求h序列的最长上升子序列
当w不严格单调递增的时候，把w相同的h做降序排列，这样就不会选出不严格单调递增的信封序列了
'''

class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        senv = sorted(envelopes, key=lambda x: (x[0], -x[1]))
        elen = len(envelopes)
        dp = [senv[0][1]]
        for i in range(1, elen):
            if senv[i][1] > dp[-1]:
                dp.append(senv[i][1])
            else:
                dp[bisect.bisect_left(dp, senv[i][1])] = senv[i][1]
        return len(dp)
