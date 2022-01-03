import math
import copy

'''
39 Combination Sum

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
 

Constraints:

1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500

基本思路
简单的递归题目，注意数字不是按顺序排列的，所以有的剪枝不能使用
'''

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        self.cur_list = []
        self.res = []
        self.cand = candidates
        self.dfs_search(0, target)
        return self.res

    def dfs_search(self, cidx, left):
        if left == 0:
            self.res.append(copy.copy(self.cur_list))
            return

        if cidx >= len(self.cand):
            return
        
        max_num = int(left / self.cand[cidx]) + 1
        for i in range(max_num):
            self.dfs_search(cidx + 1, left - i * self.cand[cidx])
            self.cur_list.append(self.cand[cidx])
        
        self.cur_list = self.cur_list[:-max_num]
        
        return