'''
280 wiggle sort

Given an integer array nums, reorder it such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

You may assume the input array always has a valid answer.

 

Example 1:

Input: nums = [3,5,2,1,6,4]
Output: [3,5,1,6,2,4]
Explanation: [1,6,2,5,3,4] is also accepted.
Example 2:

Input: nums = [6,6,5,6,3,8]
Output: [6,6,5,6,3,8]
 

Constraints:

1 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 10^4
It is guaranteed that there will be an answer for the given input nums.

思想：
判断相邻是否满足需求，不满足就交换，一定可以保持前面已经满足的需求
'''

class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        shouldLess = True
        for i in range(len(nums) - 1):
            if (shouldLess and nums[i] > nums[i + 1]) or (not shouldLess and nums[i] < nums[i + 1]):
                nums[i], nums[i + 1] = nums[i + 1], nums[i]
            shouldLess = not shouldLess
        