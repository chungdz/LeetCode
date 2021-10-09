'''
78 Subsets

Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.

基本思想

位运算，有10个元素的set，它的set个数为2^10，它的每个subset的状态用10个二进制数字表示，每个位上为1就表示再subset中存在
遍历0到2^10 - 1
'''

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []
        nlen = len(nums)
        end = 1 << nlen
        for i in range(end):
            cur_set = []
            for j in range(nlen):
                if (i >> j) & 1 == 1:
                    cur_set.append(nums[j])
            res.append(cur_set)
        return res