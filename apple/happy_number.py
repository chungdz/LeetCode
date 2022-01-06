'''
202 happy number

Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

 

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Example 2:

Input: n = 2
Output: false
 

Constraints:

1 <= n <= 231 - 1

基本思想

重复直到循环
'''

class Solution:
    def isHappy(self, n: int) -> bool:
        single_square = {}
        for i in range(10):
            single_square[i] = i * i
        self.ss = single_square
        visited = set()
        curn = n
        while curn != 1:
            if curn in visited:
                return False
            visited.add(curn)
            curn = self.nxt(curn)
        
        return True
    
    def nxt(self, n):
        strn = str(n)
        total = 0
        for digit in strn:
            total += self.ss[int(digit)]
        return total