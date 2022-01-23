'''
400 Nth Digit

Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].

Example 1:

Input: n = 3
Output: 3
Example 2:

Input: n = 11
Output: 0
Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
 

Constraints:

1 <= n <= 2^31 - 1

基本思想

写规则依次数数
'''

import math

class Solution:
    def findNthDigit(self, n: int) -> int:

        cur_max = 10
        cur_min = 1
        tmp = n
        for i in range(1, 11):
            crange = cur_max - cur_min
            tmp_digit = tmp // i
            if tmp_digit < crange:
                pos = tmp % i
                cur_num = cur_min + tmp_digit - 1
                nxt_num = cur_num + 1
                if pos == 0:
                    return int(str(cur_num)[-1])
                else:
                    return int(str(nxt_num)[pos - 1])
            else:
                tmp -= crange * i
                cur_min = cur_max
                cur_max *= 10

