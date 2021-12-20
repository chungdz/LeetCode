'''
18 4sum

Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
 

Constraints:

1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9

基本思想：
把数字两两加和，得到新的数组，再用新的数组里的数字两两加和，需要去重和检查，所以用python
'''

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        singleNumberCount = {}
        doubleNumberCount = {}
        for n in nums:
            if n in singleNumberCount:
                singleNumberCount[n] += 1
            else:
                singleNumberCount[n] = 1
        self.snc = singleNumberCount

        snums = sorted(nums)
        slen = len(snums)
        for i in range(slen):
            for j in range(i + 1, slen):
                num1 = snums[i]
                num2 = snums[j]
                sum12 = num1 + num2
                if sum12 not in doubleNumberCount:
                    doubleNumberCount[sum12] = set()
                doubleNumberCount[sum12].add((num1, num2))

        self.res = set()
        self.toReturn = []
        # avoid repeatation, only add with larger one
        for csum, combines in doubleNumberCount.items():
            nxt_num = target - csum
            if nxt_num < csum:
                continue

            clen = len(combines)
            clist = list(combines)
            if nxt_num == csum and clen > 1:
                for i in range(clen):
                    for j in range(i, clen):
                        self.check_and_add(clist[i], clist[j])
            elif nxt_num in doubleNumberCount:
                nclist = list(doubleNumberCount[nxt_num])
                nclen = len(nclist)
                for i in range(clen):
                    for j in range(nclen):
                        self.check_and_add(clist[i], nclist[j])

        return self.toReturn
    
    def check_and_add(self, c1, c2):
        nlist = sorted([c1[0], c1[1], c2[0], c2[1]])
        ndict = {}
        for n in nlist:
            if n not in ndict:
                ndict[n] = 1
            else:
                ndict[n] += 1
        for n, nc in ndict.items():
            if nc > self.snc[n]:
                return False
        
        ntuple = tuple(nlist)
        if ntuple in self.res:
            return False
        
        self.res.add(ntuple)
        self.toReturn.append(nlist)

        return True