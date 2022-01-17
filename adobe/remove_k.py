'''
402 Remove K Digits

Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

 

Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 

Constraints:

1 <= k <= num.length <= 10^5
num consists of only digits.
num does not have any leading zeros except for the zero itself.

基本思想

贪心，尽最大程度保证result是单调递增的序列，所以每次有a_{i + 1} < a_{i}，就把序列尾部所有大于a_{i + 1}的数字
删除，直到序列为空，或者删除数量最大
'''

class Solution:

    def removeKdigits(self, num: str, k: int) -> str:

        res_list = []
        nlen = len(num)
        cnt = 0

        res_list.append(num[0])
        idx = 1
        while idx < nlen:
            while len(res_list) > 0 and res_list[-1] > num[idx] and cnt < k:
                res_list.pop()
                cnt += 1
            res_list.append(num[idx])
            idx += 1
        
        while res_list[0] == "0":
            res_list.pop(0)
        
        if len(res_list) == 0:
            return "0"
        
        return "".join(res_list)
                
