'''
977 Squares of a Sorted Array

Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.
 

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?

基本思想

双指针
'''

class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        nlen = len(nums)
        res = []
        pindex = 0
        while nums[pindex] < 0:
            pindex += 1
            if pindex >= nlen:
                break
        nindex = pindex - 1

        while True:

            if pindex < nlen:
                if nindex >= 0:
                    if -nums[nindex] > nums[pindex]:
                        res.append(nums[pindex] * nums[pindex])
                        pindex += 1
                    else:
                        res.append(nums[nindex] * nums[nindex])
                        nindex -= 1
                else:
                    res.append(nums[pindex] * nums[pindex])
                    pindex += 1
            elif nindex >= 0:
                res.append(nums[nindex] * nums[nindex])
                nindex -= 1
            else:
                break
        
        return res

