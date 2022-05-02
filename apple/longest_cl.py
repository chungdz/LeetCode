'''
128  Longest Consecutive Sequence

Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
 

Constraints:

0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

基本思想 拓扑问题，建立拓扑图，从无父节点的节点开始遍历
'''

class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        if len(nums) < 1:
            return 0
        
        vdict = {}
        for n in nums:
            if n in vdict:
                continue
            
            if n - 1 in vdict:
                vdict[n] = True
            else:
                vdict[n] = False
            
            if n + 1 in vdict:
                vdict[n + 1] = True
        
        res = 0
        for k, hasPre in vdict.items():
            if not hasPre:
                tmp = 0
                curn = k
                while curn in vdict:
                    tmp += 1
                    curn += 1
                
                res = max(res, tmp)
        
        return res