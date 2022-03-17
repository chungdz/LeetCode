'''
227 Basic calculator II

Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 10^5
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 2^31 - 1].
The answer is guaranteed to fit in a 32-bit integer.

基本思想

把乘法除法看成是一个整体的数字，线性时间顺序处理
'''

class Solution:
    def calculate(self, s: str) -> int:
        s = s.replace(' ', '')
        if s[0] != '-':
            s = '+' + s
        
        return self.parse_side(s)
    
    def parse_side(self, eq):
        nsum = 0
        start = 0
        elen = len(eq)
        while start < elen:
            end = start + 1
            while end < elen and eq[end] != "+" and eq[end] != '-':
                end += 1
            cur_p = eq[start: end]
            cur_num = self.parse_one(cur_p)
            nsum += cur_num
            start = end
        
        return nsum
    
    def parse_one(self, s):
        sign = 1
        if s[0] == '-':
            sign = -1

        slen = len(s)
        cur_num = 1
        pre_symbol = '*'
        start = 1
        while start < slen:
            end = start + 1
            while end < slen and s[end].isdigit():
                end += 1
            curn = int(s[start: end])
            if pre_symbol == '*':
                cur_num = cur_num * curn
            else:
                cur_num = cur_num // curn
            
            if end < slen:
                pre_symbol = s[end]
            
            start = end + 1
        
        return cur_num * sign