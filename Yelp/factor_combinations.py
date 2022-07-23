'''
254 Factor Combinations
Numbers can be regarded as the product of their factors.

For example, 8 = 2 x 2 x 2 = 2 x 4.
Given an integer n, return all possible combinations of its factors. You may return the answer in any order.

Note that the factors should be in the range [2, n - 1].

 

Example 1:

Input: n = 1
Output: []
Example 2:

Input: n = 12
Output: [[2,6],[3,4],[2,2,3]]
Example 3:

Input: n = 37
Output: []
 

Constraints:

1 <= n <= 10^7

思想
每次遍历从左遍历到sqrt(n)，插入两个factors

然后从较小factors开始，拆分较大的factor（避免重复，保持升序），得到子数组，再加在一起


'''
import math

class Solution:
    def getFactors(self, n: int) -> List[List[int]]:
        
        def dfs(curn, left):
            res = []
            for small in range(left, int(math.sqrt(curn)) + 1):
                if curn % small == 0:
                    large = curn // small
                    res.append([small, large])
                    for sub in dfs(large, small):
                        res.append([small] + sub)
            return res

        return dfs(n, 2)