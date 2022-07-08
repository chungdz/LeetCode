from functools import cmp_to_key

def mycmp(x, y):
    s1 = x + y
    s2 = y + x

    if s1 < s2:
        return 1
    if s1 > s2:
        return -1
    return 0

class Solution:
    def largestNumber(self, nums: List[int]) -> str:
        res = ''.join(sorted([str(n) for n in nums], key=cmp_to_key(mycmp)))
        if res[0] != '0':
            return res
        else:
            return '0' 
