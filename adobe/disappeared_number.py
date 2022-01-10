'''
448 Find All Numbers Disappeared in an Array

Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

 

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Example 2:

Input: nums = [1,1]
Output: [2]
 

Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
 

Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

基本思想

内部交换，如果遇到数字n，并且它不在nums[n - 1]的位置，就和那个位置的数字交换，直到没有数字可以交换

方法二，如果遇到数字x，就nums[x - 1] + n, 到最后不大于n的数就是不存在的数字，由于有的数可能大于n，要先对n取模
'''

class Solution1:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        nlen = len(nums)
        i = 0
        break_flag = True
        while i < nlen:
            if nums[i] != i + 1:
                nxt_index = nums[i] - 1
                if nums[nxt_index] != nums[i]:
                    nums[nxt_index], nums[i] = nums[i], nums[nxt_index]
                    break_flag = False
                else:
                    i += 1
            else:
                i += 1
            
            if i == nlen:
                if break_flag:
                    break
                else:
                    i = 0
                    break_flag = True
        
        res = []
        for i in range(nlen):
            if nums[i] != i + 1:
                res.append(i + 1)
        
        return res

class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        nlen = len(nums)
        for i in range(nlen):
            cur_num = nums[i] % nlen
            cur_idx = cur_num - 1
            nums[cur_idx] += nlen
        
        res = []
        for i in range(nlen):
            if nums[i] <= nlen:
                res.append(i + 1)
        
        return res