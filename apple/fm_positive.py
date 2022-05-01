'''
41 First Missing Positive

Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses constant extra space.

 

Example 1:

Input: nums = [1,2,0]
Output: 3
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
 

Constraints:

1 <= nums.length <= 5 * 10^5
-2^31 <= nums[i] <= 2^31 - 1

基本思想

一个长为n的list最多能放1 ~ n个正整数
所以我们只关心这个范围内的数字，超过这个范围的数字一定不是最小正整数，把他们全部看成是空值

第一遍遍历，在idx位置的数字x，如果不等于idx + 1，且在数字范围内，就把它放到nums[x - 1]的位置上，然后检查nums[x - 1]位置的数字
直到遇到第一个不在范围内的数字，或者是新的x需要填充的位置已经有x了。

如果不在范围内，直接按照空置放置不管

扫描第二遍把第一个不合规位置返回，如果都合规，返回highest + 1
'''

class Solution:
    def firstMissingPositive(self, nums) -> int:
        highest = len(nums)
        for idx in range(len(nums)):
            anchor = idx + 1
            tmp = nums[idx]
            if anchor == tmp:
                continue
            
            nums[idx] = highest + 1
            while tmp <= highest and tmp > 0:
                if nums[tmp - 1] == tmp:
                    break
                new_tmp = nums[tmp - 1]
                nums[tmp - 1] = tmp
                tmp = new_tmp
                    
        for idx in range(len(nums)):
            anchor = idx + 1
            if nums[idx] != anchor:
                return anchor
        
        return highest + 1